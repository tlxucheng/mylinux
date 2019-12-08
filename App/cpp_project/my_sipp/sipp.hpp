#ifndef __SIPP__
#define __SIPP__

/* Std C includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <ctype.h>
#include <signal.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <math.h>

/* Sipp includes */

#include "xp_parser.h"
#include "scenario.hpp"
#include "screen.hpp"
#include "task.hpp"
#include "listener.hpp"
#include "socketowner.hpp"
#include "socket.hpp"
#include "call.hpp"
#include "stat.hpp"
#include "call_generation_task.hpp"
#include "logger.hpp"

/************************** Constants **************************/
#define SIPP_MAXFDS                65536
#define SIPP_MAX_MSG_SIZE          65536

#define MAX_RECV_LOOPS_PER_CYCLE   1000
#define MAX_SCHED_LOOPS_PER_CYCLE  1000
#define NB_UPDATE_PER_CYCLE        1

#ifdef GLOBALS_FULL_DEFINITION
#define extern
#define _DEFVAL(value) = value
#else
#define _DEFVAL(value)
#endif

#define DEFAULT_RATE                 10.0

extern double             rate                    _DEFVAL(DEFAULT_RATE);

extern char               local_ip[40];

extern bool               local_ip_is_ipv6;
extern int                local_port              _DEFVAL(0);

extern int                max_recv_loops          _DEFVAL(MAX_RECV_LOOPS_PER_CYCLE);
extern int                max_sched_loops         _DEFVAL(MAX_SCHED_LOOPS_PER_CYCLE);

extern int                tcp_readsize            _DEFVAL(65535);

/*********************** Global Sockets  **********************/
extern set<struct sipp_socket *> sockets_pending_reset;

extern short         use_remote_sending_addr      _DEFVAL(0);

/********************** Clock variables ***********************/

extern unsigned long clock_tick                   _DEFVAL(0);

/************ User controls and command line options ***********/
extern char               remote_host[255];

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

int open_connections();

/********************* Reset global kludge  *******************/

#ifdef GLOBALS_FULL_DEFINITION
#undef extern
#endif

#endif  // __SIPP__

