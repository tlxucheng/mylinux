#ifndef __SIPP_SOCKET_H__
#define __SIPP_SOCKET_H__

#include <sys/socket.h>

ssize_t read_message(struct sipp_socket *socket, char *buf, size_t len, struct sockaddr_storage *src);

void setup_ctrl_socket();
void process_message(struct sipp_socket *socket, char *msg, ssize_t msg_size, struct sockaddr_storage *src);

/* This is an abstraction of a socket, which provides buffers for input and
 * output. */
struct sipp_socket {
    int  ss_count; /* How many users are there of this socket? */

    int ss_transport; /* T_TCP, T_UDP, or T_TLS. */
    bool ss_ipv6;
    bool ss_control; /* Is this a control socket? */
    bool ss_call_socket; /* Is this a call socket? */
    bool ss_changed_dest; /* Has the destination changed from default. */

    int ss_fd;	/* The underlying file descriptor for this socket. */
    void *ss_comp_state; /* The compression state. */
    struct sockaddr_storage ss_remote_sockaddr; /* Who we are talking to. */
    struct sockaddr_storage ss_dest; /* Who we are talking to. */


    int ss_pollidx; /* The index of this socket in our poll structures. */
    bool ss_congested; /* Is this socket congested? */
    bool ss_invalid; /* Has this socket been closed remotely? */

    struct socketbuf *ss_in; /* Buffered input. */
    size_t ss_msglen;	/* Is there a complete SIP message waiting, and if so how big? */
    struct socketbuf *ss_out; /* Buffered output. */
};

/* Socket Buffer Management. */
#define NO_COPY 0
#define DO_COPY 1
struct socketbuf *alloc_socketbuf(char *buffer, size_t size, int copy);
void free_socketbuf(struct socketbuf *socketbuf);

struct socketbuf {
    char *buf;
    size_t len;
    size_t offset;
    struct sockaddr_storage addr;
    struct socketbuf *next;
};

#if defined (__hpux) || defined (__alpha) && !defined (__FreeBSD__)
#define sipp_socklen_t  int
#else
#define sipp_socklen_t  socklen_t
#endif

int write_socket(struct sipp_socket *socket, const char *buffer, ssize_t len, int flags, struct sockaddr_storage *dest);
char * get_inet_address(struct sockaddr_storage * addr);
int empty_socket(struct sipp_socket *socket);

#define WS_BUFFER 2 /* Buffer the message if there is no room for writing the message. */

#define SOCK_ADDR_SIZE(a) \
  (((a)->ss_family == AF_INET) ? sizeof(struct sockaddr_in) \
                               : sizeof(struct sockaddr_in6))

#if defined(__cplusplus) && defined (__hpux)
#define _RCAST(type, val) (reinterpret_cast<type> (val))
#else
#define _RCAST(type, val) ((type)(val))
#endif

#endif /* __SIPP_SOCKET_H__ */

