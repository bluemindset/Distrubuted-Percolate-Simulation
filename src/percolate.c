#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <curses.h>
#include <math.h>
#include <assert.h>
#include <getopt.h>
#include "arralloc.h"
#include "configuration.h"
#include "userInput.h"
#include "percolate.h"
#include "timer.h"
#include "arralloc.h"
#include "allocs.h"
#include "scatter.h"
#include "gather.h"
#include "map.h"
#include "percwrite.h"

void comm_config(int dims[N_DIMS], int period[N_DIMS])
{
    /*Create Cartesian Topology*/
    dims[0] = 0;
    dims[1] = 0;
    period[0] = 1;
    period[1] = 0;
}

int main(int argc, char *argv[])
{
    /***********************************************************************/
    /* Size, Rank and Neighbors
    /***********************************************************************/
    int size, rank;
    /***********************************************************************/
    /* Dimensions
    /***********************************************************************/
    int periods[N_DIMS];
    int dims[N_DIMS];
   
    int nhole, step, nchange, stop;
    long local_sum,global_sum;
    double average;

    /***********************************************************************/
    /* GRIDS
    /***********************************************************************/

    int **map = NULL;
    int **smallmap = NULL;
    int **smallmap_dims = NULL;
    int **old = NULL;
    int **new = NULL;

    /***********************************************************************/
    /* MPI Communication Initialization * Dimensions
    /***********************************************************************/

    MPI_Comm comm2D;
    /*Give birth to the Universe */
    MPI_Init(NULL, NULL);
    /*Create a new comm2D*/
    comm_config(dims, periods);
    /* Create Dimensions */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, N_DIMS, dims);
    /* Create cartesians */
    MPI_Cart_create(MPI_COMM_WORLD, N_DIMS, dims, periods, 0, &comm2D);
    /*Find the rank*/
    MPI_Comm_rank(comm2D, &rank);

    /***********************************************************************/
    /* Gather Configuration
    /***********************************************************************/
    configure con;
    get_input(&con, argc, argv);

    /***********************************************************************/
    /* Initialize Maps
    /***********************************************************************/
    map =(int **) arralloc(sizeof(int), 2, con.L, con.L);
    smallmap_dims =(int **) arralloc(sizeof(int), 2, size, 2);

    if (rank==MASTER) {
        printf("percolate: params are L = %d, rho = %f, seed = %d\n", con.L, con.rho, con.seed);
    }
    rinit(con.seed);
    MPI_Barrier(comm2D);

    /***********************************************************************/
    /*Start Timers*/
    /***********************************************************************/
    TIMER_init();
    TIMER_start(TIMER_TOTAL);

    /***********************************************************************/
    nhole = 0;

    /************************************************/

    /*Total Requests*/
    int total_req = 0 ;
    /***********************************************************************/
    /*Requests & Status
    /***********************************************************************/
    MPI_Request* requests = NULL ;
    requests =(MPI_Request  *) malloc(sizeof(MPI_Request*) * (con.L*con.L ));
    MPI_Status* status = NULL;
    status =(MPI_Status  *) malloc(sizeof(MPI_Status*) * (con.L*con.L));


    /******************************************Initialize MAP DENSITY**************************************************/
    if (rank == MASTER)
        init_density(&con,map,&nhole);
    MPI_Barrier(comm2D);
    /******************************************Initialize MAP DENSITY**************************************************/


    /******************************************Initialize SMALL MAP****************************************************/
    bounds b ;
    find_bounds(rank, &b, dims,&con);
    smallmap = (int **) arralloc(sizeof(int), 2, b.deltaH, b.deltaW);
    /******************************************Initialize SMALL MAP****************************************************/


    /***************************************************SCATTER********************************************************/
    if (rank == MASTER) {
        init_rank_zero(&con, smallmap,smallmap_dims,map,dims,&b);
        scatter_master(size,dims, &con, map, &comm2D, requests,status,&b);
    }
    else
        scatter_worker(rank,smallmap,smallmap_dims, &comm2D, requests,status,&b);
    /***************************************************SCATTER********************************************************/


    /********************************************INITIALIZE OLD & NEW MAPS*********************************************/

    old = (int **) arralloc(sizeof(int), 2, smallmap_dims[rank][0] + 2, smallmap_dims[rank][1] + 2);
    new = (int **) arralloc(sizeof(int), 2, smallmap_dims[rank][0] + 2, smallmap_dims[rank][1] + 2);

    init_old_map(rank, smallmap_dims, smallmap,old);

    /********************************************INITIALIZE OLD & NEW MAPS*********************************************/

    /***********************************************UPDATE*************************************************************/
    step = 1;
    stop = 1;

    TIMER_start(TIMER_UPDATE);
    while (stop != 0)
    {
        nchange = 0;
        MPI_Request  halo_send_requests[4];
        MPI_Request  halo_recv_requests[4];
        MPI_Status   halo_send_status[4];
        MPI_Status   halo_recv_status[4];

        /**************************************** START HALO EXCHANGE ******************************************/
        start_halo_exchange(rank, halo_send_requests,halo_recv_requests,halo_send_status,halo_recv_status,
                            &comm2D,smallmap_dims,old);
        /**************************************** START HALO EXCHANGE ******************************************/


        /***************************************** UPDATE INNER CELLS ******************************************/
         update_inner_cells(rank, smallmap_dims,old,new,&nchange);
        /***************************************** UPDATE INNER CELLS ******************************************/


        /******************************************** WAIT HALO EXCHANGE  **************************************/
        MPI_Waitall(SHALLOW_HALO, halo_recv_requests, halo_recv_status);
        MPI_Waitall(SHALLOW_HALO, halo_send_requests, halo_send_status);
        /******************************************** WAIT HALO EXCHANGE ***************************************/


        /***************************************** UPDATE HALO(OUTER) CELLS**************************************/
        update_outer_cells(rank,smallmap_dims,old, new , &nchange);
        /***************************************** UPDATE HALO(OUTER) CELLS**************************************/

        /***************************************** CALCULATE AVERAGE of MAP**************************************/
        local_sum = map_sum(rank, new, smallmap_dims); 

        MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG, MPI_SUM, MASTER,comm2D);
        if (rank==MASTER)
            average =  (double) global_sum / (con.L*con.L); 

        /***************************************** CALCULATE AVERAGE of MAP**************************************/
        print_changes(step,&nchange,average,rank);
        update_maps(rank,smallmap_dims,old, new);   /*Copy new into old*/
        MPI_Allreduce(&nchange, &stop, 1, MPI_INT, MPI_SUM, comm2D);    /*Check for if loop converge*/
        step++;

    }

    TIMER_stop(TIMER_UPDATE);
    TIMER_dump(comm2D,rank,size,step);
/***********************************************UPDATE*****************************************************************/

    update_center_map(rank,smallmap,smallmap_dims,old);

/***************************************GATHERING & WRITING INTO FILE *************************************************/
    if (rank == MASTER) {
        gather_master(size, dims, map, smallmap, &comm2D, &con, requests, status);
        write_map_file(map, &con);
        percwrite("map.pgm", map,con.L, con.max_clusters);
    }
    else
        gather_worker( rank, smallmap_dims,smallmap, &comm2D,
             requests,status);
 /************************************FINISH GATHERING****************************************************************/


/************************************************** STATISTICS *******************************************************/
    MPI_Barrier(comm2D);
    printf("\n-------------------TIME STATISTICS----------------------\n");
    printf("STEPS are %d Average is %.3f\n", step,average);
    TIMER_stop(TIMER_TOTAL);
    TIMER_dump(comm2D,rank,size,step);
    MPI_Finalize();
/************************************************** STATISTICS *******************************************************/

    return 0;
}