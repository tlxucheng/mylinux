#ifndef CALLGENERATIONTASK_HPP
#define CALLGENERATIONTASK_HPP

#include "task.hpp"

#endif

class CallGenerationTask : public task 
{
public:	
    static void initialize();
    static void set_rate(double new_rate);

    bool run();

protected:
    unsigned int wake();
    
private:
    CallGenerationTask();
    virtual ~CallGenerationTask();

	static class CallGenerationTask *instance;
	static unsigned long calls_since_last_rate_change;
	static unsigned long last_rate_change_time;
};



