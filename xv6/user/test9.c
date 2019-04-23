#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// make sure shared pages are not deallocated when no process references them.
int main()
{
	char *ptr;
	int i;
	char arr[8] = "COP4610";
	int pid = fork();
	if(pid < 0)
	{
		INFO();	
		printf(1, "TEST FAILED");
	}
	else if (pid == 0)
	{
		ptr = shmem_access(3);
		if(ptr == NULL)
  		{
			INFO();	
			printf(1, "TEST FAILED");
  		}
		for(i=0; i<7; i++)
			*(ptr+i) = arr[i];
		exit();
	}
	else
	{
		wait();
		ptr = shmem_access(3);
		if(ptr == NULL)
  		{
			INFO();	
			printf(1, "TEST FAILED");
  		}
		for(i=0; i<7; i++)
		{
			if(*(ptr+i) != arr[i])
  			{
				INFO();	
				printf(1, "TEST FAILED");
  			}
		}
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
