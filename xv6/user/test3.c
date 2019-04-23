#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


int main()
{
	void *ptr;
	void *ptr2;
	ptr = shmem_access(3);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	ptr2 = shmem_access(3);
	if(ptr == NULL)
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
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
