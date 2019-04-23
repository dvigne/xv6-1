#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// One process writes and another process reads
int main()
{
	char *ptr;
	int i;
	char arr[8] = "COP4610";
	ptr = shmem_access(2);
	if(ptr == NULL)
	{
		INFO();	
		printf(1, "TEST FAILED");
		exit();
	}
	int pid = fork();
	if(pid < 0)
	{
		INFO();	
		printf(1, "TEST FAILED");
		exit();
	}
	else if(pid == 0)
	{
		sleep(20);
		for(i=0; i<7; i++)
		{
			if(*(ptr+i) != arr[i])
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
		for(i=0; i<7; i++)
		{
			*(ptr+i) = arr[i];
		}
		wait();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
