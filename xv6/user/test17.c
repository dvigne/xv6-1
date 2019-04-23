#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_count should return 1 after two access to the same page
int main()
{
	void *ptr;
	int n;
	int i;
	for(i=0; i < 4; i++)
	{
		ptr = shmem_access(i);
		if(ptr == NULL)
		{
			INFO();
			printf(1, "TEST FAILED");
		}
		ptr = shmem_access(i);
		if(ptr == NULL)
		{
			INFO();
			printf(1, "TEST FAILED");
		}
		n = shmem_count(i);
		if(n != 1)
		{
			INFO();
			printf(1, "TEST FAILED");
		}
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
