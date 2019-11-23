//
// Created by blue on 21/11/2019.
//

#ifndef MAP_H
#define MAP_H





void init_density(configure* con,int **map,int *nhole);

void init_rank_zero(configure *con,int** smallmap,int** smallmap_dims,int** map,int dims[N_DIMS],bounds* b);


/* Initialise the old array: copy the LxL array map to the centre of
* old, and set the halo values to zero.
*/
void init_old_map(int rank, int** smallmap_dims, int** smallmap, int** old);
void start_halo_exchange(int rank, MPI_Request*  send_requests, MPI_Request*  recv_requests,
                         MPI_Status* send_status, MPI_Status* recv_status, MPI_Comm* comm2D,
                         int** smallmap_dims,int **old);

void update_neighbors(int** old,int** new,int* nchange,int i ,int j);

void update_inner_cells(int rank, int** smallmap_dims,int** old,int** new,int *nchange);

void update_outer_cells(int rank,int** smallmap_dims,int** old, int** new , int* nchange);



void update_maps(int rank, int** smallmap_dims,int** old, int** new);

void print_changes(int step, int* nchange, double average,int rank);

void update_small_map(int rank,int** smallmap, int** smallmap_dims,int** old);

void find_bounds(int rank, bounds *b, int dims[2],configure* con);
void write_map_file(int** map,configure* con);

long map_sum(int rank,int** old,int** smallmap_dims);

#endif
