#ifndef __SIPP_SOCKET_H__
#define __SIPP_SOCKET_H__

struct sipp_socket {
	
    int ss_transport; /* T_TCP, T_UDP, or T_TLS. */
};

struct socketbuf {
    char *buf;
    size_t len;
    size_t offset;
    struct sockaddr_storage addr;
    struct socketbuf *next;
};

int write_socket(struct sipp_socket *socket, const char *buffer, ssize_t len, int flags, struct sockaddr_storage *dest);

#define WS_BUFFER 2 /* Buffer the message if there is no room for writing the message. */

#endif /* __SIPP_SOCKET_H__ */

