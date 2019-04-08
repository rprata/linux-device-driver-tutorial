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

*[GPL](https://opensource.org/licenses/gpl-license)

*[LGPL](https://opensource.org/licenses/lgpl-license)

*[BSD-2-Clause](https://opensource.org/licenses/BSD-3-Clause)

*[MIT](https://opensource.org/licenses/MIT)

*[Apache-2.0](https://opensource.org/licenses/Apache-2.0)

*[MPL-2.0](https://opensource.org/licenses/MPL-2.0)

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

* *Version of form [**epoch>**]**version**[-**extra-version**].*

* * **epoch**: A (small) unsigned integer which allows you to start versions anew. If not mentioned, it’s zero. eg. “2:1.0” is after “1:2.0”.*

* * **version**: The **version** may contain only alphanumerics and the character `.’. Ordered by numeric sort for numeric parts, ascii sort for ascii parts (as per RPM or DEB algorithm).*

* * **extraversion**: Like **version**, but inserted for local customizations, eg “rh3” or “rusty1”.*

```C
MODULE_VERSION("1:1.0");
```

## Simple Kernel Programming
So as of now we know the very basic things that needed for writing driver. Now we will move into programming. In every programming language, how we will start to write the code? Any ideas? Well, in all programming there would be a starting point and ending point. If you take C Language, starting point would be the main function, Isn’t it? It will start from the starting of the main function and run through the functions which is calling from main function. Finally it exits at the main function closing point. But Here two separate functions used for that starting and ending.

1. Init function
2. Exit function

Kernel modules require a different set of header files than user programs require.And keep in mind, Module code should not invoke user space Libraries or API’s or System calls.

