#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_access return value should be one of 4 pages
// The address should be the first virtual page for the first shared page, the second virtual page for the second shared page, and so on.
int main()
{
	void* ptr;
	ptr = shmem_access(2);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	if(((int) ptr) != USERTOP - PGSIZE*1)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}

	ptr = shmem_access(3);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	if(((int) ptr) != USERTOP - PGSIZE*2)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}

	ptr = shmem_access(0);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
	}
	if(((int) ptr) != USERTOP - PGSIZE*3)
	{
		INFO();
		printf(1, "TEST FAILED");
	}

	ptr = shmem_access(1);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
	}
	if(((int) ptr) != USERTOP - PGSIZE*4)
	{
	   INFO();
	   printf(1, "TEST FAILED");
	}

	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
