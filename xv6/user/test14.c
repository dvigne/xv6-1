#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// shmem_count should return 0 if no one is referencing the page
int main()
{
	int n;
	int i;

	for(i=0; i<4; i++)
	{
		n = shmem_count(i);
		if(n != 0)
		{
			INFO();
			printf(1, "TEST FAILED");
			exit();
		}
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
