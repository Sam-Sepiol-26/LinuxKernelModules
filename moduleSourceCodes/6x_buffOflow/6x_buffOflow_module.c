#include <linux/kernel.h>

#include <linux/module.h>

#include <linux/init.h>




#define BUFF_SIZE 16



static int __init my_init(void){



	char buffer[BUFF_SIZE];

	printk(KERN_INFO "----->Module vulnerable to Buffer Overflow\n");

	memset(buffer, 'A', 64); //This overwrites the buffer with size 16

	return 0;

}




static void __exit my_exit(void){

	printk(KERN_INFO "Module has been unloaded <-------\n");

}




module_init(my_init);

module_exit(my_exit);




MODULE_LICENSE("GPL");

MODULE_AUTHOR("0x00S30");

MODULE_DESCRIPTION("Sample module for Buffer Overflow in kernel");
