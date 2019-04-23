#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


//invalid input test
int main()
{
	int n;
	n = shmem_count(-1);
	if(n != -1)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	n = shmem_count(-100);
	if(n != -1)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	n = shmem_count(4);
	if(n != -1)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	n = shmem_count(100);
	if(n != -1)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
