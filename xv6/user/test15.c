#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_count should return 0 if no one is referencing the page
int main()
{
	void *ptr;
	int n;
	int i;

	for(i=0; i<4; i++)
	{
		n = shmem_count(i);
		if(n != 0)
		{
			INFO();
			printf(1, "TEST FAILED");
			exit();
		}
	}
	int pid = fork();
	if(pid < 0)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	else if (pid == 0)
	{
		for(i=0; i<4; i++)
		{
			ptr = shmem_access(i);
			if(ptr == NULL)
			{
				INFO();
				printf(1, "TEST FAILED");
				exit();
			}
		}
		exit();
	}
	else
	{
		wait();
		for(i=0; i<4; i++)
		{
			n = shmem_count(i);
			if(n != 0)
			{
				INFO();
				printf(1, "TEST FAILED");
				exit();
			}
		}
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
