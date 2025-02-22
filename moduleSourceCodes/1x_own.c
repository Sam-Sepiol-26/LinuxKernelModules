#include <linux/module.h>
#include <linux/kernel.h>



static int __init own_init(void){
	printk(KERN_INFO "Hey, Im 0x00S30 and I have successfully loaded my first module!");
	return 0;
}


static void __exit own_exit(void){
	printk(KERN_INFO "Hey its 0x00S30 again and I have successfully removed this module!");
}


module_init(own_init);
module_exit(own_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("0X00S30");
MODULE_DESCRIPTION("My first module for the Linux Kernel 6.11.2!");
