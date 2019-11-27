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
#include "gather.h"
#include "map.h"
/*====================================================================*/

void gather_master(int size,int dims[N_DIMS],int**map,int** smallmap,
                   MPI_Comm* comm2D, configure* con, MPI_Request* requests,MPI_Status* status){

    int rk,i,j,k,total_req = 0 ;
    bounds b;

    for (rk = 1; rk < size; rk++)
    {
        find_bounds(rk, &b, dims,con);
        MPI_Datatype colTypeT;

        MPI_Type_vector(b.deltaH, 1, con->L, MPI_INT, &colTypeT);
        MPI_Type_commit(&colTypeT);
        k = 0;
        for (i = b.sW; i < b.eW; i++)
        {
            MPI_Irecv(&map[b.sH][i], 1, colTypeT, rk, 0, *comm2D, &requests[total_req + k]);
            k++;
        }
        total_req += k;
    }
    MPI_Waitall(total_req, requests, status);

    /*Master must assign to itself*/
    find_bounds(MASTER, &b, dims,con);

    for (i = 0; i < b.eH; i++)
    {
        for (j = 0; j < b.eW; j++)
        {
            map[i][j] = smallmap[i][j];
        }
    }
}



void gather_worker(int rank, int** smallmap_dims,int** smallmap, MPI_Comm* comm2D,
                   MPI_Request* requests,MPI_Status* status){

    int i,k,total_req = 0;

    MPI_Datatype colTypeTT;
    MPI_Type_vector(smallmap_dims[rank][0], 1, smallmap_dims[rank][1], MPI_INT, &colTypeTT);
    MPI_Type_commit(&colTypeTT);
    k = 0;

    for(i = 0; i < smallmap_dims[rank][1]; i++)
    {
        MPI_Isend(&smallmap[0][i], 1, colTypeTT, 0, 0, *comm2D, &requests[k++]);
    }
    total_req = k;
    MPI_Waitall(total_req, requests, status);



}