/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef GATHER_H
#define GATHER_H

/***************************************************************************//**
 * Gathering all the columns from the each worker smallmap as described in the report.
 * @size 				The number processes. 
 * @dims[N_DIMS]:   	Table dimensions of MPP_cart_dim
 * @map:	 			The full map that is gathered into multiple pieces. 
 * @smallmap:		 	The small map that the process receives
 * @comm2D: 			The MPI communicator that the operation will happen on.
 * @con: 				A pointer that points to the configuration structure
 *            			that user data input will be stored.
 * @requests 			The requests that are issued for communication.
 * @status 				The status that are issued for communication.
 ******************************************************************************/
void gather_master(int size,int dims[N_DIMS],int**map,int** smallmap,
                   MPI_Comm* comm2D, configure* con, MPI_Request* requests,MPI_Status* status);


/***************************************************************************//**
 * Sending all the columns of the small map to master described in the report.
 * @rank 				The rank of the process. 
 * @smallmap_dims:   	The lenght and height of the small map on the process.
 * @map:	 			The full map that is gathered into multiple pieces. 
 * @smallmap:		 	The small map that the process receives
 * @comm2D: 			The MPI communicator that the operation will happen on.
 * @requests 			The requests that are issued for communication.
 * @status 				The status that are issued for communication.
 ******************************************************************************/
void gather_worker(int rank, int** smallmap_dims,int** smallmap, MPI_Comm* comm2D,
                   MPI_Request* requests,MPI_Status* status);




#endif
