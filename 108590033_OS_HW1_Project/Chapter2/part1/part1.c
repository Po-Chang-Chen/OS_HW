#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>



static int __init part1_init(void)
{
    printk("Loading Kernel Module\n");
    return 0;
}
static void __exit part1_exit(void)
{
    printk("Removing Kernel Module\n");
}
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("part1");
MODULE_AUTHOR("108590033");
module_init(part1_init);
module_exit(part1_exit);
