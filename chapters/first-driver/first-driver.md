# First Device Driver #

Now we are going to see First Device Driver development. Before writing driver, we should give the module information. So First we will see about those module information.

## Module Information ##

* License
* Author
* Module Description
* Module Version

These all informations are present in the linux/module.h as a macros.

### License ###

The following license idents are currently accepted as indicating free software modules:

* [GPL](https://opensource.org/licenses/gpl-license)

* [LGPL](https://opensource.org/licenses/lgpl-license)

* [BSD-2-Clause](https://opensource.org/licenses/BSD-3-Clause)

* [MIT](https://opensource.org/licenses/MIT)

* [Apache-2.0](https://opensource.org/licenses/Apache-2.0)

* [MPL-2.0](https://opensource.org/licenses/MPL-2.0)

This exists for several reasons:

1. modinfo can show license info for users wanting to vet their setup is free
2. The community can ignore bug reports including proprietary modules
3. Vendors can do likewise based on their own policies

We can give the License for our driver (module) like below. For this you need to include the Linux/module.h header file.

```C
MODULE_LICENSE("MIT");
```

### Author ###
Using this Macro we can mention that who is wrote this driver or module. So modinfo can show author name for users wanting to know. We can give the Author name for our driver (module) like below. For this you need to include the Linux/module.h header file.

```C
MODULE_AUTHOR("Renan Prata");
```

*Note: Use “Name *email*” or just “Name”, for multiple authors use multiple MODULE_AUTHOR() statements/lines.*

### Module Description ###
Using this Macro we can give the description of the module or driver. So modinfo can show module description for users wanting to know. We can give the description for our driver (module) like below. For this you need to include the linux/module.h header file.

```C
MODULE_DESCRIPTION("A sample driver");
```

### Module Version ###
Using this Macro we can give the version of the module or driver. So modinfo can show module version for users wanting to know.

* Version of form [**epoch>**]**version**[-**extra-version**].

* **epoch**: A (small) unsigned integer which allows you to start versions anew. If not mentioned, it’s zero. eg. "2:1.0" is after "1:2.0".

* **version**: The **version** may contain only alphanumerics and the character '.'. Ordered by numeric sort for numeric parts, ascii sort for ascii parts (as per RPM or DEB algorithm).

* **extraversion**: Like **version**, but inserted for local customizations, eg "rh3" or "rusty1".

```C
MODULE_VERSION("1:1.0");
```

## Simple Kernel Programming ##
So as of now we know the very basic things that needed for writing driver. Now we will move into programming. In every programming language, how we will start to write the code? Any ideas? Well, in all programming there would be a starting point and ending point. If you take C Language, starting point would be the main function, Isn’t it? It will start from the starting of the main function and run through the functions which is calling from main function. Finally it exits at the main function closing point. But Here two separate functions used for that starting and ending.

1. Init function
2. Exit function

Kernel modules require a different set of header files than user programs require.And keep in mind, Module code should not invoke user space Libraries or API’s or System calls.

### Init function ###
This is the function which will executes first when the driver is loaded into the kernel. For example when we load the driver using insmod, this function will execute. Please see below to know the syntax of this function.

```C
static int __init hello_world_init(void) /* Constructor */
{
    return 0;
}
module_init(hello_world_init);
```

### Exit function ###
This is the function which will executes last when the driver is unloaded from the kernel. For example when we unload the driver using rmmod, this function will execute. Please see below to know the syntax of this function.

```C
void __exit hello_world_exit(void)
{

}
module_exit(hello_world_exit);
```

This function should register itself by using module_exit() macro.

### Printk() ###
In C programming how we will print the values or whatever? Correct. Using printf() function. printf() is a user space function. So we cant use this here. So they created one another function for kernel which is printk().

One of the differences is that printk lets you classify messages according to their severity by associating different loglevels, or priorities, with the messages. You usually indicate the loglevel with a macro. I will explain about the macros now. There are several macros used for printk.

* KERN_EMERG - Used for emergency messages, usually those that precede a crash.

* KERN_ALERT - Situation requiring immediate action.

* KERN_CRIT - Critical conditions, often related to serious hardware or software failures.

* KERN_ERR - Used to report error conditions; device drivers often use KERN_ERR to report hardware difficulties.

* KERN_WARNING - Warnings about problematic situations that do not, in themselves, create serious problems with the system.

* KERN_NOTICE - Situations that are normal, but still worthy of note. A number of security-related conditions are reported at this level.

* KERN_INFO - Informational messages. Many drivers print information about the hardware they find at startup time at this level.

* KERN_DEBUG - Used for debugging messages.

```C
printk(KERN_INFO "Linux Device Driver Hello World");
```

### Difference between printf and printk ###
* printk() is a kernel level function, which has the ability to print out to different loglevels. We can see the prints using dmesg command.
* printf() will always print to a file descriptor – STD_OUT. We can see the prints in STD_OUT console.

## Simple Driver ##

This is the complete code for our simple device driver (hello-world-module.c). You can access this code in subdirectory 'src'. Once we have the C code, it is time to compile it and create the module file hello-world-module.ko. Creating a Makefile for your module is straightforward. With the C code (hello-world-module.c) and Makefile ready, all we need to do is invoke make to build our first driver (hello-world-module.ko).

In Terminal you need to enter sudo make like below video.

[![asciicast](https://asciinema.org/a/T4FG5THwcMFRy7SGIeafbPACi.png)](https://asciinema.org/a/T4FG5THwcMFRy7SGIeafbPACi)


