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

/************************** Constants **************************/
#define SIPP_MAXFDS                65536
#define SIPP_MAX_MSG_SIZE          65536

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
extern int                tcp_readsize            _DEFVAL(65535);

/*********************** Global Sockets  **********************/
extern set<struct sipp_socket *> sockets_pending_reset;

extern short         use_remote_sending_addr      _DEFVAL(0);

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

int open_connections();

#endif

