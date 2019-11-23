#ifndef __TASK__
#define __TASK__

#include <map>
#include <list>
#include <sys/types.h>
#include <string.h>

class task;

class timewheel
{
public:
	timewheel();

	void remove_paused_task(task *task);
private:
    /* How many task are in this wheel. */
    int count;
	
    unsigned int wheel_base;
};

typedef std::list<task *> task_list;

class task
{
public:
    task();
    virtual ~task();

    virtual bool run() = 0;

protected:
	void setRunning();
	bool running;

private:
	void add_to_runqueue();
	bool remove_from_runqueue();

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

#endif

