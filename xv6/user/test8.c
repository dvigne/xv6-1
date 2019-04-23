#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// sbrk should not allocate and go past shared memory

int main()
{
	void *ptr;
	ptr = shmem_access(0);
	if(ptr == NULL)
  	{
		INFO();	
		printf(1, "TEST FAILED");
		exit();
  	}
	void *ptr2;
	while (1)
	{
		ptr2 = sbrk(1024);
		if(ptr2 >= ptr && ptr2 != (char *) -1)
		{
			INFO();	
			printf(1, "TEST FAILED");
			exit();
		}
		if(ptr2 == (char *) -1)
			break;
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
