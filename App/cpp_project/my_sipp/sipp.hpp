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
#include "strings.hpp"
#include "infile.hpp"

/************************** Constants **************************/
#ifdef SVN_VERSION
# ifdef LOCAL_VERSION_EXTRA
#  define SIPP_VERSION               SVN_VERSION LOCAL_VERSION_EXTRA
# else
#  define SIPP_VERSION               SVN_VERSION
# endif
#else
# define SIPP_VERSION               "unknown"
#endif

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

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

#define TRANSPORT_TO_STRING(p)     ((p==T_TCP) ? "TCP" : ((p==T_TLS)? "TLS" : ((p==T_UDP)? "UDP" : "SCTP")))

/******************** Default parameters ***********************/
#define DEFAULT_RATE                 10.0
#define DEFAULT_PORT                 5060
#define DEFAULT_TRANSPORT            T_UDP

#define DEFAULT_SERVICE              ((char *)"service")
#define DEFAULT_AUTH_PASSWORD        ((char *)"password")

extern double             rate                    _DEFVAL(DEFAULT_RATE);

extern char               local_ip[40];

extern bool               local_ip_is_ipv6;
extern int                local_port              _DEFVAL(0);

extern int                max_recv_loops          _DEFVAL(MAX_RECV_LOOPS_PER_CYCLE);
extern int                max_sched_loops         _DEFVAL(MAX_SCHED_LOOPS_PER_CYCLE);

extern int                tcp_readsize            _DEFVAL(65535);

#define GET_TIME(clock)       \
{                             \
  struct timezone tzp;        \
  gettimeofday (clock, &tzp); \
}

/*********************** Global Sockets  **********************/
extern struct sipp_socket *main_socket            _DEFVAL(NULL);
extern set<struct sipp_socket *> sockets_pending_reset;
extern char          hostname[80];
extern struct        addrinfo * local_addr_storage;
extern struct        sockaddr_storage   local_sockaddr;
extern struct	     sockaddr_storage   remote_sockaddr;

extern short         use_remote_sending_addr      _DEFVAL(0);
extern struct        sockaddr_storage remote_sending_sockaddr;
extern int           user_port                    _DEFVAL(0);

/********************** Clock variables ***********************/

extern unsigned long clock_tick                   _DEFVAL(0);

/************ User controls and command line options ***********/
extern char               remote_host[255];
extern char               remote_ip[40];
extern char               remote_ip_escaped[42];
extern int                remote_port             _DEFVAL(DEFAULT_PORT);
extern char               local_ip_escaped[42];
extern int                transport               _DEFVAL(DEFAULT_TRANSPORT);
extern int                multisocket             _DEFVAL(0);

extern int                buff_size               _DEFVAL(65535);

extern unsigned long      stop_after              _DEFVAL(0xffffffff);

extern const char       * call_id_string          _DEFVAL("%u-%p@%s");
extern unsigned int       pid                     _DEFVAL(0);
extern unsigned int       base_cseq               _DEFVAL(0);

extern char               media_ip_escaped[42];
extern int                media_port              _DEFVAL(0);
extern bool               media_ip_is_ipv6;

extern const char       * service                 _DEFVAL(DEFAULT_SERVICE);
extern int                users                   _DEFVAL(-1);

extern char             **generic[100];
extern bool               pause_msg_ign           _DEFVAL(0);

int open_connections();

// extern field file management
typedef std::map<string, FileContents *> file_map;
extern file_map inFiles;
extern char *default_file _DEFVAL(NULL);

/********************* Mini-Parser Routines *******************/

int get_method(char *msg);
char * get_peer_tag(char *msg);
unsigned long int get_cseq_value(char *msg);
unsigned long get_reply_code(char *msg);

/********************* Reset global kludge  *******************/

#ifdef GLOBALS_FULL_DEFINITION
#undef extern
#endif

extern struct   sipp_socket *new_sipp_socket(bool use_ipv6, int transport);
extern void	sipp_customize_socket(struct sipp_socket *socket);
extern int	sipp_bind_socket(struct sipp_socket *socket, struct sockaddr_storage *saddr, int *port);

#endif  // __SIPP__

