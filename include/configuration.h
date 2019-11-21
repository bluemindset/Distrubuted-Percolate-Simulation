/**
 * @Author: B159973
 * @Date:	15/10/2019
 * @Course: Programming Skills - 2019
 * @University of Edinburgh
*/
#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

/***************************************************************************//**
 * This data structure is used to store a lot of critical values regarding the
 * program. It basically provides the configuration for the program.
 * @ L:   	 			The width and height of the map. For example 5x5 map contains
 						25 squares.
 * @float rho:	 		The density ρ.
 * @seed:		 		The seed that is used to supply values to the random uniform function
 *				 		that  will be compared with density ρ.
 * @allowed_squares: 	The squares in the mapthat have a positive integer value.
 * @max_clusters: 		The maximum clusters the program will output,starting from the
 				  		largest one.
 * @dat_filename		The file name of the .dat type file.
 * @pgm_filename		The file name of the .pgm type file.
 ******************************************************************************/
typedef struct
{
    int L;
    float rho;
    int seed;
    int allowed_squares;
    int max_clusters;
    char *pgm_filename;
} configure;

/***************************************************************************//**
 * Assigns safely the arguments into the configuration structure.
 * @con 				The pointer that points to the configuration structure.The
 *						configuration structure is allocated in main.c .
 * @L:   	 			The width and height of the map. For example 5x5 map contains
 						25 squares.
 * @float rho:	 		The density ρ.
 * @seed:		 		The seed that is used to supply values to the random uniform function
 *				 		that  will be compared with density ρ.
 * @allowed_squares: 	The squares in the mapthat have a positive integer value.
 * @max_clusters: 		The maximum clusters the program will output,starting from the
 				  		largest one.
 * @dat_filename		The file name of the .dat type file.
 * @pgm_filename		The file name of the .pgm type file.
 ******************************************************************************/
void set_config(configure *con, int L, float rho, int seed, char *perc_file, int max_clusters);

#endif