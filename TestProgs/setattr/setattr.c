#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <dirent.h>
#include <string.h>

/*

	setattr Program

	Parameters: "attrname=attrvalue" pair (char*)
		     list of "files" to add attribute to (char*)


	returns 0 upon successful syscalls for each file
	returns -1 when insufficient arguments are passed
	returns -1 when syscall fails
*/

int main(int argc, char *argv[])
{
	//strips the name value pair
	char* attributes;
	attributes = argv[1];//first argument is name=value pair

	if (attributes == NULL)//checks if valid parameters
	{
		printf("No attributes argument passed\n");
		return -1;
	}

	char* attrvalue;
	attrvalue = strrchr(attributes, '=');
	if(!attrvalue)
	{
		printf("Invalid args");
		return -1;
    	
	}
	attrvalue += sizeof(char);//gets string before equals sign
	
	char* attrname;
	attrname = strtok(attributes, "=");
	if(!attrname)
	{
		printf("Invalid args");
		return -1;
    	
	}//gets string before equals sign


	//looping through file arguments
	//creates filepaths and calls syscall 356 (add attribute)
	long int ret = -999;
	char filepath[128];//128 bytes max
	int i = 2;
	for (; i < argc; i++)
	{
		getcwd(filepath, sizeof(filepath));//creates filepath from file
		if (filepath==NULL)//constraints on filepath
		{
			printf("\nPath Too Big");
			continue;
		}		

		strcat(filepath, "/");
		strcat(filepath, argv[i]);//concatenates absolute filepath

		ret = syscall(355, filepath, attrname, attrvalue, 128 + sizeof(argv[i]) + 1);
		//set attribute syscall
		if (ret==-1)
		{
			
			//ret = syscall(358, filepath, attrname);
			//if syscall fails, remove offending attribute
			return -1;
		}

	}
	if (ret == -999)//validates parameters
	{
		printf("No file arguments passed\n");
		return -1;
	}
	return 0;
}

