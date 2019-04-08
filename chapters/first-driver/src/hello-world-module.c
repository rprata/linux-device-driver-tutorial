#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_world_init(void)
{
    printk(KERN_INFO "[hello-world-module] Kernel Module Inserted Successfully...\n");    
    return 0;
}

void __exit hello_world_exit(void)
{
    printk(KERN_INFO "[hello-world-module] Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Renan Prata <renancprata@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("1:1.0");