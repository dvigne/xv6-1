#include "types.h"
#include "user.h"

#define PGSIZE 4096
#define USERTOP 0xA0000

int main(int argc, char *argv[]) 
{
	int n;
	int i;
	for(i=0; i < 4; i++)
	{
		n = shmem_count(i);
		printf(1, "n = %d\n", n);
		if(n != 1)
			printf(1, "Test Failed!\n");
	}
	printf(1, "Test Passed!\n");
	exit();
}
