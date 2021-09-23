#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static unsigned int devone_major = 0;
module_param(devone_major, uint, 0);

static int devone_open(struct inode *inode, struct file *file)
{
    printk("%s: major %d minor %d (pid %d)\n", __func__, imajor(inode), iminor(inode), current->pid);

    inode->i_private = inode;  /* free to use */
    file->private_data = file; /* free to use */

    printk("  i_private=%p private_data=%p\n", inode->i_private, file->private_data);

    return 0;

}

static int devone_close(struct inode *inode, struct file *file)
{
    printk("%s: major %d minor %d (pid %d)\n", __func__, imajor(inode), iminor(inode), current->pid);
    printk("  i_private=%p private_data=%p\n", inode->i_private, file->private_data);

    return 0;
}