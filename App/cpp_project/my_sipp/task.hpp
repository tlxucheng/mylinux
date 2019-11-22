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
	
};

typedef std::list<task *> task_list;

class task
{
public:
    task();
    virtual ~task();

protected:
	void setRunning();
	bool running;

private:
	void add_to_runqueue();
	bool remove_from_runqueue();
	
    /* If we are running, the iterator to remove us from the running list. */
    task_list::iterator runit;
};

#endif

