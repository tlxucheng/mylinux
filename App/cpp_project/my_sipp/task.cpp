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

}

task::~task()
{

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


