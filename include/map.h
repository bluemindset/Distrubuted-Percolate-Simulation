/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef MAP_H
#define MAP_H

/***************************************************************************//**
* Test to see if percolation occurred by looking for positive numbers
* that appear on both the top and bottom edges
* @comm  		The communicator to use for selecting the timers.
* @rank			The rank of the process to dump its timing.
* @size 		Number of all the processes.
* @steps		The number of steps of the update loop.
* @con: 		A pointer that points to the configuration structure
*            	that user data input will be stored.
* @map:	 		The full map that is gathered into multiple pieces. 
 ******************************************************************************/
void percolation_check(int** map,configure* con);

/***************************************************************************//**
* Initialize the density to the map by updating some squares to the integer
* value 1. This squares are selected by comparing an output of a random uniform
* with the density ρ (rho) given by the user. The random uniform function found
* in uni.c file which uses a random seed.
*
* @param con:        	A pointer that points to the configuration structure. The
*                    	function use some values from it.
* @param map:    		The 2D array where the map is stored.
* @param nhole:			A counter that enter an increasing value by one if the 
*						map square is not empty.
 *******************************************************************************/
void init_density(configure* con,int **map,int *nhole);

/***************************************************************************//**
* Initialize the small map on master rank to be all zero.
*
* @param con:        	A pointer that points to the configuration structure. The
*                    	function use some values from it.
* @param smallmap:    	The 2D array where the map is stored.
* @param smallmap_dims: A counter that enter an increasing value by one if the 
*						map square is not empty.
* @smallmap:		 	The small map that the process receives
* @map:	 				The full map that is gathered into multiple pieces. 
* @dims[N_DIMS]:   		Table dimensions of MPP_dim_create
* @b:					The bounds of the current process - Start/End Width-Height
 *******************************************************************************/
void init_smallmap(configure *con,int** smallmap,int** smallmap_dims,int** map,int dims[N_DIMS],bounds* b);


/***************************************************************************//**
* Initialise the old array: copy the LxL array map to the centre of
* old, and set the halo values to zero.
*
* @rank:	 			The rank of the process.
* @param smallmap:    	The 2D array where the small map is stored.
* @param smallmap_dims: A counter that enter an increasing value by one if the 
*						map square is not empty.
* @smallmap:		 	The small map that the process receives
* @old:					The small old map.
 *******************************************************************************/
void init_old_map(int rank, int** smallmap_dims, int** smallmap, int** old);

/***************************************************************************//**
* Start the halo exchange by issuing Isends and Irecvs.
* @rank:	 			The rank of the process.
* @send_requests 		The requests that are issued for sending the halos.
* @recv_requests 		The requests that are issued for receiving the halos.
* @send_status			The status that are issued for sending the halos.
* @recv_status			The status that are issued for receiving the halos.
* @comm2D: 			The MPI communicator that the operation will happen on.
* @smallmap_dims:   	The lenght and height of the small map on the process.
* @old:					The small old map.
/******************************************************************************/
void start_halo_exchange(int rank, MPI_Request*  send_requests, MPI_Request*  recv_requests,
                         MPI_Status* send_status, MPI_Status* recv_status, MPI_Comm* comm2D,
                         int** smallmap_dims,int **old);

/***************************************************************************//**
* Update the neighbors. The same mechanism (four ifs) are used in the serial 
* version of the program.
* @old:					The small old map.
* @new:					The small new map.
* @nchange				The number of changes during updating
* @i,j					Indicators for updating the particular cell
/******************************************************************************/
void update_neighbors(int** old,int** new,int* nchange,int i ,int j);


/***************************************************************************//**
* Update the inner cells of the small map, the ones that are not in halos.
* @rank:	 			The rank of the process.
* @old:					The small old map.
* @new:					The small new map.
* @nchange				The number of changes during updating
* @smallmap_dims:   	The lenght and height of the small map on the process.
/******************************************************************************/
void update_inner_cells(int rank, int** smallmap_dims,int** old,int** new,int *nchange);

/***************************************************************************//**
* Update the outer cells of the small map, the halos.
* @rank:	 			The rank of the process.
* @old:					The small old map.
* @new:					The small new map.
* @nchange				The number of changes during updating
* @ smallmap_dims: A counter that enter an increasing value by one if the 
/******************************************************************************/
void update_outer_cells(int rank,int** smallmap_dims,int** old, int** new , int* nchange);

/***************************************************************************//**
* Copy the the new small map into the old small map and calculate the sum of 
* every cell.
* @rank:	 			The rank of the process.
* @old:					The small old map.
* @new:					The small new map.
* @nchange				The number of changes during updating
* @smallmap_dims:   	The lenght and height of the small map on the process.
* @return 				The sum of all the cells.
/******************************************************************************/
long update_maps(int rank, int** smallmap_dims,int** old, int** new);

/***************************************************************************//**
* Print data, number of steps and average every 100 steps
* @step:	 			The number of steps during the update.
* @nchange:				The number of changes during updating
* @average:   			The lenght and height of the small map on the process.
* @rank:	 			The rank of the process.
/******************************************************************************/
void print_changes(int step, int* nchange, double average,int rank);

/***************************************************************************//**
* Copy the old small map into the small map for gathering
* @rank:	 			The rank of the process.
* @smallmap:		 	The small map that the process will give to master.
* @smallmap_dims:   	The lenght and height of the small map on the process.
* @old:					The small old map.
/******************************************************************************/
void update_small_map(int rank,int** smallmap, int** smallmap_dims,int** old);

/***************************************************************************//**
* Find the bounds, of the current process - Start/End Width-Height
* Mathematical notations are included inside the report
* @rank:	 			The rank of the process.
* @b:					The bounds of the current process - Start/End Width-Height
* @dims[N_DIMS]:   		Array dimensions of MPP_dim_create
* @con: 				A pointer that points to the configuration structure
*            			that user data input will be stored.
/******************************************************************************/
void find_bounds(int rank, bounds *b, int dims[2],configure* con);

#endif
