/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef PERCWRITE_H
#define PERCWRITE_H

/*  Write the map to the file "map.pgm", displaying only the very
*  largest cluster (or multiple clusters if exactly the same size).
*  If the last argument here was 2, it would display the largest 2
*  clusters etc.
*  @percfile	The file to write the produced pgm file.
*  @map 		The simulated grid
*  @l 			The problem size
*  @ncluster	Number of clusters to be printed
*/
void percwrite(char *percfile, int **map, int l, int ncluster);


#endif
