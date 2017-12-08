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
asmlinkage long cs401_remove_attribute( char *filename, char *attrname )
{
	printk("358: Remove Attributes\n");
	mm_segment_t fs;
	fs = get_fs();
    	set_fs(get_ds());//permits usage of syscall

	struct stat file_info; //file info struct
	int new_stat = sys_newstat(filename, &file_info);
	if (new_stat==0)
	{
		if (S_ISREG(file_info.st_mode));
		else
			return -1;//if not file exit
	}
	else
		return -1;//file does not exist
	//check

  	
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



	//if directory exists and file exists, delete file
	//if directory is empty, delete directory
	char file_location[128];//attribute file location
	new_stat =  sys_newstat(attr_dir,&file_info);
	if(new_stat==0 && S_ISDIR(file_info.st_mode) )
	{
		sprintf(file_location,"%s/%s",attr_dir,attrname);//gets location of attribute file

	        if( sys_newstat(file_location,&file_info)==0 && S_ISREG(file_info.st_mode) )
	        {
	            if( sys_unlink(file_location) )
	                return -1;
        	    sys_rmdir(attr_dir);
        	}
   	     else
   	         return -1;//file doesnt exist
	}
	else
		return -1;//no attribute directory exists

	set_fs(fs);
	return 0;
}

