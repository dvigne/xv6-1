#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int main(void) {
  printf(1, "test getpids\n", getpid());
  exit();
}
