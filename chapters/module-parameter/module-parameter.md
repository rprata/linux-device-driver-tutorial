# Passing Arguments to Device Driver #

We can pass the arguments to any other functions in the same program. But Is it possible to pass any arguments to any program? I think Probably yes. Right? Well, we can. In C Programming we can pass the arguments to the program. For that we need to add argc and argv in the main function definition. I hope everyone knows that. Now come to our topic. Is it possible to pass the argument to the Device Driver? Fine. In this tutorial, we are going to see that topic.

## Types of Permissions ##

* `S_IWUSR`
* `S_IRUSR`
* `S_IXUSR`
* `S_IRGRP`
* `S_IWGRP`
* `S_IXGR`

```
In this S_I is a common header.
R = read ,W =write,X= Execute.
USR =user, GRP = Group
Using OR ‘|’ (or operation) we can set multiple permissions at a time.
```

## Module Parameters Macros ##

* `module_param`
* `module_param_array`
* `module_param_cb`

### module_param ###

This macro used to initialize the arguments. module_param takes three parameters: the name of the variable, its type, and a permissions mask to be used for an accompanying sysfs entry. The macro should be placed outside of any function and is typically found near the head of the source file. `module_param` macro, defined in `linux/moduleparam.h`. 

```
module_param(devName, typeOfParam, perm)
```

module_param() macro creates the sub-directory under /sys/module. For example:

```
module_param(fakeDev, int, S_IWUSR|S_IRUSR)
```

This will create a sysfs entry `/sys/module/<module-name>/parameters/fakeDev`. 
Numerous types are supported for module parameters:

* bool
* invbool (type inverts the value, so that true values become false and vice versa)
* charp (char *)
* int
* long
* short
* uint
* ulong
* ushort

### module_param_array ###

This macro is used to send the array as an argument. Array parameters, where the values are supplied as a comma-separated list, are also supported by the module loader. To declare an array parameter, use:

```
module_param_array(devName, typeOfParam, num, perm)
```

### module_param_cb ##

This macro used to register the callback whenever the argument (parameter) got changed. I think you don’t understand. Let me explain it properly. 

For Example, I have created one parameter by using module_param and it will create a sysfs entry. When value of sysfs changed (you can change using `echo 1 > /sys/module/<module-name>/parameters/fakeDev`), we can get notification by callback. If you want to get a notification whenever the value got to change. we need to register our handler function to its file operation structure.

```
struct kernel_param_ops {
  int (*set)(const char *val, const struct kernel_param *kp);
  int (*get)(char *buffer, const struct kernel_param *kp);
  void (*free)(void *arg);
}
```

## When we will need this notification? ##

I will tell you about the practical scenario. Whenever the value is set to 1, you have to write something into a hardware register. How can you do this if the change of value variable is not notified to you? Got it? I think you have understood. If you didn't understand, just see the explanation in the same directory.