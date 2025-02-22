#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>



void memory_alloc_kernel(void);


void memory_alloc_kernel(void){
	char *ptr;
	ptr = kmalloc(128, GFP_KERNEL);
	if(ptr){
		printk(KERN_INFO "Memory has been allocated: %p by ------> 0x00S30\n", ptr);
	}

	kfree(ptr);

	printk("And memory has been cleared!!\n");

}



static int __init my_init(void){
	printk("Loading module -----> 0x00S30\n");
	memory_alloc_kernel();
	return 0;
}



static void __exit my_exit(void){
	printk("Exiting module ------> 0x00S30\n");
}



module_init(my_init);
module_exit(my_exit);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("0x00S30");
MODULE_DESCRIPTION("A kernel module that allocates memory in the kernel dynamically and frees it!!");
