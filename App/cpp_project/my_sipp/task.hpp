#ifndef __TASK__
#define __TASK__

#include <map>
#include <list>
#include <sys/types.h>
#include <string.h>

class task;

typedef std::list<task *> task_list;

/* This arrangement of wheels lets us support up to 32 bit timers.
 *
 * If we were to put a minimum bound on timer_resol (or do some kind of dynamic
 * allocation), then we could reduce the level one order by a factor of
 * timer_resol. */
#define LEVEL_ONE_ORDER 12
#define LEVEL_TWO_ORDER 10
#define LEVEL_THREE_ORDER 10
#define LEVEL_ONE_SLOTS (1 << LEVEL_ONE_ORDER)
#define LEVEL_TWO_SLOTS (1 << LEVEL_TWO_ORDER)
#define LEVEL_THREE_SLOTS (1 << LEVEL_THREE_ORDER)

/* A time wheel structure as defined in Varghese and Lauck's 1996 journal
 * article (based on their 1987 SOSP paper). */
class timewheel
{
public:
    timewheel();

    int expire_paused_tasks();
    /* Add a paused task and increment count. */
    void add_paused_task(task *task, bool increment);
    void remove_paused_task(task *task);
    int size();
private:
    /* How many task are in this wheel. */
    int count;

    unsigned int wheel_base;

    /* The actual wheels. This is a variation on having one wheel for
     * seconds, another for minutes and a third for hours - in this
     * model, the first wheel holds tasks that should be scheduled in
     * the next 2^12ms (~4s), the second wheel holds tasks that
     * should be scheduled between 2^12 and 2^22ms (~4s-~69m), and
     * the third wheel holds tasks that should be scheduled between
     * 2^22ms and 2^32ms (~69m-~8 years). */
    task_list wheel_one[LEVEL_ONE_SLOTS];
    task_list wheel_two[LEVEL_TWO_SLOTS];
    task_list wheel_three[LEVEL_THREE_SLOTS];

    /* Calls that are paused indefinitely. */
    task_list forever_list;

    /* Turn a task into a list (based on wakeup). */
    task_list *task2list(task *task);
};

class task
{
public:
    task();
    virtual ~task();

    virtual bool run() = 0;

protected:
    /* Wake this up, if we are not already awake. */
    void setRunning();
    /* Put us to sleep (we must be running). */
    void setPaused();
    /* When should this task wake up? */
    virtual unsigned int wake() = 0;
    /* Is this task paused or running? */
    bool running;

private:
    /* Run and Pause Queue Maintenance. */
	void add_to_runqueue();
	bool remove_from_runqueue();
    void add_to_paused_tasks(bool increment);
    void recalculate_wheel();

	/* This is for our complete task list. */
    task_list::iterator taskit;
    /* If we are running, the iterator to remove us from the running list. */
    task_list::iterator runit;
    /* If we are paused, the iterator to remove us from the paused list. */
    task_list::iterator pauseit;
	/* The list that we are stored in (only when paused) . */
    task_list *pauselist;
	/* The timing wheel is our friend so that it can update our list pointer. */
    friend class timewheel;
};

task_list * get_running_tasks();
int expire_paused_tasks();

#endif

