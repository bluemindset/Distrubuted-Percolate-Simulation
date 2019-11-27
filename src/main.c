/**
 * @Author: B159973
 * @Date:   26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
/*========================== Library Files ===========================*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <getopt.h>
#include "arralloc.h"
#include "configuration.h"
#include "userInput.h"
#include "main.h"
#include "timer.h"
#include "arralloc.h"
#include "allocs.h"
#include "scatter.h"
#include "gather.h"
#include "map.h"
#include "percwrite.h"
/*====================================================================*/

void comm_config(int dims[N_DIMS], int period[N_DIMS])
{
    /*Configure Cartesian Topology - Insert periodicity on the first dimension*/
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
    /***********************************************************************/
    /* Counter 
    /***********************************************************************/
    int nhole, step, nchange, stop;
    /***********************************************************************/
    /* Local and global sum for finding average 
    /***********************************************************************/
    long local_sum, global_sum;
    double average;
    /***********************************************************************/
    /* Total Requests
    /***********************************************************************/
    int total_req = 0 ; 
    /***********************************************************************/
    /* GRIDS
    /***********************************************************************/
    int **map = NULL;
    int **smallmap = NULL;
    int **smallmap_dims = NULL;
    int **old = NULL;
    int **new = NULL;
    /***********************************************************************/
    /* MPI Communication Declaration
    /***********************************************************************/
    MPI_Comm comm2D;
    /***********************************************************************/
    /* Get the configurations from the user
    /***********************************************************************/
    configure con;
    get_input(&con, argc, argv);

    /***********************************************************************/
    /* Give birth to the Universe
    /***********************************************************************/
    MPI_Init(NULL, NULL);
    /***********************************************************************/
    /* Create a new comm2D with the first dimension to be periodic
    /***********************************************************************/
    comm_config(dims, periods);
    /***********************************************************************/
    /* Get size of the world & Create Dimensions 
    /***********************************************************************/
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, N_DIMS, dims);
    /***********************************************************************/
    /*  Create cartesians
    /***********************************************************************/
    MPI_Cart_create(MPI_COMM_WORLD, N_DIMS, dims, periods, 0, &comm2D);
    /***********************************************************************/
    /* Find the rank
    /***********************************************************************/
    MPI_Comm_rank(comm2D, &rank);
    /***********************************************************************/
    /*Requests & Status for Scatter & Gather 
    /***********************************************************************/
    MPI_Request *requests = NULL ;
    requests = (MPI_Request *) malloc(sizeof(MPI_Request *) * (con.L * con.L ));
    MPI_Status *status = NULL;
    status = (MPI_Status *) malloc(sizeof(MPI_Status *) * (con.L * con.L));
    /***********************************************************************/
    /*Requests & Status for Halo exchange 
    /***********************************************************************/
    MPI_Request  halo_send_requests[SHALLOW_HALO];
    MPI_Request  halo_recv_requests[SHALLOW_HALO];
    MPI_Status   halo_send_status[SHALLOW_HALO];
    MPI_Status   halo_recv_status[SHALLOW_HALO];
    /***********************************************************************/
    /* Initialize Maps
    /***********************************************************************/
    map = (int **) arralloc(sizeof(int), 2, con.L, con.L);
    smallmap_dims = (int **) arralloc(sizeof(int), 2, size, 2);

    if (rank == MASTER)
    {
        printf("percolate: params are L = %d, rho = %f, seed = %d\n", con.L, con.rho, con.seed);
    }
    rinit(con.seed);

    /***********************************************************************/
    /*Start Timers
    /***********************************************************************/
    t_init();
    MPI_Barrier(comm2D);
    t_start(TIMER_TOTAL);


    /******************************************Initialize MAP DENSITY**************************************************/
    nhole = 0;
    if (rank == MASTER)
        init_density(&con, map, &nhole);
    MPI_Barrier(comm2D);
    /******************************************Initialize MAP DENSITY**************************************************/


    /******************************************Initialize SMALL MAP****************************************************/
    bounds b ;
    find_bounds(rank, &b, dims, &con);
    smallmap = (int **) arralloc(sizeof(int), 2, b.deltaH, b.deltaW);
    /******************************************Initialize SMALL MAP****************************************************/


    /***************************************************SCATTER********************************************************/
    if (rank == MASTER)
    {
        init_smallmap(&con, smallmap, smallmap_dims, map, dims, &b);
        scatter_master(size, dims, &con, map, &comm2D, requests, status, &b);
    }
    else
        scatter_worker(rank, smallmap, smallmap_dims, &comm2D, requests, status, &b);
    /***************************************************SCATTER********************************************************/


    /********************************************INITIALIZE OLD & NEW MAPS*********************************************/
    old = (int **) arralloc(sizeof(int), 2, smallmap_dims[rank][0] + 2, smallmap_dims[rank][1] + 2);
    new = (int **) arralloc(sizeof(int), 2, smallmap_dims[rank][0] + 2, smallmap_dims[rank][1] + 2);

    init_old_map(rank, smallmap_dims, smallmap, old);
    /********************************************INITIALIZE OLD & NEW MAPS*********************************************/


    /***********************************************UPDATE*************************************************************/
    step = 1;
    stop = 1;
    /***********************************************************************/
    /*Start Timers
    /***********************************************************************/
    MPI_Barrier(comm2D);
    t_start(TIMER_UPDATE);
    
    while (stop != 0)
    {
        nchange = 0;
        local_sum = 0 ;

        /**************************************** START HALO EXCHANGE ******************************************/
        start_halo_exchange(rank, halo_send_requests, halo_recv_requests, halo_send_status, halo_recv_status,
                            &comm2D, smallmap_dims, old);
        /**************************************** START HALO EXCHANGE ******************************************/

        /***************************************** UPDATE INNER CELLS ******************************************/
        update_inner_cells(rank, smallmap_dims, old, new, &nchange);
        /***************************************** UPDATE INNER CELLS ******************************************/


        /******************************************** WAIT HALO EXCHANGE  **************************************/
        MPI_Waitall(SHALLOW_HALO, halo_recv_requests, halo_recv_status);
        MPI_Waitall(SHALLOW_HALO, halo_send_requests, halo_send_status);
        /******************************************** WAIT HALO EXCHANGE ***************************************/


        /***************************************** UPDATE HALO(OUTER) CELLS**************************************/
        update_outer_cells(rank, smallmap_dims, old, new, &nchange);
        /***************************************** UPDATE HALO(OUTER) CELLS**************************************/

        /***************************************** CALCULATE AVERAGE of MAP**************************************/
        local_sum = update_maps(rank, smallmap_dims, old, new); /*Copy new into old*/
        MPI_Allreduce(&local_sum, &global_sum, 1, MPI_LONG, MPI_SUM, comm2D);
        average =  (double) global_sum / (con.L * con.L);
        /***************************************** CALCULATE AVERAGE of MAP**************************************/

        print_changes(step, &nchange, average, rank); /*Print number of changes and average*/

        /***************************************** STOPPING CRETIRION**************************************/
        MPI_Allreduce(&nchange, &stop, 1, MPI_INT, MPI_SUM, comm2D);    /*Check for if loop converge*/
        step++;
        /***************************************** STOPPING CRETIRION **************************************/
    }
    /***********************************************************************/
    /*Stop Timers
    /***********************************************************************/
    MPI_Barrier(comm2D);
    t_stop(TIMER_UPDATE);

    update_small_map(rank, smallmap, smallmap_dims, old);/*Copy the old small map into the small map*/

    /*************************************** GATHERING & WRITING INTO FILE *************************************************/
    if (rank == MASTER)
    {
        gather_master(size, dims, map, smallmap, &comm2D, &con, requests, status);
        percolation_check(map, &con);
        percwrite("map.pgm", map, con.L, con.max_clusters);
    }
    else
        gather_worker( rank, smallmap_dims, smallmap, &comm2D,
                       requests, status);
    /************************************ GATHERING & WRITING INTO FILE ****************************************************************/


    /************************************************** STATISTICS *******************************************************/
    MPI_Barrier(comm2D);
    printf("\n-------------------TIME STATISTICS----------------------\n");
    printf("STEPS are %d Average is %.3f\n", step, average);
    /***********************************************************************/
    /*Stop Timers & Dump the times
    /***********************************************************************/
    t_stop(TIMER_TOTAL);
    t_dump(comm2D, rank, size, step);
    /***********************************************************************/
    /* Destroy the Universe
    /***********************************************************************/
    MPI_Finalize();
    /************************************************** STATISTICS *******************************************************/

    return 0;
}