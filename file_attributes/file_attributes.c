#include <linux/kernel.h>

 asmlinkage long sys_hello(void)
{
        printk(“Hello world\n”);
        return 0;
 }



asmlinkage long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{
	
	char* new_dir = "." + filename + "_attr" + NULL;//creates name of new directory
	

	if (true)
	{
		return 0;
	}
	else
	{
		return -1;
	}
	
}
/*This call sets the attribute named “attrname” to the value in “attrvalue” which has length “size” to the file named “filename”. 

The filename must be an absolute path to the file. The strings should be null terminated, and reasonable limits should be enforced on all strings. The return value should be 0 for success, or a negative error value.
*/
asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{

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
