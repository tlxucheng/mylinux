#include "sipp.hpp"

task_list all_tasks;
task_list running_tasks;
timewheel paused_tasks;

task_list* get_running_tasks()
{
    return &running_tasks;
}

// Methods for the task class

task::task()
{
    this->taskit = all_tasks.insert(all_tasks.end(), this);
    add_to_runqueue();
}

task::~task()
{
    if (running) {
        remove_from_runqueue();
    } else {
        paused_tasks.remove_paused_task(this);
    }
    all_tasks.erase(taskit);
}

void task::add_to_runqueue()
{
	this->runit = running_tasks.insert(running_tasks.end(), this);
    this->running = true;
}

bool task::remove_from_runqueue()
{
    if (!this->running) {
        return false;
    }
    running_tasks.erase(this->runit);
    this->running = false;
    return true;
}

void task::setRunning()
{
    if (!running) {
        paused_tasks.remove_paused_task(this);
        add_to_runqueue();
    }
}

timewheel::timewheel()
{
    count = 0;
    wheel_base = clock_tick;
}

void timewheel::remove_paused_task(task *task)
{
    task_list *list = task->pauselist;
    list->erase(task->pauseit);
    count--;
}


