/**
 * @Author: B159973
 * @Date: 26/11/2019
 * @Course: MPP - 2019
 * @University of Edinburgh
*/

/*========================== Library Files ===========================*/
#include <time.h>
#include <float.h>
#include <mpi.h>
#include <stdio.h>
#include "timer.h"
/*====================================================================*/



struct timer_s
{
    double          _start;
    double          _sum;
    double          _elapsed;
    unsigned int    alive;
};

static struct timer_s timer[NUM_TIMERS];

static const char *timer_name[] = {"Total Time", "Update Time"};


int t_init()
{
    int n;
    for (n = 0; n < NUM_TIMERS; n++)
    {
        timer[n]._start  = 0.0;
        timer[n]._sum  = 0.0;
        timer[n]._elapsed  = 0.0;
        timer[n].alive = 0;
    }

    return 0;
}

void t_start(const int t_id)
{
    timer[t_id]._start = MPI_Wtime();
    timer[t_id].alive  = 1;
    return;
}

void t_stop(const int t_id)
{

    double t_elapse;

    if (timer[t_id].alive)
    {
        t_elapse = MPI_Wtime() - timer[t_id]._start;
        timer[t_id]._sum += t_elapse;
        timer[t_id]._elapsed = t_elapse;
        timer[t_id].alive = 0;
    }

    return;
}

void t_dump( MPI_Comm comm, int rank, int size, int steps)
{
    int    n;
    double _elapsed, t_min, t_max, t_avg, t_step;

    for (n = 0; n < NUM_TIMERS; n++)
    {
        if ( timer[n].alive == 0 )
        {
            _elapsed = timer[n]._elapsed;
            t_avg = timer[n]._sum;
            t_min = _elapsed;
            t_max = _elapsed;

            MPI_Reduce(&(timer[n]._sum), &t_avg, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
            MPI_Reduce(&(timer[n]._elapsed), &t_min, 1, MPI_DOUBLE, MPI_MIN, 0, comm);
            MPI_Reduce(&(timer[n]._elapsed), &t_max, 1, MPI_DOUBLE, MPI_MAX, 0, comm);

            t_avg /= size;
            t_step = (t_max / (double)steps);
            printf("RANK  %d, %.20s MIN: %2.3f MAX: %2.3f AVG: %2.3f STEP: %2.5f\n", rank, timer_name[n], t_min, t_max, t_avg, t_step);

        }
    }
    return;
}

double find_min(const double a, const double b)
{
    if(a < b)
        return a;
    else
        return b;
}

double find_max(const double a, const double b)
{
    if(a < b)
        return a;
    else
        return b;
}