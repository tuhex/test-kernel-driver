/* dev_mod */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("tuhex");
MODULE_DESCRIPTION("mods a device num. and implements some callback functions");

/**
 * @brief function is called, when the device file is opened
 */
static int driver_append(struct inode *device_file, struct file *instance) {
	rcu_read_lock();
	printk("dev_mod - open was called!\n");
	return 0;
}

static int driver_shut(struct inode *device_file, struct file *instance) {
	printk("dev_mod - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_append,
	.release = driver_shut
};

#define MYMAJOR 90

/**
 * @brief function is called, when the module is loaded into kernel
 */
static int __init ModuleInit(void) {
	int retval;

	printk("Hello, kernel!\n");
	// register device num.
	retval = register_chrdev(MYMAJOR, "my_dev_mod", &fops);
	if (retval == 0)
		printk("dev_mod - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	else if(retval > 0)
		printk("dev_mod - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	else {
		printk("Coult not register device num!\n");
		return -1;
	}
	return 0;
}

static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my_dev_mod");
	printk("goodbye, kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
