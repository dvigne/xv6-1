#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int intinuse[NPROC];   // whether this slot of the process table is in use (1 or 0)
  int inttickets[NPROC]; // the number of tickets this process
  int hasintpid[NPROC];     // the PID of each process
  int intticks[NPROC];   // the number of ticks each process has accumulated
  int intstrides[NPROC];
};

#endif // _PSTAT_H_
