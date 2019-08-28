#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

dev_t dev = 0;
static struct class *dev_class;
static struct cdev main_cdev;

static int __init main_init(void);
static void __exit main_exit(void);
static int main_open(struct inode *inode, struct file *file);
static int main_release(struct inode *inode, struct file *file);
static ssize_t main_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t main_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
.owner          = THIS_MODULE,
.read           = main_read,
.write          = main_write,
.open           = main_open,
.release        = main_release,
};

static int main_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Driver Open Function Called...!!!\n");
    return 0;
}

static int main_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Driver Release Function Called...!!!\n");
    return 0;
}

static ssize_t main_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver Read Function Called...!!!\n");
    return 0;
}
static ssize_t main_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	char text[len];
	memcpy(text, buf, len);
	text[len - 1] = '\0';
	
    printk(KERN_INFO "Driver Write Function Called [%s]...!!!\n", text);
    return len;
}

static int __init main_init(void)
{
	if (alloc_chrdev_region(&dev, 0, 1, "KernelTest_Dev") < 0) 
	{
		printk(KERN_INFO "Cannot allocate major number for device 1\n");
	}

	printk(KERN_INFO "Major = %d / Minor = %d", MAJOR(dev), MINOR(dev));

    cdev_init(&main_cdev, &fops);

    if((cdev_add(&main_cdev, dev, 1)) < 0){
        printk(KERN_INFO "Cannot add the device to the system\n");
        goto r_class;
    }


	if ((dev_class = class_create(THIS_MODULE, "test_class")) == NULL) {
		printk(KERN_INFO "Cannot create struct class for device\n");
		goto r_class;
	}
	
	if (device_create(dev_class, NULL, dev, NULL, "test_dev") == NULL) {
		printk(KERN_INFO "Cannot create device test_dev\n");
		goto r_device;
	}
    printk(KERN_INFO "[main-module] Kernel Module Inserted Successfully...\n");    
    return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, 1);
	return -1;
}

void __exit main_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&main_cdev);
	unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "[main-module] Kernel Module Removed Successfully...\n");
}

module_init(main_init);
module_exit(main_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Renan Prata <renancprata@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("1:2");