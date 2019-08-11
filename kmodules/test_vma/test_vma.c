#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>

static int pid;
module_param(pid, int, S_IRUGO);

static int __init my_init(void)
{
    struct task_struct *tsk;	

    if(0 == pid)
    {
        tak = current;
	pid = tak->pid
    }
    else 
    {
    }

    return 0;
}

static void __exit my_exit(void)
{
    return;
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
