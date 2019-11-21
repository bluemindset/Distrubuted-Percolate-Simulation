/**
 * @Author: B159973
 * @Date:   15/10/2019
 * @Course: Programming Skills - 2019
 * @University of Edinburgh
*/
/*========================== Library Files ===========================*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "arralloc.h"
#include "configuration.h"
/*====================================================================*/

void set_config(configure *con, int L, float rho,int seed, char *perc_file, int max_clusters)
{
    con->L = L;
    con->rho = rho;
    con->seed = seed;
   	con->allowed_squares = 0;
    con->max_clusters = max_clusters;
    con->pgm_filename = strdup(perc_file);
}