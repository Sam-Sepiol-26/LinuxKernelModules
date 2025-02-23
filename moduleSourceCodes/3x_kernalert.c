#include <linux/module.h>
#include <linux/kernel.h>



void prntmsg(void);

void prntmsg(void){
	printk(KERN_ALERT "Hey, it's 0x00S30!\n");
}


static int __init init_func(void){
	printk(KERN_INFO "Module loaded successfully!\n");
	prntmsg();
	return 0;
}


static void __exit exit_func(void){
	printk(KERN_INFO "Module Unloaded successfully!\n");
}


module_init(init_func);
module_exit(exit_func);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("0x00S30");
MODULE_DESCRIPTION("0x00S30 ----> Testing the usage of kern_alert!");
