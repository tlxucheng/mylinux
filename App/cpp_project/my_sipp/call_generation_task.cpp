#include "sipp.hpp"

class CallGenerationTask *CallGenerationTask::instance = NULL;
unsigned long CallGenerationTask::calls_since_last_rate_change = 0;
unsigned long CallGenerationTask::last_rate_change_time = 0;
/* 虚函数编译不过先注释 */
void CallGenerationTask::initialize()
{
    /*
    assert(instance == NULL);
    instance = new CallGenerationTask();
    */
}

/*
CallGenerationTask::CallGenerationTask()
{
    setRunning();
}
*/

/*
CallGenerationTask::~CallGenerationTask()
{
 	instance = NULL;
}
*/

void CallGenerationTask::set_rate(double new_rate)
{

}

