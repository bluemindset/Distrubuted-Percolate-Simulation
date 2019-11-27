/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef ALLOCS_H
#define	ALLOCS_H

/***************************************************************************//**
 * Allocate a string in memory by calling the build-in function malloc().
 * If the allocation of the memory fails then return an error message
 * and exit the program unsuccessfully.
 *
 * @param p_str: A pointer to a pointer to a 1 byte character memory location.
 *				 This double pointer is used to allocate an array of
 *				 characters (a string) and point to that array of characters.
 * @param size:	 The size of the dynamic array to allocate. This parameter will
 *				 multiply with the character type byte size, which
 *				 is 1 byte.
 * @return:		 Nothing
 ******************************************************************************/
void alloc_str(char **p_str, const int size);
/***************************************************************************//**
 * If the allocation of the memory fails then return an error message
 * and exit the program unsuccessfully.
 *
 * @param p_int: A pointer to a pointer to a 4 byte integer memory location.
 *				 This double pointer is used to allocate an array of
 *				 integers and point to that array of integers.
 * @return:		 Nothing
 *
 ******************************************************************************/
void check_int_list(int *p_int);


/***************************************************************************//**
 * If the allocation of the memory fails then return an error message
 * and exit the program unsuccessfully.
 *
 * @param p_map: A pointer to a pointer to a pointer on a 4 byte integer
 * 				 memory location.
 *				 This double pointer is used to allocate a 2D dynamic array of
 *				 integers.
 * @return:		 Nothing
 ******************************************************************************/
void check_map(int **p_map);

/***************************************************************************//**
 * Deallocate successfully any pointers that are 
 *
 * @param p_mem ...: The pointer to be free from memory.
 * @return:		 Nothing
 ******************************************************************************/
void dealloc(void *p_mem, ...);

#endif