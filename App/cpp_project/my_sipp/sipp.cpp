#define GLOBALS_FULL_DEFINITION

#include "sipp.hpp"
#include "sip_parser.hpp"
#include "socket.hpp"
#include "assert.h"
#include "logger.hpp"

/* start command
 * server: ./my_sipp -sn uas
 * clent:  ./my_sipp -sn uac 127.0.0.1
 *
 * 有限次数运行命令
 * server: ./my_sipp -sn uas
 * clent:  ./my_sipp -sn uac 127.0.0.1 -m 1
 *
 * 消息写入日志
 * server: ./my_sipp -sn uas -trace_msg
 * client: ./my_sipp -sn uac 127.0.0.1 -m 1 -trace_msg
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

/* 未解决问题
 * 2019-12-8
 * 1. 打印help程序如何自动退出的
 * 2. ERROR 函数产生coredump
 *
 *

/******************** Recv Poll Processing *********************/
extern int pollnfds;
extern struct sipp_socket  *sockets[SIPP_MAXFDS];
extern struct pollfd        pollfiles[SIPP_MAXFDS];

extern int pending_messages;

#define GLOBALS_FULL_DEFINITION

/***************** Option Handling Table *****************/
struct sipp_option {
    const char *option;
    const char *help;
    int type;
    void *data;
    /* Pass 0: Help and other options that should exit immediately. */
    /* Pass 1: All other options. */
    /* Pass 2: Scenario parsing. */
    int pass;
};

#define SIPP_OPTION_HELP	   1
#define SIPP_OPTION_INT		   2
#define SIPP_OPTION_SETFLAG	   3
#define SIPP_OPTION_UNSETFLAG	   4
#define SIPP_OPTION_STRING	   5
#define SIPP_OPTION_ARGI 	   6
#define SIPP_OPTION_TIME_SEC	   7
#define SIPP_OPTION_FLOAT	   8
#define SIPP_OPTION_BOOL	  10
#define SIPP_OPTION_VERSION	  11
#define SIPP_OPTION_TRANSPORT	  12
#define SIPP_OPTION_NEED_SSL	  13
#define SIPP_OPTION_IP		  14
#define SIPP_OPTION_MAX_SOCKET	  15
#define SIPP_OPTION_CSEQ	  16
#define SIPP_OPTION_SCENARIO	  17
#define SIPP_OPTION_RSA		  18
#define SIPP_OPTION_LIMIT	  19
#define SIPP_OPTION_USERS	  20
#define SIPP_OPTION_KEY		  21
#define SIPP_OPTION_3PCC	  22
#define SIPP_OPTION_TDMMAP	  23
#define SIPP_OPTION_TIME_MS	  24
#define SIPP_OPTION_SLAVE_CFG     25
#define SIPP_OPTION_3PCC_EXTENDED 26
#define SIPP_OPTION_INPUT_FILE	  27
#define SIPP_OPTION_TIME_MS_LONG  28
#define SIPP_OPTION_LONG          29
#define SIPP_OPTION_LONG_LONG     30
#define SIPP_OPTION_DEFAULTS      31
#define SIPP_OPTION_OOC_SCENARIO  32
#define SIPP_OPTION_INDEX_FILE    33
#define SIPP_OPTION_VAR		  34
#define SIPP_OPTION_RTCHECK	  35
#define SIPP_OPTION_LFNAME	  36
#define SIPP_OPTION_LFOVERWRITE	  37
#define SIPP_OPTION_PLUGIN	  38
#define SIPP_OPTION_NEED_SCTP	  39
#define SIPP_HELP_TEXT_HEADER	  255

/* Put each option, its help text, and type in this table. */
struct sipp_option options_table[] = {
    {"h", NULL, SIPP_OPTION_HELP, NULL, 0},		
    {"help", NULL, SIPP_OPTION_HELP, NULL, 0},

    {"trace_msg", "Displays sent and received SIP messages in <scenario file name>_<pid>_messages.log", SIPP_OPTION_SETFLAG, &useMessagef, 1},
	{
		"sn", "Use a default scenario (embedded in the SIPp executable). If this option is omitted, the Standard SipStone UAC scenario is loaded.\n"
		"Available values in this version:\n\n"
		"- 'uac'	  : Standard SipStone UAC (default).\n"
		"- 'uas'	  : Simple UAS responder.\n"
		"- 'regexp'   : Standard SipStone UAC - with regexp and variables.\n"
		"- 'branchc'  : Branching and conditional branching in scenarios - client.\n"
		"- 'branchs'  : Branching and conditional branching in scenarios - server.\n\n"
		"Default 3pcc scenarios (see -3pcc option):\n\n"
		"- '3pcc-C-A' : Controller A side (must be started after all other 3pcc scenarios)\n"
		"- '3pcc-C-B' : Controller B side.\n"
		"- '3pcc-A'   : A side.\n"
		"- '3pcc-B'   : B side.\n", SIPP_OPTION_SCENARIO, NULL, 2
	},
    {"r", "Set the call rate (in calls per seconds).  This value can be"
     "changed during test by pressing '+','_','*' or '/'. Default is 10.\n"
     "pressing '+' key to increase call rate by 1 * rate_scale,\n"
     "pressing '-' key to decrease call rate by 1 * rate_scale,\n"
     "pressing '*' key to increase call rate by 10 * rate_scale,\n"
     "pressing '/' key to decrease call rate by 10 * rate_scale.\n",
     SIPP_OPTION_FLOAT, &rate, 1},
    {"m", "Stop the test and exit when 'calls' calls are processed", SIPP_OPTION_LONG, &stop_after, 1},
};

/* Command line parsing */
#define REQUIRE_ARG() if((++argi) >= argc) { ERROR("Missing argument for param '%s'.\n" \
				     "Use 'sipp -h' for details",  argv[argi - 1]); }
#define CHECK_PASS() if (option->pass != pass) { break; }


void help()
{
	printf("need two para.");
}

struct sipp_option *find_option(const char *option) {
    int i;
    int max = sizeof(options_table)/sizeof(options_table[0]);

    /* Allow options to start with '-' or '--' */
    if (option[0] != '-') {
        return NULL;
    }
    option++;
    if (option[0] == '-') {
        option++;
    }

    for (i = 0; i < max; i++) {
        if (!strcmp(options_table[i].option, option)) {
            return &(options_table[i]);
        }
    }

    return NULL;
};

/* 替换sipp中实现，可以实现一次invite---200OK交互 */
void pollset_process(int wait)
{
    int rs; /* Number of times to execute recv().
	     For TCP with 1 socket per call:
	         no. of events returned by poll
	     For UDP and TCP with 1 global socket:
	         recv_count is a flag that stays up as
	         long as there's data to read */
	         
    int loops = max_recv_loops;

    /* What index should we try reading from? */
    static int read_index;
	
    // If not using epoll, we have a queue of pending messages to spin through.

    if (read_index >= pollnfds) {
        read_index = 0;
    }

    /* Get socket events. */
    rs = poll(pollfiles, pollnfds, wait ? 1 : 0);
    if((rs < 0) && (errno == EINTR)) {
        return;
    }

    /* We need to flush all sockets and pull data into all of our buffers. */
    for (int poll_idx = 0; rs > 0 && poll_idx < pollnfds; poll_idx++)
	{
        struct sipp_socket *sock = sockets[poll_idx];
        int events = 0;
        int ret = 0;
		
        assert(sock);
		
        if (pollfiles[poll_idx].revents & POLLIN) 
		{
            /* We can empty this socket. */ 
	        empty_socket(sock);
            events++;
        }

	    if (events) 
		{
	        rs--;
	    }
	
    	pollfiles[poll_idx].revents = 0;
    }

    if (read_index >= pollnfds) {
        read_index = 0;
    }
  
    /* We need to process any new messages that we read. */
    while (pending_messages && (loops > 0)) {
        //getmilliseconds();

        if (sockets[read_index]->ss_msglen) {
            char msg[SIPP_MAX_MSG_SIZE];
            struct sockaddr_storage src;
            ssize_t len;

            len = read_message(sockets[read_index], msg, sizeof(msg), &src);
            if (len > 0) {
                process_message(sockets[read_index], msg, len, &src);
            } else {
                assert(0);
            }
            loops--;
        }
        read_index = (read_index + 1) % pollnfds;
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

    /* Initialize the tolower table. */
    init_tolower_table();

    for(pass = 0 ; pass <= 3; pass++)       /* pass循环的作用是什么? */
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
				ERROR("Invalid argument: '%s'.\n" "Use 'sipp -h' for details", argv[argi]);
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
					REQUIRE_ARG();
					CHECK_PASS();
					if(main_scenario)
					{
						ERROR("Internal error, main_scenario already set");
					}
                    else if(!strcmp(argv[argi-1], "-sn"))
					{
						i = find_scenario(argv[argi]);
						/* set_scenario(argv[argi]); */
						main_scenario = new scenario(0, i);
						scenario_file = new char [strlen(argv[argi])+1] ;
                        sprintf(scenario_file,"%s", argv[argi]);
						/* main_scenario->stats->setFileName(scenario_file, ".csv"); */
						
					}
					/* 此时加上会走到下面一个break, 原因没有查找 */
					//else 
					//{
			        //	ERROR("Internal error, I don't recognize %s as a scenario option\n", argv[argi] - 1);
			        //}
					break;
				case SIPP_OPTION_LONG:
					REQUIRE_ARG();
					CHECK_PASS();
					*((long*)option->data) = get_long(argv[argi], argv[argi-1]);
					break;
		        case SIPP_OPTION_SETFLAG:
					REQUIRE_ARG();
					CHECK_PASS();
					*((bool *)option->data) = true;
					break;
				default:
					break;
					ERROR("Internal error: I don't recognize the option type for %s", argv[argi]);				   
			}
		}
    }

	/* 操作log相关 */	
	if(useMessagef == 1) {
		rotate_messagef();
	}

	/* 是否需要调用 */
    init_default_messages();

	TRACE_MSG("start main_scenario->runInit().\n");

	main_scenario->runInit();
	
	main_scenario->computeSippMode();

	if(creationMode == MODE_CLIENT) 
    {	    	
		CallGenerationTask::initialize();
		CallGenerationTask::set_rate(rate);
    }

	open_connections();

    /* 用于命令行命令接受socket，暂时不使用 */
	//setup_ctrl_socket();
	
	traffic_thread();

    return 0;
}

