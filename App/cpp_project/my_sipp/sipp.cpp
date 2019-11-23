#define GLOBALS_FULL_DEFINITION

#include "sipp.hpp"
#include "sip_parser.hpp"
#include "socket.hpp"
#include "assert.h"

/* start command
 * server: ./sipp -sn uas
 * clent:  ./sipp -sn uac 127.0.0.1
 */

/******************** Recv Poll Processing *********************/

extern struct sipp_socket  *sockets[SIPP_MAXFDS];

#define GLOBALS_FULL_DEFINITION

void help()
{
	printf("need two para.");
}

void pollset_process(int wait)
{	
    int loops = max_recv_loops;
	
    static int 			      read_index;
	char                      msg[SIPP_MAX_MSG_SIZE];
	struct sockaddr_storage   src;
	
	ssize_t len = read_message(sockets[read_index], msg, sizeof(msg), &src);
	if (len > 0) {
		process_message(sockets[read_index], msg, len, &src);
	} else {
		assert(0);
	}

}

void traffic_thread()
{
	while(1)
	{
	    /*
		while (sockets_pending_reset.begin() != sockets_pending_reset.end())
		{
            reset_connection(*(sockets_pending_reset.begin()));
            sockets_pending_reset.erase(sockets_pending_reset.begin());
        }
        */
		
        /* Schedule all pending calls and process their timers */
        task_list *running_tasks;

        /* We should never get so busy with running calls that we can't process some messages. */
        int loops = max_sched_loops;

		/* Now we process calls that are on the run queue. */
        running_tasks = get_running_tasks();

		task * last = NULL;

        task_list::iterator iter;
        for(iter = running_tasks->begin(); iter != running_tasks->end(); iter++) {
            if(last) {
                last -> run();
                if (sockets_pending_reset.begin() != sockets_pending_reset.end()) {
                    last = NULL;
                    break;
                }
            }
            last = *iter;
            if (--loops <= 0) {
                break;
            }
        }
        if(last) {
            last -> run();
        }

		/*
        while (sockets_pending_reset.begin() != sockets_pending_reset.end()) {
            reset_connection(*(sockets_pending_reset.begin()));
            sockets_pending_reset.erase(sockets_pending_reset.begin());
        }
        */
		
        pollset_process(running_tasks->empty());
	}
}

int main(int argc, char *argv[])
{
    int argi = 0;
	int i    = 0;

    if(argc < 2)
	{
		help();
		exit(EXIT_OTHER);
    }

	for(argi = 1; argi < argc; argi++)
	{
		if(!strcmp(argv[argi - 1], "-sn"))
		{
			i = find_scenario(argv[argi]);
			main_scenario = new scenario(0, i);
		}
		else 
		{
        	ERROR("Internal error, I don't recognize %s as a scenario option\n", argv[argi] - 1);
        }
	}

	main_scenario->runInit();
	
	main_scenario->computeSippMode();
	
	if (creationMode == MODE_CLIENT) 
    {	    	
		CallGenerationTask::initialize();
		CallGenerationTask::set_rate(rate);
    }

	open_connections();

	setup_ctrl_socket();

	traffic_thread();

    return 0;
}

