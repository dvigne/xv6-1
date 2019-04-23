#include "types.h"
#include "user.h"

#define PGSIZE 4096
#define USERTOP 0xA0000

int main(int argc, char *argv[])	// echo function called on exec
{
	char *ptr;
	int i;
	for(i=3; i>=0; i--)
	{
		ptr = shmem_access(i);
		if(ptr == NULL)
			printf(1, "Test Failed!\n");
		*ptr = 'c';
	}
	printf(1, "Test Passed!\n");
	exit();
}
