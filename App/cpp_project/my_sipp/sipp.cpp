#define GLOBALS_FULL_DEFINITION

#include "sipp.hpp"
#include "sip_parser.hpp"
#include "socket.hpp"
#include "assert.h"

/* start command
 * server: ./sipp -sn uas
 * clent:  ./sipp -sn uac 127.0.0.1
 *
 * 有限次数运行命令
 * server: ./sipp -sn uas
 * clent:  ./sipp -sn uac 127.0.0.1 -m 1
 *
 * 消息写入日志
 * server: ./sipp -sn uas -trace_msg
 * client: ./sipp -sn uac 127.0.0.1 -m 1 -trace_msg
 *
 * 进程启动流程
 * 1. 命令行解析
 * 2. 调用构造函数scenario(解析默认xml---->构造SendingMessage类----->解析出来需要替换的关键字)
 * 3. 调用main_scenario->runInit()，构造call类
 * 4. 初始化 CallGenerationTask 类, 根据rate创建任务
 * 5. open_connections();
 * 6. setup_ctrl_socket(); 用于接收进程运行时的命令
 * 7. traffic_thread(); 循环执行已构造的任务
 */

/* open_connections()函数流程分析
 * 解析命令函数的IP和Port
 * client端生成 local_sockaddr ----->创建 main_socket
 * erver端创建 socket--->local_sockaddr--->创建 main_socket
 */

/* setup_ctrl_socket()流程分析 
 */

/* 
 * 发包流程分析
 * main_scenario->runInit()---> connect_socket_if_needed()---->associate_socket(new_sipp_call_socket)
 * new call()-----> executeMessage()--->send_scene()--->send_raw()
 * call::init ---> associate_socket();
 * CallGenerationTask::run ---> call_ptr->associate_socket(main_socket);
 */

/*
 * logger流程分析
 * TRACE_MSG()
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
    int 				argi 	= 0;
	int 				i    	= 0;
    int 				pass 	= 0;
	struct  sipp_option *option = NULL;

    if(argc < 2)
	{
		help();
		exit(EXIT_OTHER);
    }

    for(pass = 0 ; pass <= 3; pass++)
    {
		for(argi = 1; argi < argc; argi++)
		{
		    option = find_option(argv[argi]);
            if(!option)
        	{
        		if (argv[argi][0] != '-') {
                    strncpy(remote_host, argv[argi], sizeof(remote_host) - 1);
                    continue;
        		}

				help();
				ERROR("Invalid argument: '%s'.\n"
                      "Use 'sipp -h' for details", argv[argi]);
        	}

			switch(option->type)
			{
				case SIPP_OPTION_HELP:
					exit(EXIT_OTHER);
				case SIPP_OPTION_INT:
					break;
				case SIPP_OPTION_TRANSPORT:
					break;
				case SIPP_OPTION_SCENARIO:
					if(main_scenario)
					{
						ERROR("Internal error, main_scenario already set");
					}
					else if(!strcmp(argv[argi - 1], "-sn"))
					{
						i = find_scenario(argv[argi]);
						//set_scenario(argv[argi]);
						main_scenario = new scenario(0, i);
						 //main_scenario->stats->setFileName(scenario_file, ".csv");
						
					}
					else 
					{
			        	ERROR("Internal error, I don't recognize %s as a scenario option\n", argv[argi] - 1);
			        }
					break;
				case SIPP_OPTION_INT:
					break;
				case SIPP_OPTION_LONG:
					*((long*)option->data) = get_long(argv[argi], argv[argi-1]);
					break;
				default
					ERROR("Internal error: I don't recognize the option type for %s", argv[argi]);				   
			}
		}
    }

	/* 操作log相关 */

	/* 是否需要调用 */
    init_default_messages();

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

