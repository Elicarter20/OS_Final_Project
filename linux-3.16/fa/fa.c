#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <linux/dirent.h>  
#include <linux/stat.h>     

asmlinkage long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{
	printk("355: Set Attributes\n");
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
		if (S_ISREG(file_info.st_mode));
		else
			return -1;//if not file exit
	}
	else
		return -1;//file does not exist

	//creating directory file path
    	char *file;	//will hold file
    	char *temp;	
    	char* namecopy[256];//copy of filename
    	char* attr_dir[256];//attribute directory path


    	copy_from_user( namecopy, filename, sizeof(namecopy)/sizeof(char)); //creates copy of filename
    	file  = strrchr(filename, '/');//gets last occurence of backslash (the file)
    	file += sizeof(char);	//removes last backslash
    	temp = strstr( namecopy, file );//splits occurence of file name in file path
    	strncpy( temp,"\0",1);	//makes pointer past before filename to null
    	sprintf(attr_dir,"%s.%s_attr",namecopy,file);//concatenates full path
 
	new_stat = sys_newstat(attr_dir,&file_info);
	if (new_stat == 0)
	{
		if (S_ISDIR(file_info.st_mode) );
		else
			sys_mkdir(attr_dir, 0);//creates attribute directory if doesnt exist
	}
	else
	{
		return -1;
	}

   	char* file_path[256];//creates attribute file path
    	sprintf(file_path,"%s/%s",attr_dir,attrname);
    	printk("%s\n", file_path);
    	sys_unlink(file_path);                //replaces existing file

 
    	sys_mknod(file_path, file_info.st_mode,0);//creates new file

    	int file_descriptor = sys_open(file_path, O_CREAT|O_WRONLY,0);//opens created file
    	if(file_descriptor<0)
	{
		printk("File not created\n");
		return -1;
	}
   	sys_write(file_descriptor,attrvalue,size);//writes to created file 
   	set_fs(fs);
    	return 0;
}


