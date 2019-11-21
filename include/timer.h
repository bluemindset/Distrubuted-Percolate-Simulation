#ifndef TIME_H
#define TIME_H

int TIMER_init();
void TIMER_start(const int);
void TIMER_stop(const int);
void TIMER_dump( MPI_Comm comm, int rank, int size,int steps);

enum timer_id {TIMER_TOTAL = 0,
	       		TIMER_UPDATE =1
};

#endif