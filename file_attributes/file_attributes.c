#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/kernel.h>
#include <linux/syscall.h>
#include <linux/iofile.h>
#include <linux/errno.h>
#include <linux/linkage.h>
#include <linux/fcntl.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
 asmlinkage long sys_hello(void)
{
        printk(“Hello world\n”);
        return 0;
 }



asmlinkage long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{
	unsigned int string_length = stren_user(basename(filename)) + 7 //7 bits for . , _attr and a NUll pointer.
	char* new_dir = (char*)malloc(string_length*sizeof(char));
	new_dir = "." + filename + "_attr" + NULL;//creates name of new directory
	char* dir_path = dirname(filename);
	/*
	Check if the attribute directory exists. IF no attribute directory exists, then create a
	new one */
	if(opendir(dir_path) == NULL){
		mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUR);
	}
	char* attribute_path = dir_path + attrname;
	//open file description and write attribute data into the new file.
	int fp = open(attribute_path, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	write(fp, attrvalue, size);
	return 0;
	
}
/*This call sets the attribute named “attrname” to the value in “attrvalue” which has length “size” to the file named “filename”. 

The filename must be an absolute path to the file. The strings should be null terminated, and reasonable limits should be enforced on all strings. The return value should be 0 for success, or a negative error value.
*/
asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{
	unsigned int string_length = stren_user(basename(filename)) + 7 //7 bits for . , _attr and a NUll pointer.
	char* new_dir = (char*)malloc(string_length*sizeof(char));
	new_dir = "." + filename + "_attr" + NULL;//creates name of new directory
	char* dir_path = dirname(filename);
	if(opendir(path) == NULL){
		return -1;
	}
	struct stat *std;
	char* attribute_path = new_dir + attrname;
	/*Obtain the information about the file and write it to the area pointed by std pointer.*/
	if(int stat(new_dir, std) != -1){
		unsigned int size = std.st_size;
		if(bufsize == NULL){
			fprintf(stderr, "out of memory\n");
			exit(1);
		} else if (bufsize < size){
			return -1;
		}
		int fp = open(attribute_path, O_RDWR);
		int con = read(fp, buf, bufsize);
		return con;
	} else {
		return -1;
	}
}
/*This call gets the value of the attribute named “attrname” attached to the file named “filename”. The value is stored in the buf pointer which must have at least “bufsize” by
tes of storage. 
The filename must be an absolute path to the file. The strings should be null terminated, and reasonable limits should be enforced on all strings. The return value should be the number of bytes returned for success, or a negative error value.
*/
asmlinkage long cs401_get_attribute_names(char *filename, char *buf, int bufsize)
{

}
/*This call gets all of the names of attributes that are set for the file “filename”. The list of attributes is returned as a “:” (colon) separated list in the “buf” string. The buf pointer  must have at least “bufsize” bytes of storage. The filename must be an absolute path to  the file. The strings should be null terminated, and reasonable limits should be e
*/

asmlinkage long cs401_remove_attribute(char *filename, char *attrname)
{

}

/*This call removes the specified attribute from the file. It should remove the file that was created in the attribute directory. If this was the last user attribute for this file the attribute directory should also be removed. Note, this will require some locks as some other process may be adding a new attribute at the same time, and should not fail because the directory was removed from under it. The return value should be 0 for success, or a negative error value. This system call can be used with the cs401_get_attribute_names() call to remove ‘all’ of the attributes attached to a specific file.
*/
