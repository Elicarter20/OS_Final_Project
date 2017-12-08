#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/string.h>
#include <linux/dirent.h> 
#include <linux/stat.h>  
#include <linux/fs.h>
#include <linux/ctype.h>
#include <linux/types.h>   

asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{
	printk("356: Get Attributes\n");
     	mm_segment_t fs;    
     	fs = get_fs();
     	set_fs(get_ds());//permits usage of syscalls

    	if (filename[0] != '/')
	{
		printk("not absolute filepath");
		return -1;
	}//checks if absolute filepath
   
	struct stat file_info; //file info struct
	int new_stat = sys_newstat(filename, &file_info);
	if (new_stat==0)
	{
		if (S_ISREG(file_info.st_mode) );
		else
			return -1;//if not filee exit
	}
	else
		return -1;//file does not exist

	//creating directory file path

    	char *file	;	//will hold file
    	char *temp	;	
    	char* namecopy[256];//copy of filename
    	char* attr_dir[256];//attribute directory path

    	copy_from_user( namecopy, filename, sizeof(namecopy)/sizeof(char)); //creates copy of filename
    	file  = strrchr(filename, '/');//gets last occurence of backslash (the file)
    	file += sizeof(char);	//removes last backslash
    	temp = strstr( namecopy, file );//splits occurence of file name in file path
    	strncpy( temp,"\0",1);	//makes pointer past before filename to null
    	sprintf(attr_dir,"%s.%s_attr",namecopy,file);//concatenates full path


	
  	// Check if the directory exists
	new_stat = sys_newstat(attr_dir, &file_info);	
	if(!(new_stat==0 && S_ISDIR(file_info.st_mode)))
		return -1;//directory doesnt exist
	
	char file_path[256]; //holds attribute file path
	sprintf(file_path,"%s/%s",attr_dir,attrname);
	new_stat = sys_newstat(file_path, &file_info);	
	
	if(!(new_stat==0 && S_ISREG(file_info.st_mode)))
		return -1;
	//if file does not exist, return -1

	int file_descriptor = sys_open(file_path, O_RDWR, 0);//reads from file using syscall

	
  	char attrvalue[256];
	sys_read(file_descriptor, attrvalue, file_info.st_size);//reads file into attrvalue 

	printk("Attribute Value: %s\n", attrvalue);
	copy_to_user(buf, attrvalue, file_info.st_size);//returns attrvalue to user

	sys_close(file_descriptor);//closes file
    	set_fs(fs);
	return(sizeof(attrvalue));
}

