/**
 * @Author: B159973
 * @Date:	26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/

#ifndef TIME_H
#define TIME_H

/***************************************************************************//**
 * Number of timers.
 ******************************************************************************/
#define NUM_TIMERS 2
/***************************************************************************//**
 * Initialize all the timers to be zero.
 ******************************************************************************/
int t_init();
/***************************************************************************//**
* Start the selected timer, either TOTAL or UPDATE (check report)
 ******************************************************************************/
void t_start(const int);
/***************************************************************************//**
* Stop the selected timer, either TOTAL or UPDATE (check report)
 ******************************************************************************/
void t_stop(const int);
/***************************************************************************//**
* Dump all the timings into the screen output
* @comm  		The communicator to use for selecting the timers.
* @rank			The rank of the process to dump its timing.
* @size 		Number of all the processes.
* @steps		The number of steps of the update loop. 
 ******************************************************************************/
void t_dump( MPI_Comm comm, int rank, int size,int steps);

/***************************************************************************//**
 * Timers for measuring the whole program time and for the update section 
 ******************************************************************************/
enum timer_id {TIMER_TOTAL = 0,
	       		TIMER_UPDATE =1
};

#endif