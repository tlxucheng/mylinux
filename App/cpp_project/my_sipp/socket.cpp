#include <stdlib.h>
#include <unistd.h>
#include "sipp.hpp"
#include "socket.hpp"

struct sipp_socket  *sockets[SIPP_MAXFDS];

extern char * get_call_id(char *msg);

int open_connections()
{	
    int status = 0;

	return status;
}

void setup_ctrl_socket()
{

}

int send_nowait(int s, const void *msg, int len, int flags)
{
	int rc;

    rc = send(s, msg, len, flags);

	return rc;
}

static ssize_t socket_write_primitive(struct sipp_socket *socket, const char *buffer, size_t len, struct sockaddr_storage *dest)
{
    ssize_t rc;

	switch(socket->ss_transport) {
		case T_TLS:
			break;
		case T_SCTP:
			break;
		case T_TCP:		
			rc = send_nowait(socket->ss_fd, buffer, len, 0);
			break;
		case T_UDP:
			rc = sendto(socket->ss_fd, buffer, len, 0, (struct sockaddr *)dest, SOCK_ADDR_SIZE(dest));
			break;
		default:
			ERROR("Internal error, unknown transport type %d\n", socket->ss_transport);
		}

	return rc;
}

int write_socket(struct sipp_socket *socket, const char *buffer, ssize_t len, int flags, struct sockaddr_storage *dest)
{
	int rc;

	if(NULL == socket)
	{
		return 0;
	}

    rc = socket_write_primitive(socket, buffer, len, dest);

	return rc;
}

ssize_t read_message(struct sipp_socket *socket, char *buf, size_t len, struct sockaddr_storage *src)
{
    size_t avail;

    memcpy(buf, socket->ss_in->buf + socket->ss_in->offset, avail);
    memcpy(src, &socket->ss_in->addr, SOCK_ADDR_SIZE(&socket->ss_in->addr));

	return avail;
}

void process_message(struct sipp_socket *socket, char *msg, ssize_t msg_size, struct sockaddr_storage *src)
{	
    char *call_id = get_call_id(msg);

    listener *listener_ptr = get_listener(call_id);

	listener_ptr -> process_incoming(msg, src);

}

void buffer_read(struct sipp_socket *socket, struct socketbuf *newbuf)
{
    struct socketbuf *buf = socket->ss_in;
    struct socketbuf *prev = buf;

    if (!buf) {
        socket->ss_in = newbuf;
        return;
    }

    while(buf->next) {
        prev = buf;
        buf = buf->next;
    }

    prev->next = newbuf;
}

int empty_socket(struct sipp_socket *socket)
{
    int ret = -1;
    int readsize=0;

	if (socket->ss_transport == T_UDP || socket->ss_transport == T_SCTP) {
        readsize = SIPP_MAX_MSG_SIZE;
    } else {
        readsize = tcp_readsize;
    }

    struct socketbuf *socketbuf;
    char *buffer;
	
    sipp_socklen_t addrlen = sizeof(struct sockaddr_storage);

	buffer = (char *)malloc(readsize);
    if (!buffer) {
        ERROR("Could not allocate memory for read!");
    }

    switch(socket->ss_transport) {
    case T_TCP:
    case T_UDP:
        ret = recvfrom(socket->ss_fd, buffer, readsize, 0, (struct sockaddr *)&socketbuf->addr,  &addrlen);
        break;
    case T_TLS:
		break;
	case T_SCTP:
		break;

	}
	
    buffer_read(socket, socketbuf);

	return ret;
}

