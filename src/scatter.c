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
#include "map.h"
/*====================================================================*/

void scatter_master(int size, int dims[N_DIMS], configure *con, int **map, MPI_Comm *comm2D, MPI_Request *requests, MPI_Status *status, bounds *b)
{
    int total_req = 0;
    int rk, i, k;
    for (rk = 1; rk < size; rk++)
    {
        find_bounds(rk, b, dims, con);
        MPI_Datatype colType;

        MPI_Type_vector(b->deltaH, 1, con->L, MPI_INT, &colType);
        MPI_Type_commit(&colType);

        k = 0;
        for (i = b->sW; i < b->eW; i++)
        {
            MPI_Issend(&map[b->sH][i], 1, colType, rk, 0, *comm2D, &requests[total_req + k]);
            k++;
        }
        total_req += k;
    }
    MPI_Waitall(total_req, requests, status);
}

void scatter_worker(int rank, int **smallmap, int **smallmap_dims, MPI_Comm *comm2D, MPI_Request *requests, MPI_Status *status, bounds *b)
{
    int i, total_req = 0;


    MPI_Datatype colType;

    smallmap_dims[rank][0] = b->deltaH;
    smallmap_dims[rank][1] = b->deltaW;

    MPI_Type_vector(b->deltaH, 1, b->deltaW, MPI_INT, &colType);
    MPI_Type_commit(&colType);

    for(i = 0; i < b->deltaW; i++)
    {
        MPI_Irecv(&smallmap[0][i], 1, colType, MASTER, 0, *comm2D, &requests[total_req++]);
    }

    MPI_Waitall(total_req, requests, status);
}