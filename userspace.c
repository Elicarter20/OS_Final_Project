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
	//creates file directory name

	struct stat s = {0};
	if (stat(new_dir, &s) == -1)
	{
		mkdir(new_dir, 0777);
        	//printf("test \n");
	}
	//creates directory
	
	strcat(new_dir, "/");
	strcat(new_dir, attrname);
	printf("%s\n", new_dir);
	//creates file path
	
	FILE* file = fopen(new_dir, "w");
	if (file != NULL)
	{
		fputs(attrvalue, file);
		fclose(file);
		//writes file
		
		return 0;
	}
	return -1;
	
}


long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{
	
//check if absoulte path to file
	if (filename[0] != '/')
	{
		printf("Not absolute\n");
		return -1;
	}

	buf = (char*) malloc(bufsize);
	//allocates buffer in memory


	char* attr_dir  = (char*) malloc(sizeof(filename) + 100);
	//strcpy(new_dir, ".");//prepend "."
	
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	strcat(attr_dir, attrname);
	//creates filepath to read from


	FILE* attr_file = fopen(attr_dir, "rb");
	if (attr_file != NULL)
	{
		fread(buf, sizeof(char), bufsize, attr_file);
		//printf("%s\n", buf);
		fclose(attr_file);
		//reads from file	
		return sizeof(buf);
	}
	return -1;
}
/*This call gets the value of the attribute named “attrname” attached to the file named “filename”. The value is stored in the buf pointer which must have at least “bufsize” by
tes of storage. 
The filename must be an absolute path to the file. The strings should be null terminated, and reasonable limits should be enforced on all strings. The return value should be the number of bytes returned  for success, or a negative error value.
*/




long cs401_get_attribute_names(char *filename, char *buf, int bufsize)
{
	if (filename[0] != '/')
	{
		printf("Not absolute\n");
		return -1;
	}
	//checks if absolute path to file
	

	buf = (char*) malloc(bufsize);
	//allocates buffer in memory


	char* attr_dir  = (char*) malloc(sizeof(filename) + 100);
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	//creates filepath to read from

	DIR *dir;
	struct dirent *ent;
	if((dir = opendir(attr_dir)) != NULL)
	{
		while((ent = readdir (dir)) != NULL)
		{	
			if(ent->d_name == "..")
				printf("F");
			if (ent->d_name == ".")
				continue;
			strcat(buf, ent->d_name);
			strcat(buf, ":");
			printf("%s\n", buf);
		}
		closedir(dir);
		return sizeof(buf);
	}
	else
	{
		/*could not open directory*/
		perror("attr dir does not exist");
		return -1;
	}
	//traverses directory and builds buf with colon seperated files
	
	
	
}
/* gets all of the names of attributes that are set for the file “filename”. The list of attributes is returned as a “:” (colon) separated list in the “buf” string. The buf pointer  must have at least “bufsize” bytes of storage. The filename must be an absolute path to  the file. The strings should be null terminated, and reasonable limits should be e
*/
long cs401_remove_attribute(char *filename, char *attrname)
{
	if (filename[0] != '/')
	{
		printf("Not absolute\n");
		return -1;
	}
	//checks if absolute path to file
	
	char* attr_dir  = (char*) malloc(sizeof(filename) + 100);
	char* attr_file = (char*) malloc(sizeof(filename)+100);
	
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	strcpy(attr_file, attr_dir);
	strcat(attr_file, attrname);
	//creates filepaths to read from
	
	FILE* file = fopen(attr_file, "r");
	DIR * dir;
	struct dirent *ent;
	int n = 0;
	if (file != NULL)//checks if file exists
	{
		printf("\n Removing: %s\n", attr_file);
		remove(attr_file);
		if((dir = opendir(attr_dir)) != NULL)
		{
			while((ent=readdir(dir)) != NULL)
			{
				if(++n> 2)
				{
					break;
				}
			}
			closedir(dir);
			if(n<=2)
			{
				printf("\n Removing empty attr dir\n");
				rmdir(attr_dir);
			}
			return 0;
		}
	}
	else if (ENOENT == errno)
	{
		printf("\n File/Directory doesnt exist\n");
		return -1;
	}
	//something else went wrong
	return -1;
	
	//remove file
	//if dir is empty remove 	
}

/*This call removes the specified attribute from the file. It should remove the file that was created in the attribute directory. If this was the last user attribute for this file the attribute directory should also be removed. Note, this will require some locks as some other process may be adding a new attribute at the same time, and should not fail because the directory was removed from under it. The return value should be 0 for success, or a negative error value. This system call can be used with the cs401_get_attribute_names() call to remove ‘all’ of the attributes attached to a specific file.
*/



int hello(char* aint)
{
	return 2;
}
int main()//char* argv[])
{
	char* file = "/home/oscreader/Desktop/FileAttributes/OS_Final_Project/userspace.c";
	char * a = "Creator";
	char * b = "Bloom";
	char* ret = "";


         long int amma = syscall(3111);
         printf("System call sys_hello returned %ld\n", amma);
	long int ammo = syscall(356);
         printf("System call 356 returned %ld\n", ammo);
	//long i = cs401_set_attribute(file, "Date", "Dog", sizeof(file));
	//long k = cs401_set_attribute(file, "Maker", "Me", sizeof(file));
	//long ki =  cs401_get_attribute(file, "Creator", ret, 100);    
	//long ik =  cs401_get_attribute(file, "Maker", ret, 100);     
	//long joke = cs401_get_attribute_names(file, ret, 100);
	//long ikea = cs401_remove_attribute(file, "Maker");
	//long ike = cs401_remove_attribute(file, "Date");
//	long ik = cs401_remove_attribute(file, "Boss");
	//printf("%d\n", ki);
	return 0;
}



//Does hello world syscall at 317
//Other syscalls are being added
