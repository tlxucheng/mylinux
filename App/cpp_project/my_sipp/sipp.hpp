#ifndef __SIPP__
#define __SIPP__

/************************** Constants **************************/
#define SIPP_MAXFDS                65536
#define SIPP_MAX_MSG_SIZE          65536


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

/*********************** Global Sockets  **********************/
extern set<struct sipp_socket *> sockets_pending_reset;


#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

int open_connections();

#endif

