#include "sipp.hpp"

class CallGenerationTask *CallGenerationTask::instance = NULL;
unsigned long CallGenerationTask::calls_since_last_rate_change = 0;
unsigned long CallGenerationTask::last_rate_change_time = 0;

void CallGenerationTask::initialize()
{
    assert(instance == NULL);
    instance = new CallGenerationTask();
}

CallGenerationTask::CallGenerationTask()
{
    setRunning();
}

CallGenerationTask::~CallGenerationTask()
{
 	instance = NULL;
}

unsigned int CallGenerationTask::wake() {
    int retval;
#if 0
    if (paused || (users >= 0)) {
        // When paused or when we're doing user-based rather than
        // rate-based calls, return a sentinel value to indicate that
        // this task should wait forever before rescheduling.
        retval = DONT_RESCHEDULE;
    } else {
        float ms_per_call = rate_period_ms/MAX(rate, 1);
        /* We need to compute when the next call is going to be
         * opened. The current time is the time when the rate last
         * changed, plus the number of calls since then multiplied by
         * the number of milliseconds between each call.
         *
         * We then add the number of milliseconds between each call to that
         * figure. */

        retval = (unsigned long) last_rate_change_time +
            (calls_since_last_rate_change * ms_per_call) + ms_per_call;

        /* On startup, when last_rate_change_time is 0, this
        calculation can be 0 (if we're opening multiple calls per ms).
        But 0 indicates that we should wait forever, so avoid that and
        return 1 instead. */
        if (retval == 0 /* DONT_RESCHEDULE */) {
          retval = 1;
        }
  }
#endif
    
  return retval;
}

extern int g_test_one_send;
bool CallGenerationTask::run()
{
    /* 先不加while(calls_to_open--)，只跑一次消息交互 */
    int userid = 0;

    if (g_test_one_send) {
        delete this;
        return false;
    }

    call* call_ptr = call::add_call(userid,
                                 local_ip_is_ipv6,
                                 use_remote_sending_addr ? &remote_sending_sockaddr : &remote_sockaddr);
    if(!call_ptr) {
        ERROR("Out of memory allocating call!");
    }

    // outbound_congestion = false; Statistics

    if (!multisocket) {
        switch(transport) {
        case T_UDP:
            call_ptr->associate_socket(main_socket);
            main_socket->ss_count++;
            break;
        /*
        case T_TCP:
        case T_SCTP:
        case T_TLS:
            call_ptr->associate_socket(tcp_multiplex);
            tcp_multiplex->ss_count++;
            break;
        */
        }
    }

	return true;
}

void CallGenerationTask::set_rate(double new_rate)
{

}

