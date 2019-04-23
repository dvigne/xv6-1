#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// Make sure shared pages are readable and writable
int shemem_access_readable_writable()
{
	char *ptr;
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
		char c = 'c';
		ptr[100] = c;	// write
		char d = *(ptr+100); // read
		if (c != d)
		{
	   		INFO();
	   		printf(1, "TEST FAILED");
			exit();
		}
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
