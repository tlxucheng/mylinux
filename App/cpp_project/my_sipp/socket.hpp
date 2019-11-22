#ifndef __SIPP_SOCKET_H__
#define __SIPP_SOCKET_H__

#include <sys/socket.h>

struct sipp_socket {
	
    int ss_transport; 			/* T_TCP, T_UDP, or T_TLS. */
	int ss_fd;					/* The underlying file descriptor for this socket. */
	
    struct socketbuf *ss_in; 	/* Buffered input. */
    struct socketbuf *ss_out; 	/* Buffered output. */
};

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

#define WS_BUFFER 2 /* Buffer the message if there is no room for writing the message. */

#define SOCK_ADDR_SIZE(a) \
  (((a)->ss_family == AF_INET) ? sizeof(struct sockaddr_in) \
                               : sizeof(struct sockaddr_in6))

#endif /* __SIPP_SOCKET_H__ */

