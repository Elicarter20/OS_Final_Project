#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int amma = syscall(317);
         printf("System call sys_hello returned %ld\n", amma);
	
         return 0;
}

//Does hello world syscall at 317
//Other syscalls are being added