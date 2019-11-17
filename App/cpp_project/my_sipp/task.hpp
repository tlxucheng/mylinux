#ifndef __TASK__
#define __TASK__

class task;

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
	void remove_from_runqueue();
};

#endif

