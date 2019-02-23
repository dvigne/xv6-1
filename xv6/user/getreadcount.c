#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int main(void) {
  printf(1, "There have been %d reads\n", getreadcount());
  exit();
}
