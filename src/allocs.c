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
#include <stdarg.h>
#include "configuration.h"
#include "arralloc.h"
#include "allocs.h"
/*====================================================================*/

void alloc_str(char **p_str, const int size)
{
    *p_str = (char *) malloc(sizeof(char) * size);
    if (!(*p_str))
    {
        perror("Memory for string was not allocated. Program exit!");
        exit(EXIT_FAILURE);
    }
}

void check_map(int **p_map)
{
    if (!(p_map))
    {
        perror("Memory for map was not allocated. Program exit!");
        exit(EXIT_FAILURE);
    }
}

void check_int_list(int *p_int)
{
    if (!(p_int))
    {
        perror("Memory for map was not allocated. Program exit!");
        exit(EXIT_FAILURE);
    }
}



void dealloc(void *start_p, ...)
{
    va_list args;
    void *p;

    va_start(args, start_p); /*Fetch the first pointer in the variadic argument list*/
    for (p = start_p; p != NULL; p = va_arg(args, void *))   /*Free them all*/
    {
        free(p);
    }
    va_end(args);
}