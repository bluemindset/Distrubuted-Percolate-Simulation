/**
 * @Author: B159973
 * @Date:   26/11/2019
 * @Course: MPP - 2019
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