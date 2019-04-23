#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// Make sure pointers frome shared pages can be successfully passed to system calls.
int main()
{
	char *ptr;
	int i;
	ptr = shmem_access(3);
	if(ptr == NULL)
	{
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	char arr[4] = "tmp";
	for(i=0; i<4; i++)
		*(ptr+i) = arr[i];
	// argstr
	int fd = open(ptr, O_WRONLY|O_CREATE);
	if(fd == -1)
	{
		printf(1, "open system call failed to take a string from within a shared page\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	//argptr
	int n = write(fd, ptr, 10);
	if(n == -1)
	{
		printf(1, "write system call failed to take a pointer from within a shared page.\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	// making sure invalid strings are still caught
	int fd2 = open((char *)(USERTOP/2), O_WRONLY|O_CREATE);
	if(fd2 != -1)
	{
		printf(1, "write system call successfully accepted an ivalid string\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	// making sure invalid pointers are still caught
	n = write(fd, (char *)(USERTOP/2), 10);
	if(n != -1)
	{
		printf(1, "write system call successfully accepted an ivalid pointer\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	// make sure edge case is checked.
	n = write(fd, (char *)(ptr + 4094), 10);
	if(n != -1)
	{
		printf(1, "write system call successfully accepted an overflowing pointer in a shared page\n");
		INFO();
		printf(1, "TEST FAILED");
		exit();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
