/**
 * @Author: B159973
 * @Date:   26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
/*========================== Library Files ===========================*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "validation.h"
#include "allocs.h"
#include "configuration.h"
#include "userInput.h"
/*====================================================================*/

void get_input(configure *con, int argc, char **argv)
{
    char *L = NULL;
    char *rho = NULL;
    char *seed = NULL;
    char *pgm_file = NULL;
    char *max_clusters = NULL;
    alloc_str(&L, MAX_L);
    alloc_str(&seed, MAX_RANDOM_SEED_SZ);
    alloc_str(&rho, MAX_RHO);
    alloc_str(&pgm_file, MAX_FILENAME);
    alloc_str(&max_clusters, MAX_L * MAX_L);
    int par; /*The parameter which the option arguments will return from the command line arguments*/
    while((par = getopt(argc, argv, "l:s:m:r:p:h")) != -1) /* For each argument in the option argument list*/
    {
        switch(par)
        {
        case 'l':/*Check for a valid size*/
            if (!(valid_number(optarg) && valid_size(optarg, MAX_L)))
            {
                printf("Please enter correct size of the cluster.It must be a positive for up to %d digits.\n", MAX_L);
                exit(EXIT_FAILURE);
            }
            L = strdup(optarg);
            break;

        case 's':/*Check for a valid seed*/
            if (!( valid_number(optarg) && valid_size(optarg, MAX_RANDOM_SEED_SZ)))
            {
                printf("\nPlease enter a correct seed.It must a number between 0 and %d digits, between values 0 and 1.\n", MAX_RANDOM_SEED);
                exit(EXIT_FAILURE);
            }
            seed = strdup(optarg);
            break;

        case 'm':/*Check for a valid max cluster*/
            if (!(valid_number(optarg) && valid_size(optarg, MAX_L * MAX_L)))
            {
                printf("\nPlease correct number of clusters. It must be a positive from 1 to L*L.\n");
                exit(EXIT_FAILURE);
            }
            max_clusters = strdup(optarg);
            break;

        case 'r':/*Check for a valid rho file*/
            if (!( valid_fraction(optarg) && valid_size(optarg, MAX_RHO) && ( ((atof(optarg)) <= 1.0)) ))
            {
                printf("\nPlease enter a correct density.It must be fraction up to %d digits, between values 0 and 1.\n", MAX_RHO);
                exit(EXIT_FAILURE);
            }
            rho = strdup(optarg);
            break;

        case 'p':/*Check for a valid pgm file*/
            if ( !(valid_filename(optarg, PGM_TYPE) && valid_size(optarg, MAX_FILENAME)) )
            {
                printf("\nPlease enter filename for the percolate to output the map image file.It must have a data type of .pgm\n");
                exit(EXIT_FAILURE);
            }
            pgm_file = strdup(optarg);
            break;

        case 'h': /*Help command*/
            printf("\nPlease enter correct values for the problem to run:\n");
            printf("-l @num: For the map width and height\n");
            printf("-r @rho: For the density rho.\n");
            printf("-m @max clusters: For the The maximum clusters the program will output.\n");
            printf("-s @seed: For the seed for the number generator.\n");
            printf("-d @DAT filename: For the output .dat file. Must finish in .dat\n");
            printf("-p @PGM filename: For the output .pgm file.Must finish in .pgm\n\n");
            exit(EXIT_FAILURE);
            break;

        default:
            printf("You have entered a wrong paramessster. Please type -h for help.");
        }
    }

    if (argc != ARGC_SIZE) /*Check for the correct number of arguments*/
    {
        printf("Please enter correct amount of optameters. Please type -h for help.");
        exit(EXIT_FAILURE);
    }
    set_config(con, atoi(L), atof(rho), atoi(seed), pgm_file, atoi(max_clusters)); /*Set all the values in the configure structure*/
}


