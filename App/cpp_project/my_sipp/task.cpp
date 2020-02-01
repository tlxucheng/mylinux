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

void task::add_to_paused_tasks(bool increment)
{
    paused_tasks.add_paused_task(this, increment);
}

void task::setRunning()
{
    if (!running) {
        paused_tasks.remove_paused_task(this);
        add_to_runqueue();
    }
}

void task::setPaused()
{
    if (running) {
        if (!remove_from_runqueue()) {
            WARNING("Tried to remove a running call that wasn't running!\n");
            assert(0);
        }
    } else {
        paused_tasks.remove_paused_task(this);
    }
    assert(running == false);
    add_to_paused_tasks(true);
}

// Methods for the timewheel class

// Based on the time a given task should next be woken up, finds the
// correct time wheel for it and returns a list of other tasks
// occuring at that point.
task_list *timewheel::task2list(task *task)
{
  unsigned int wake = task->wake();

  if (wake == 0) {
        return &forever_list;
  }

  assert(wake >= wheel_base);
  assert(wheel_base <= clock_tick);

  unsigned int time_until_wake = wake - wheel_base;

  unsigned int slot_in_first_wheel = wake % LEVEL_ONE_SLOTS;
  unsigned int slot_in_second_wheel = (wake / LEVEL_ONE_SLOTS) % LEVEL_TWO_SLOTS;
  unsigned int slot_in_third_wheel = (wake / (LEVEL_ONE_SLOTS * LEVEL_TWO_SLOTS));

  bool fits_in_first_wheel = ((wake / LEVEL_ONE_SLOTS) == (wheel_base / LEVEL_ONE_SLOTS));
  bool fits_in_second_wheel = ((wake / (LEVEL_ONE_SLOTS * LEVEL_TWO_SLOTS)) ==
                                (wheel_base / (LEVEL_ONE_SLOTS * LEVEL_TWO_SLOTS)));
  bool fits_in_third_wheel = (slot_in_third_wheel < LEVEL_THREE_SLOTS);

    if (fits_in_first_wheel) {
        return &wheel_one[slot_in_first_wheel];
    } else if (fits_in_second_wheel) {
        return &wheel_two[slot_in_second_wheel];
    } else if (fits_in_third_wheel) {
      return &wheel_three[slot_in_third_wheel];
    } else{
      ERROR("Attempted to schedule a task too far in the future");
      return NULL;
    }
}


timewheel::timewheel()
{
    count = 0;
    wheel_base = clock_tick;
}

// Adds a task to the correct timewheel. When increment is false, does
// not increment the count of tasks owned by this timewheel, and so
// can be used for recalculating the wheel of an existing task.
void timewheel::add_paused_task(task *task, bool increment)
{
    task_list::iterator task_it;
    if (task->wake() && task->wake() < wheel_base) {
        task->add_to_runqueue();
        return;
    }
    task_list *list = task2list(task);
    task_it = list->insert(list->end(), task);
    task->pauselist = list;
    task->pauseit = task_it;
    if (increment) {
        count++;
    }
}

void timewheel::remove_paused_task(task *task)
{
    task_list *list = task->pauselist;
    list->erase(task->pauseit);
    count--;
}


