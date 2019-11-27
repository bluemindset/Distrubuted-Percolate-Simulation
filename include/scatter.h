/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/

#ifndef SCATTER_H
#define SCATTER_H


/***************************************************************************//**
 * Scattering all the columns from the big map to the workers, as described in the report.
 * @size 				The number processes. 
 * @dims[N_DIMS]:   	Table dimensions of MPP_cart_dim
 * @map:	 			The full map that is gathered into multiple pieces. 
 * @comm2D: 			The MPI communicator that the operation will happen on.
 * @con: 				A pointer that points to the configuration structure
 *            			that user data input will be stored.
 * @requests 			The requests that are issued for communication.
 * @status 				The status that are issued for communication.
 * @bounds				The bounds of the current process - Start/End Width-Height
 ******************************************************************************/
void scatter_master(int size,int dims[N_DIMS], configure *con, int** map, MPI_Comm* comm2D, 
					MPI_Request* requests,MPI_Status* status,bounds *b);

/***************************************************************************//**
 * Scattering all the columns from the big map to the workers, as described in the report.
 * @size 				The number processes. 
 * @dims[N_DIMS]:   	Table dimensions of MPP_dim_create
 * @map:	 			The full map that is gathered into multiple pieces. 
 * @smallmap:		 	The small map that the process receives.
 * @comm2D: 			The MPI communicator that the operation will happen on.
 * @smallmap_dims:   	The lenght and height of the small map on the process.
 * @requests 			The requests that are issued for communication.
 * @status 				The status that are issued for communication.
 * @b					The bounds of the current process - Start/End Width-Height
 ******************************************************************************/
void scatter_worker(int rank, int** smallmap,int** smallmap_dims, MPI_Comm* comm2D, 
					MPI_Request* requests,MPI_Status* status,bounds *b);

#endif
