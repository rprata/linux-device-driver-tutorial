#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>


dev_t dev = 0;
static int __init main_init(void)
{
	if (alloc_chrdev_region(&dev, 0, 1, "KernelTest_Dev") < 0) 
	{
		printk(KERN_INFO "Cannot allocate major number for device 1\n");
	}
	printk(KERN_INFO "Major = %d / Minor = %d", MAJOR(dev), MINOR(dev));
    printk(KERN_INFO "[main-module] Kernel Module Inserted Successfully...\n");    
    return 0;
}

void __exit main_exit(void)
{
	unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "[main-module] Kernel Module Removed Successfully...\n");
}

module_init(main_init);
module_exit(main_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Renan Prata <renancprata@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("1:1.0");