#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static void print_cpu(char *pStr)
{
    preempt_disable();
    pr_info("%s cpu=%d.\n", pStr, smp_processor_id());
    preempt_enable();
 
    return;
}

static int __init my_init(void)
{
    print_cpu("Loading module");

    return 0;
}

static void __exit my_exit(void)
{
    print_cpu("Kill was done on.");

    return;
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Xu Cheng");
MODULE_LICENSE("GPL");
