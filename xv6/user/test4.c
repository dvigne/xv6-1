#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_access is called once in the parent process. It is then called again after fork in child process. The address received should be the same as the parent process.
int shmem_access_double_call_fork()
{
	void* ptr;
	ptr = shmem_access(3);
	//printf(1,"parent ptr = %d\n", (int) ptr);
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
	else if (pid == 0)
	{
		void *ptr2;
		ptr2 = shmem_access(3);
		//printf(1,"child ptr2 = %d\n", (int) ptr2);
		if(ptr2 == NULL)
		{
			INFO();
			printf(1, "TEST FAILED");
			exit();
		}
		if(ptr != ptr2)
		{
	   		 INFO();
	   		 printf(1, "TEST FAILED");
			 exit();
		}
		exit();
	}
	else
		wait();
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
