#include <time.h>
#include <float.h>
#include <mpi.h>
#include <stdio.h>
#include "timer.h"


#define TIMERS 2

struct timer_struct {
  double          t_start;
  double          t_sum;
  double          t_elapsed;
  unsigned int    active;
};


static struct timer_struct timer[TIMERS];

static const char * timer_name[] = {"Total Time","Update Time"};

double find_min(const double a, const double b) {
    return ((a < b) ? a : b);
}

double find_max(const double a, const double b) {
    return ((a > b) ? a : b);
}


int TIMER_init() {

  int n;
  for (n = 0; n < TIMERS; n++) {
    timer[n].t_start  = 0.0;
    timer[n].t_sum  = 0.0;
    timer[n].t_elapsed  = 0.0;
    timer[n].active = 0;
  }

  return 0;
}


/****************************************************************************
 *
 *  TIMER_start
 *
 *  Start timer for the specified timer.
 *
 ****************************************************************************/

void TIMER_start(const int t_id) {

  timer[t_id].t_start = MPI_Wtime();
  timer[t_id].active  = 1;
  return;
}


/****************************************************************************
 *
 *  TIMER_stop_timer
 *
 *  Stop the specified timer and add the elapsed time to the total.
 *
 ****************************************************************************/

void TIMER_stop(const int t_id) {

  double t_elapse;

  if (timer[t_id].active) {

    t_elapse = MPI_Wtime() - timer[t_id].t_start;

    timer[t_id].t_sum += t_elapse;
    timer[t_id].t_elapsed = t_elapse;

    timer[t_id].active = 0;
  }

  return;
}

/*****************************************************************************
 *
 *  TIMER_statistics
 *
 *  Print a digestable overview of the time statistics.
 *
 *****************************************************************************/

void TIMER_dump( MPI_Comm comm, int rank, int size,int steps) {

  int    n;
  double t_elapsed, t_min, t_max, t_avg, t_step;

  for (n = 0; n < TIMERS; n++) {
      if ( timer[n].active == 0 ) {

          t_elapsed = timer[n].t_elapsed;
          t_avg = timer[n].t_sum;
          t_min = t_elapsed;
          t_max = t_elapsed;
          
          MPI_Reduce(&(timer[n].t_sum), &t_avg, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
          MPI_Reduce(&(timer[n].t_elapsed), &t_min, 1, MPI_DOUBLE, MPI_MIN, 0, comm);
          MPI_Reduce(&(timer[n].t_elapsed), &t_max, 1, MPI_DOUBLE, MPI_MAX, 0, comm);

          t_avg /= size;
          t_step= (t_max/(double)steps);
          printf("RANK  %d, %.20s MIN: %2.3f MAX: %2.3f AVG: %2.3f STEP: %2.5f\n", rank, timer_name[n], t_min, t_max, t_avg,t_step);

      }
  }

  return;
}