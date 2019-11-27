/**
 * @Author: B159973
 * @Date:   26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/
#ifndef MAIN_H
#define MAIN_H


/***************************************************************************//**
 * Dimensions used for finding neighbors
*******************************************************************************/
#define ZERO_DIM 0
#define FIRST_DIM 1
/***************************************************************************//**
 * Master Rank
*******************************************************************************/
#define MASTER 0
/***************************************************************************//**
 * 2D De-composition Domain
*******************************************************************************/
#define N_DIMS 2
/***************************************************************************//**
 * Printing frequency of the steps and average
*******************************************************************************/
#define PRINT_FREQ 100
/***************************************************************************//**
 * Exchange only two rows and two columns
*******************************************************************************/
#define SHALLOW_HALO 4

typedef struct
{
    /*start width boundary of process */
    int sW;
    /*end width boundary of process */
    int eW;
    /*start height boundary of process */
    int sH;
    /*end height boundary of process */
    int eH;

    int deltaH;
    int deltaW;

} bounds;



/***************************************************************************//**
* Takes a single integer in the range
*       0 <= ijkl <= 900 000 000
* and produces the four smaller integers needed for rstart  
*******************************************************************************/
void rinit(int ijkl);
/***************************************************************************//**
* C version of Marsaglia's UNI random number generator
*******************************************************************************/
float uni(void);

#endif