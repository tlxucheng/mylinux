#ifndef __TASK__
#define __TASK__

class task;

typedef std::list<task *> task_list;

class task
{
public:
    task();
    virtual ~task();
};

#endif

