#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "syscall.h"

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// Determine if an invalid index can be passed to shmem_access()
int main()
{
	void* ptr;
	ptr = (void*) (shmem_access(-1));
	if(ptr != NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	ptr = (shmem_access(-400));
	if(ptr != NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	ptr = (shmem_access(4));
	if(ptr != NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	ptr = (shmem_access(100));
	if(ptr != NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
