#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/init.h>

unsigned long **syscall_table;
asmlinkage long (*original_sys_open)(const char __user *, int, mode_t);

asmlinkage long hooked_sys_open(const char __user *filename, int flags, mode_t mode) {
    printk(KERN_INFO "File Opened: %s\n", filename);
    return original_sys_open(filename, flags, mode);  // Call original syscall
}

static int __init hook_init(void) {
    syscall_table = (unsigned long **) kallsyms_lookup_name("sys_call_table");
    write_cr0(read_cr0() & (~0x10000));  // Disable write protection
    original_sys_open = (void *)syscall_table[__NR_open];
    syscall_table[__NR_open] = (unsigned long *)hooked_sys_open;
    write_cr0(read_cr0() | 0x10000);  // Enable write protection
    return 0;
}

static void __exit hook_exit(void) {
    write_cr0(read_cr0() & (~0x10000));
    syscall_table[__NR_open] = (unsigned long *)original_sys_open;
    write_cr0(read_cr0() | 0x10000);
}

module_init(hook_init);
module_exit(hook_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shiva");
MODULE_DESCRIPTION("Syscall Hooking Example");
