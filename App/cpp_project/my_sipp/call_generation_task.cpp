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

bool CallGenerationTask::run()
{
    /* 先不加while(calls_to_open--)，只跑一次消息交互 */
    int userid = 0;

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

