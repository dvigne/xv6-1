#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_access should fail if the entire address space is used.
int main()
{
	void *ptr;
	while(1)
	{
		ptr = sbrk(1024);
		if(ptr == (char *) -1)
			break;
	}
	ptr = shmem_access(0);
	if(ptr != NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
