#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// A newly exec-ed program should reallocate virtual pages if shmeme_access is called.
char *args2[] = { "echo_two", 0 };
int main()
{
	void *ptr;
	int i;
	for(i=0; i<4; i++)
	{
		ptr = shmem_access(i);
		//printf(1, "i = %d\n", i);
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
		INFO();	
		printf(1, "TEST FAILED");
		exit();
	}
	else if (pid == 0)
	{
		exec("echo_two", args2);
		printf(1, "exec failed!\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	else
		wait();
	exit();
}
