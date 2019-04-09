#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int value, arr_value[4];
char *name;
int cb_value = 0;

module_param(value, int, S_IRUSR|S_IWUSR);                      //integer value
module_param(name, charp, S_IRUSR|S_IWUSR);                     //String
module_param_array(arr_value, int, NULL, S_IRUSR|S_IWUSR);      //Array of integers

/*----------------------Module_param_cb()--------------------------------*/
int notify_param(const char *val, const struct kernel_param *kp)
{
        int res = param_set_int(val, kp); // Use helper for write variable
        if(res==0) {
                printk(KERN_INFO "Call back function called...\n");
                printk(KERN_INFO "New value of cb_value = %d\n", cb_value);
                return 0;
        }
        return -1;
}

const struct kernel_param_ops my_param_ops = 
{
        .set = &notify_param, // Use our setter ...
        .get = &param_get_int, // .. and standard getter
};

module_param_cb(cb_value, &my_param_ops, &cb_value, S_IRUGO|S_IWUSR );
/*-------------------------------------------------------------------------*/

static int __init hello_world_init(void)
{
        int i;
        printk(KERN_INFO "value = %d  \n", value);
        printk(KERN_INFO "cb_value = %d  \n", cb_value);
        printk(KERN_INFO "name = %s \n", name);
        for (i = 0; i < (sizeof arr_value / sizeof (int)); i++) {
                printk(KERN_INFO "Arr_value[%d] = %d\n", i, arr_value[i]);
        }
        printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
	return 0;
}

void __exit hello_world_exit(void)
{
        printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Renan Prata <renancprata@gmail.com");
MODULE_DESCRIPTION("A simple hello world driver using module parameters");
MODULE_VERSION("1:1.0");