#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#

long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{

	//check if absoulte path to file
	if (filename[0] != '/')
	{
		printf("Not absolute\n");
		return -1;
	}

	//reasonable check on size
	/*
	if (size > x)
	{
		printf("Too big\n");
		return -1;
	}
	*/
	

	char* new_dir = (char*) malloc(sizeof(filename) + 100);
	//strcpy(new_dir, ".");//prepend "."
	strcpy(new_dir, filename);	
	strcat(new_dir, "_attr\0");//null terminated string
	//printf("%s\n", new_dir);

	struct stat s = {0};
	if (stat(new_dir, &s) == -1)
	{
		mkdir(new_dir, 0777);
        	//printf("test \n");
	}
	
	FILE* file = fopen(attrname, "w");
	fprintf(file, attrvalue);
	fclose(file);

	//FILE* dir  = fopen(new_dir, "w");
	
	//fputs(attrname, dir);
	//fprintf(dir, attrname);
	//if (dir ==NULL)
	//{
	//	perror("fopen");
	//}

	
return 0;

	
	
}

int main()
{
	char* file = "/home/oscreader/Desktop/FileAttributes/OS_Final_Project/userspace.c";
	char * a = "Creator";
	char * b = "Bloom";
         long int amma = syscall(317);
         printf("System call sys_hello returned %ld\n", amma);
	long i = cs401_set_attribute(file, a, b, sizeof(file));
         return 0;
}



//Does hello world syscall at 317
//Other syscalls are being added
