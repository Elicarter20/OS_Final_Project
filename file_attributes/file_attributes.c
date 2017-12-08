#include <linux/kernel.h>
/*#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/err.h>
#include <linux/fts.h>
#include <linux/dirent.h>
*/

asmlinkage long cs401_set_attribute(char *filename, char  *attrname, char *attrvalue, int size)
{
	        printk("355: Set Attributes\n");
		return 0;
}

asmlinkage long cs401_get_attribute(char *filename, char *attrname, char *buf, int bufsize)
{	
	printk("356: Get Attributes\n");
	return 0;

}

asmlinkage long cs401_get_attribute_names(char *filename, char *buf, int bufsize)
{
	prink("357: Get List\n");
	return 0;
}


asmlinkage long cs401_remove_attribute(char *filename, char *attrname)
{
	printk("358: Remove attr\n");
	return 0;
}
