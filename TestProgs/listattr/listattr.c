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

	listattr Program

	Parameters: "attrname" attribute name (char*)
		     list of "files" to list attributes for (char*)

	prints out a list of attributes for file param(s)

	returns 0 upon successful syscalls for each file
	returns -1 when no arguments are passed
	returns -1 when syscall fails
*/

int main(int argc, char *argv[])
{
	int flag = 1; //flag for LISTALL
	
	//Gets arguments
	char* attrname;
	attrname = argv[1];//gets first parameter from cmmd line


	if (attrname == NULL)//check if passed in attribute arguments
	{
		printf("No attributes argument passed\n");
		return -1;
	}
	//checks for LISTALL flag
	if (strcmp(attrname, "LISTALL") == 0)//flags for LISTALL option
		flag = 0;

	//logic for listing all attributes
	if(flag == 0)
	{	
		long int ret = -999;
		char filepath[128];//space for filepath
		char buffer[128];//space for buffer (attrvalue returned by syscall)
		int i = 2;	//skips first and second cmmd line arguments
		for (; i < argc; i++)//loops through list of files
		{
			getcwd(filepath, sizeof(filepath));	//creates file path
			if (filepath==NULL)		//constraints on filepath
			{
				printf("\nPath Too Big");
				continue;
			}		

			strcat(filepath, "/");
			strcat(filepath, argv[i]);
			//builds absolute filepath string

			ret = syscall(357, filepath, buffer, 128 + sizeof(argv[i]) + 1);
			//get attributes list syscall	
			
			if (ret==-1)//check if successful syscall
			{
				printf("Get Attribute List Syscall failed\n");			
				return -1;
			}
		
			long int rec;//for returning syscall
			char xbuff[128];//buffer for get attribute syscalls

			char* name;//everything before a colon
			char* bname = buffer;//everything after a colon (being stripped down)
			while (ret > 0 )//looping through attrname list
			{
				name = strtok(bname, ":");//strips before colon
				if(!name)
					break;		//if NULL breaks
				bname = strrchr(buffer, ":");//moves buffer forward past colon
				rec = syscall(356, filepath, name, xbuff, 128 + sizeof(argv[i]) + 1);
				//get attribute syscall

				if (ret==-1)//check if successful syscall
				{
					printf("Get Attribute List Syscall failed\n");			
					return -1;
				}
				printf("%s %s=%s\n", argv[i], name, xbuff);//prints return values of get attr
			}
			
		}
		if (ret == -999)//checks if list of files was passed as argument
		{
			printf("No file arguments passed\n");
			return -1;
		}
		return 0;
	}	

	//looping through file arguments
	long int ret = -2;		
	char filepath[128];//space for filepath
	char buffer[128];//space for buffer (returned by get attribute syscall)
	int i = 2;		//skips first two cmd line arugments
	for (; i < argc; i++)//loops through list of files calling get attribute syscall for each
	{
		getcwd(filepath, sizeof(filepath));	//builds file path
		if (filepath==NULL)		//constraint on filepath
		{
			printf("\nPath Too Big");
			continue;
		}		
		strcat(filepath, "/");
		strcat(filepath, argv[i]);//builds absolute filepath string
		printf("%s\n", argv[i]);
		ret = syscall(356, filepath, attrname, buffer, 128 + sizeof(argv[i]) + 1);		
		//get attribute syscall
		if (ret==-1)//failure case
		{
			printf("Get Attribute Syscall Failed\n");			
			return -1;
		}
		printf("%s %s=%s\n", argv[i], attrname, buffer);//prints formatted output
	}	
	if (ret == -2)//failure if no file arguments passed
	{
		printf("No file arguments passed\n");
		return -1;
	}
	return 0;
}

