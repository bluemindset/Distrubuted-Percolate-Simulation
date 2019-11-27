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
#include "map.h"
/*====================================================================*/

void percolation_check(int** map,configure* con){

   int itop,ibot ,perc = 0;

    for (itop = 0; itop < con->L; itop++)
    {
        if (map[itop][con->L - 1] > 0)
        {
            for (ibot = 0; ibot < con->L; ibot++)
            {
                if (map[itop][con->L - 1] == map[ibot][0])
                {
                    perc = 1;
                }
            }
        }
    }
    if (perc != 0)
    {
        printf("percolate: cluster DOES percolate\n");
    }
    else
    {
        printf("percolate: cluster DOES NOT percolate\n");
    }
}

void init_density(configure* con,int **map,int *nhole){
    int i,j;
    double r;
    for (i = 0; i < con->L; i++)
    {
        for (j = 0; j < con->L; j++)
        {
            r = uni();

            if (r < con->rho)
            {
                map[i][j] = 0;
            }
            else
            {
                (*nhole)++;
                map[i][j] = *nhole;
            }
        }
    }
    printf("percolate: rho = %f, actual density = %f\n",
           con->rho, 1.0 - ((double) *nhole) / ((double) con->L * con->L) );
}

void init_smallmap(configure *con,int** smallmap,int** smallmap_dims,int** map,int dims[N_DIMS],bounds* b){

    int i,j;

    smallmap_dims[0][0] = b->deltaH;
    smallmap_dims[0][1] = b->deltaW;

    for (i = 0; i < b->eH; i++)
    {
        for (j = 0; j < b->eW; j++)
        {
            smallmap[i][j] = map[i][j];
        }
    }
}

void init_old_map(int rank, int** smallmap_dims, int** smallmap, int** old){
    int i,j;
    for (i = 1; i <= smallmap_dims[rank][0]; i++)
    {
        for (j = 1; j <= smallmap_dims[rank][1]; j++)
        {
            old[i][j] = smallmap[i - 1][j - 1];
        }
    }
    for (i = 0; i <= smallmap_dims[rank][0] + 1; i++) // zero the bottom and top halos
    {
        old[i][0]   = 0;
        old[i][smallmap_dims[rank][1] + 1] = 0;
    }
    for (j = 0; j <= smallmap_dims[rank][1] + 1; j++) // zero the left and right halos
    {
        old[0][j]   = 0;
        old[smallmap_dims[rank][0] + 1][j] = 0;
    }
}



void start_halo_exchange(int rank, MPI_Request*  send_requests, MPI_Request*  recv_requests, MPI_Status* send_status, MPI_Status* recv_status, MPI_Comm* comm2D,
                         int** smallmap_dims,int **old){

    int left, right, up, down;
    MPI_Datatype colTypeN;
    MPI_Datatype rowTypeN;

    /*Find neighbors*/
    MPI_Cart_shift( *comm2D, ZERO_DIM, 1, &up, &down);
    MPI_Cart_shift( *comm2D, FIRST_DIM, 1, &left, &right);
    
    /*Create vectors and commit them*/
    MPI_Type_vector(smallmap_dims[rank][0], 1, smallmap_dims[rank][1] + 2, MPI_INT, &colTypeN);
    MPI_Type_vector(1, smallmap_dims[rank][1], smallmap_dims[rank][1] + 2, MPI_INT, &rowTypeN);
    MPI_Type_commit(&colTypeN);
    MPI_Type_commit(&rowTypeN);

    /*Right and left neighbors, mind the tags*/
    MPI_Issend(&old[1][smallmap_dims[rank][1]], 1, colTypeN, right, 1, *comm2D, &send_requests[0]);
    MPI_Issend(&old[1][1], 1, colTypeN, left, 0, *comm2D, &send_requests[1]);
    MPI_Irecv(&old[1][0], 1, colTypeN, left, 1, *comm2D, &recv_requests[0]);
    MPI_Irecv(&old[1][smallmap_dims[rank][1] + 1], 1, colTypeN, right, 0, *comm2D, &recv_requests[1]);

    /*Up and down neighbors, mind the tags*/
    MPI_Issend(&old[1][1], 1, rowTypeN, up, 0, *comm2D, &send_requests[2]);
    MPI_Issend(&old[smallmap_dims[rank][0]][1], 1, rowTypeN, down, 1, *comm2D, &send_requests[3]);
    MPI_Irecv(&old[0][1], 1, rowTypeN, up, 1, *comm2D, &recv_requests[2]);
    MPI_Irecv(&old[smallmap_dims[rank][0] + 1][1], 1, rowTypeN, down, 0, *comm2D, &recv_requests[3]);
}

void update_neighbors(int** old,int** new,int* nchange,int i ,int j){
    int oldval,newval;

    oldval = old[i][j];
    newval = oldval;

    if (oldval != 0)
    {
        if (old[i - 1][j] > newval) newval = old[i - 1][j];
        if (old[i + 1][j] > newval) newval = old[i + 1][j];
        if (old[i][j - 1] > newval) newval = old[i][j - 1];
        if (old[i][j + 1] > newval) newval = old[i][j + 1];

        if (newval != oldval)
        {
            ++(*nchange);
        }
    }
    new[i][j] = newval;
}

void update_inner_cells(int rank, int** smallmap_dims,int** old,int** new,int *nchange){

    int i,j;
    for (i = 2; i <= smallmap_dims[rank][0] - 1; i++)
    {
        for (j = 2; j <= smallmap_dims[rank][1] - 1; j++)
        {
            update_neighbors(old,new,nchange,i,j);
        }
    }
}

void update_outer_cells(int rank,int** smallmap_dims,int** old, int** new , int* nchange){
    int i,j;

    i = 1;
    for (j = 1 ; j <= smallmap_dims[rank][1]; j++)
    {
        update_neighbors(old,new,nchange,i,j);
    }

/*************************************************************************/
    i = smallmap_dims[rank][0];

    for (j = 1 ; j <= smallmap_dims[rank][1]; j++)
    {
        update_neighbors(old,new,nchange,i,j);
    }

/*************************************************************************/
    j = smallmap_dims[rank][1];

    for (i = 1 ; i <= smallmap_dims[rank][0]; i++)
    {
        update_neighbors(old,new,nchange,i,j);
    }

/*************************************************************************/
    j = 1;

    for (i = 1 ; i <= smallmap_dims[rank][0]; i++)
    {
        update_neighbors(old,new,nchange,i,j);
    }
}

long update_maps(int rank, int** smallmap_dims,int** old, int** new){

    int i,j;
    long sum =0;
    for (i = 1; i <= smallmap_dims[rank][0]; i++)
    {
        for (j = 1; j <= smallmap_dims[rank][1]; j++)
        {
            sum += new[i][j];
            old[i][j] = new[i][j];
        }
    }
    return sum;
}


void print_changes(int step, int* nchange, double average,int rank){
    
    if (step % PRINT_FREQ == 0)
    {
        printf("Rank %d percolate: number of changes on step %d is %d\n",
               rank, step, *nchange);
        printf("Average is: %.3f\n",average); 
    }

}

void update_small_map(int rank,int** smallmap, int** smallmap_dims,int** old){
    int i,j;
    for (i = 1; i <= smallmap_dims[rank][0]; i++)
    {
        for (j = 1; j <= smallmap_dims[rank][1]; j++)
        {
            smallmap[i - 1][j - 1] = old[i][j];
        }
    }
}


void find_bounds(int rank, bounds *b, int dims[2],configure* con)
{
    int factorW, factorH;
    float d, dW, dH;
    factorW = rank % (dims[1]);
    factorH = floor(rank / dims[1]);
    dW = con->L / (float) dims[1];
    dH = con->L / (float) dims[0];

    b->sW = (int) ceil((double) (dW * factorW));
    b->eW = (int) ceil((double) (dW * (factorW + 1)));

    /*Calculate the starting height*/
    b->sH = (int) ceil((double) (factorH * dH));
    b->eH = (int) ceil((double) ((factorH + 1) * dH));

    /* If assignment goes beyond the limit then slice it until N*/
    if (b->eH > con->L) b->eH = con->L;
    if (b->eW > con->L) b->eW = con->L;

    b->deltaH = b->eH - b->sH;
    b->deltaW = b->eW - b->sW;
}

