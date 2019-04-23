#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// A newly exec-ed program should not have access to shared pages when it begins.
char *args[] = { "echo_one", 0 };
int main()
{
	void *ptr;
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
	int pid = fork();
	if(pid < 0)
	{
		printf(1, "TEST FAILED");
		exit();
	}
	else if (pid == 0)
	{
		printf(1, "Attempt to access shared pages that were not requested should result in a trap.\n");
		exec("echo_one", args);
		printf(1, "exec failed!\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	else
		wait();
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
