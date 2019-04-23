#include "types.h"
#include "user.h"

#define PGSIZE 4096
#define USERTOP 0xA0000

// echo_one helper function.
int main(int argc, char *argv[])	// echo function called on exec
{
	char *ptr = (char *)(USERTOP - 4096);
	*ptr = 'c';
	exit();
}
