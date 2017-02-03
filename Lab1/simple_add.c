#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_simple_add(int num1, int num2, int* res)
{
printk(KERN_ALERT "Num1: %d\n", num1);
printk(KERN_ALERT "Nul2: %d\n", num2);
*res = num1 + num2;
printk(KERN_ALERT "Result: %d\n",* res);
return 0;
}
