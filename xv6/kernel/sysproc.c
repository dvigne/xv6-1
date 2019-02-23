#include "types.h"
#include "pstat.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

unsigned long numsys = 0;
extern struct pstat *pstattable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getreadcount(void)
{
  return numsys;
}

int
sys_settickets(void)
{
  int tickets;
  argint(0,&tickets);
  pstattable->inttickets[sys_getpid()] = tickets;
  pstattable->intstrides[sys_getpid()] = 10000 / tickets;
  if(pstattable->inttickets[sys_getpid()] == tickets){
    return 1;
  } else {
    return -1;
  }
  return 0;
}

int
sys_getpinfo(void)
{
  for(int i = 0; i < NPROC; i++){
    if(pstattable->intinuse[i] == 0)
      continue;
    cprintf("%d | %d | %d | %d | %d \n", pstattable->intinuse[i],
                  pstattable->inttickets[i], pstattable->hasintpid[i],
                  pstattable->intticks[i], pstattable->intstrides[i]);
  }
  return 1;
}
