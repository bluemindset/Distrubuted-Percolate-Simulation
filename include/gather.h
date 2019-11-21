//
// Created by blue on 21/11/2019.
//

#ifndef GATHER_H
#define GATHER_H

void gather_master(int size,int dims[N_DIMS],int**map,int** smallmap,
                   MPI_Comm* comm2D, configure* con, MPI_Request* requests,MPI_Status* status);



void gather_worker(int rank, int** smallmap_dims,int** smallmap, MPI_Comm* comm2D,
                   MPI_Request* requests,MPI_Status* status);




#endif //PROJECT_GATHER_H
