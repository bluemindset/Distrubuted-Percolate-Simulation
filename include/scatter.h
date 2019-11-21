//
// Created by blue on 21/11/2019.
//

#ifndef SCATTER_H
#define SCATTER_H

void scatter_master(int size,int dims[N_DIMS], configure *con, int** map, MPI_Comm* comm2D, MPI_Request* requests,MPI_Status* status,bounds *b);

void scatter_worker(int rank, int** smallmap,int** smallmap_dims, MPI_Comm* comm2D, MPI_Request* requests,MPI_Status* status,bounds *b);


#endif //PROJECT_SCATTER_H
