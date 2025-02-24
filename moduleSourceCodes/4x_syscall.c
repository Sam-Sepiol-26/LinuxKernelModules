#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE0(my_syscall){
	printk(KERN_INFO "Hey, It's 0x00S30's new syscall!");
	return 0;
}


//the sys_call_table "syscall_64.tbl" needs to be modified
//inorder for this to run
//cannot modify the syscall table in kernel versions > 6.x
//because mordern kernels hide syscall table from kallsyms export
//and CR0 is directly blocked because of KPTI (kernel page table isolation)
