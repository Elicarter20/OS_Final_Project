#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/stddef.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/err.h>
#include <linux/dirent.h>
#include <linux/stddef.h>
#include <linux/time.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <asm/uaccess.h>
#include <asm/segment.h>
asmlinkage long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{
	printk("355: Set Attributes\n");

	//check if absoulte path to _file
	if (filename[0] != '/')
	{
		printk("Not absolute\n");
		return -1;
	}

	//reasonable check on size
	
	//creates _filepath for directory
	char* attr_dir = (char*) vmalloc(sizeof(filename) + 100);
	//strcpy(attr_dir, ".");//prepend "."
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr/\0");//null terminated string

	
	struct file *fp = (struct file *)NULL;
	fp = filp_open(attr_dir, O_DIRECTORY|O_CREAT, S_IRUSR);
	

	/*struct file *fp = struc
	struct vfs_stat s = {0};
	if (vfs_stat(attr_dir, &s) == -1)
	{
		vfs_mkdir(attr_dir, 0777);
        	//printk("test if creating \n");
	}*/
	//creates directory
	strcat(attr_dir, attrname);
	//printk("%s\n", attr_dir);
	//creates _file path for new _file
	
	struct file* attr_file = (struct file*) NULL;
	//attr_file = filp_open(attr_file, 
	//if (_file != NULL)
	
	/*{
		fputs(attrvalue, _file);
		fclose(_file);
		//writes _file
		return 0;
	}*/
	return -1;
}

asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{	
/*
//check if absoulte path to _file
	if (filename[0] != '/')
	{
		printk("Not absolute\n");
		return -1;
	}

	buf = (char*) vmalloc(bufsize);
	//allocates buffer in memory


	char* attr_dir  = (char*) vmalloc(sizeof(filename) + 100);
	//strcpy(new_dir, ".");//prepend "."
	
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	strcat(attr_dir, attrname);
	//creates _filepath to read from


	struct file* attr__file = fopen(attr_dir, "rb");
	if (attr__file != NULL)
	{
		fread(buf, sizeof(char), bufsize, attr__file);
		//printk("%s\n", buf);
		fclose(attr__file);
		//reads from _file	
		return sizeof(buf);
	}
*/
	printk("356: Get Attributes\n");
	return 0;

}

/*This call gets the value of the attribute named “attrname” attached to the _file named “filename”. The value is stored in the buf pointer which must have at least “bufsize” by
tes of storage. 
The filename must be an absolute path to the _file. The strings should be null terminated, and reasonable limits should be enforced on all strings. The return value should be the number of bytes returned  for success, or a negative error value.
*/



asmlinkage long cs401_get_attribute_names(char *filename, char *buf, int bufsize)
{
/*
	if (filename[0] != '/')
	{
		printk("Not absolute\n");
		return -1;
	}
	//checks if absolute path to _file
	

	buf = (char*) vmalloc(bufsize);
	//allocates buffer in memory


	char* attr_dir  = (char*) vmalloc(sizeof(filename) + 100);
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	//creates _filepath to read from

	DIR *dir;
	struct dirent *ent;
	if((dir = opendir(attr_dir)) != NULL)
	{
		while((ent = readdir (dir)) != NULL)
		{	
			if(ent->d_name == "..")
				printk("F");
			if (ent->d_name == ".")
				continue;
			strcat(buf, ent->d_name);
			strcat(buf, ":");
			printk("%s\n", buf);
		}
		closedir(dir);
		return sizeof(buf);
	}
	else
	{
		//perror("attr dir does not exist");
		//return -1;
	}
	//traverses directory and builds buf with colon seperated _files
	
*/	
	printk("357: List Attributes\n");
	return 0;
}

/* gets all of the names of attributes that are set for the _file “filename”. The list of attributes is returned as a “:” (colon) separated list in the “buf” string. The buf pointer  must have at least “bufsize” bytes of storage. The filename must be an absolute path to  the _file. The strings should be null terminated, and reasonable limits should be e
*/

asmlinkage long cs401_remove_attribute(char *filename, char *attrname)
{
/*
	if (filename[0] != '/')
	{
		printk("Not absolute\n");
		return -1;
	}
	//checks if absolute path to _file
	
	char* attr_dir  = (char*) vmalloc(sizeof(filename) + 100);
	char* attr__file = (char*) vmalloc(sizeof(filename)+100);
	
	strcpy(attr_dir, filename);	
	strcat(attr_dir, "_attr\0");//null terminated
	strcat(attr_dir, "/");
	strcpy(attr__file, attr_dir);
	strcat(attr__file, attrname);
	//creates _filepaths to read from
	
	struct file* _file = fopen(attr__file, "r");
	DIR * dir;
	struct dirent *ent;
	int n = 0;
	if (_file != NULL)//checks if _file exists
	{
		printk("\n Removing: %s\n", attr__file);
		remove(attr__file);
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
				printk("\n Removing empty attr dir\n");
				vfs_rmdir(attr_dir);
			}
			return 0;
		}
	}
	else if (ENOENT == errno)
	{
		printk("\n File/Directory doesnt exist\n");
		return -1;
	}
	//something else went wrong
	return -1;
	
	//remove _file
	//if dir is empty remove 	
*/
		printk("358: Rem Attributes\n");
		return 0;
}

/*This call removes the specified attribute from the _file. It should remove the _file that was created in the attribute directory. If this was the last user attribute for this _file the attribute directory should also be removed. Note, this will require some locks as some other process may be adding a new attribute at the same time, and should not fail because the directory was removed from under it. The return value should be 0 for success, or a negative error value. This system call can be used with the cs401_get_attribute_names() call to remove ‘all’ of the attributes attached to a specific _file.
*/
