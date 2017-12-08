#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <linux/dirent.h> 
#include <linux/stat.h>  
#include <linux/string.h>
#include <linux/fs.h>


struct dirent
{
	long 		d_ino;
	off_t 		d_off;
	unsigned short 	d_reclen;
	char		d_name[];
};//standard linux directory entry definition 

asmlinkage long cs401_get_attribute_names(char *filename, char *buf, int bufsize)
{
	printk("357: List Attributes\n");
   	mm_segment_t fs;    
    	fs = get_fs();
    	set_fs(get_ds());//permits usage of syscall
 
	//checks if file exists	
	struct stat file_info;//allows file info access    
	int new_stat = sys_newstat(filename, &file_info);
	if (new_stat==0)//if file exists proceed, else exit
	{
		if (S_ISREG(file_info.st_mode));
		else
			return -1;//if not file exit
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
	

	//traversing directory
	char directory_entries[1024];
	char total_attr[1024] = "\0";
	int dir_pointer,entry; //ints for dir traversal
   	char* dir_name; //hold string of directory entry
	int len = 0;    	
	struct dirent *dent=NULL; //directory entry struct
	dir_pointer = sys_open(attr_dir,O_RDONLY,0);//opens directory
 	while(true)//looping through the directory
    	{
        	entry = sys_getdents(dir_pointer,directory_entries,1024);//gets entry count
        	if(entry==-1) //if doesnt exist
			return -1;
        	if(entry==0)//if empty
			 break;       
		len = 0;
        	for(;len<entry;)//length be
        	{
            		dent = (struct dirent *)(directory_entries+len);//builds local versionvof entry
	     		dir_name = dent->d_name;
			if(strcmp(dir_name,".") && strcmp(dir_name,".."))
        	  	 {
        	          
        	 		strcat(total_attr, dir_name);
        	  		strcat(total_attr, ":");
				//builds string of directory entries using directory name
        		    }
       		            len+= dent->d_reclen;//increments length
        	}
    	}
    	sys_close(dir_pointer);


	total_attr[strlen(total_attr)-1]='\0';//remove final colon
	copy_to_user(buf, total_attr, bufsize);	// returns attribute names to user
	printk("Values: %s\n", total_attr);
   	set_fs(fs);
	return(strlen(total_attr));//returns bytes copied
}
