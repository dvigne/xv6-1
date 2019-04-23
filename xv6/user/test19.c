#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// Exec should decrement count for shared pages. Parent accesses a shared page, then it forks. Child performs exec to start a new program. In the new program, the count for the shared page should be 1.
char *args3[] = {"echo_three", 0};
int main()
{
	void* ptr;
	int n;
	int i;

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
	for(i=0; i<4; i++)
	{
		n = shmem_count(i);
		if(n != 1)
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
			n = shmem_count(i);
			if(n != 2)
			{
				INFO();
				printf(1, "TEST FAILED");
				exit();
			}
		}
		exec("echo_three", args3);
		printf(1, "exec failed!\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	else
		wait();
	exit();
}
