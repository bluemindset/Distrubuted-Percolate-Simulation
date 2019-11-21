/**
 * @Author: B159973
 * @Date:	15/10/2019
 * @Course: Programming Skills - 2019
 * @University of Edinburgh
*/
#ifndef ARRALOC_H
#define	ARRALOC_H

/***************************************************************************//**
* Provided by the University of Edinburgh:
*  ~arralloc.  Allocate a psuedo array of any dimensionality and type with   
*  specified size for each dimension.  Each dimension is	 	      
*  an array of pointers, and the actual data is laid out in standard 'c'     
*  fashion ie last index varies most rapidly.  All storage is got in one     
*  block, so to free whole array, just free the pointer array.               
*  array = (double***) arralloc(sizeof(double), 3, 10, 12, 5);		      
*******************************************************************************/
void *arralloc(size_t size, int ndim, ...);


#endif