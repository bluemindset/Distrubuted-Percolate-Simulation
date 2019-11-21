//
// Created by blue on 21/11/2019.
//

#ifndef PERCWRITE_H
#define PERCWRITE_H

/*  Write the map to the file "map.pgm", displaying only the very
*  largest cluster (or multiple clusters if exactly the same size).
*  If the last argument here was 2, it would display the largest 2
*  clusters etc.
*/
void percwrite(char *percfile, int **map, int l, int ncluster);


#endif
