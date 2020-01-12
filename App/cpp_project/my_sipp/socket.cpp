#include <stdlib.h>
#include <unistd.h>
#include "sipp.hpp"
#include "socket.hpp"

/******************** Recv Poll Processing *********************/

int pollnfds;
struct pollfd        pollfiles[SIPP_MAXFDS];
struct sipp_socket  *sockets[SIPP_MAXFDS];

int pending_messages = 0;

extern char * get_call_id(char *msg);

int open_connections()
{	
    int status = 0;

	if(!strlen(remote_host))
	{
		if((sendMode != MODE_SERVER)) 
		{
            ERROR("Missing remote host parameter. This scenario requires it");
		}
	}
	else 
	{
        /* client端执行 */
		int temp_remote_port = 0;
        get_host_and_port(remote_host, remote_host, &temp_remote_port);
	    if (temp_remote_port != 0) {
            remote_port = temp_remote_port;   //remote_port 默认5060
        }

		/* Resolving the remote IP */
		struct addrinfo   hints;
		struct addrinfo * local_addr;

		memset((char*)&hints, 0, sizeof(hints));
		hints.ai_flags	= AI_PASSIVE;
		hints.ai_family = PF_UNSPEC;
		
		if (getaddrinfo(remote_host,
						NULL,
						&hints,
						&local_addr) != 0) {
			ERROR("Unknown remote host '%s'.\n"
				  "Use 'sipp -h' for details", remote_host);
		}
	
		memset(&remote_sockaddr, 0, sizeof( remote_sockaddr ));
		memcpy(&remote_sockaddr,
			   local_addr->ai_addr,
			   SOCK_ADDR_SIZE(
				   _RCAST(struct sockaddr_storage *,local_addr->ai_addr)));
		
		freeaddrinfo(local_addr);

	    strcpy(remote_ip, get_inet_address(&remote_sockaddr));
            if (remote_sockaddr.ss_family == AF_INET) {
                (_RCAST(struct sockaddr_in *, &remote_sockaddr))->sin_port =
                    htons((short)remote_port);
                strcpy(remote_ip_escaped, remote_ip);
            } else {
                (_RCAST(struct sockaddr_in6 *, &remote_sockaddr))->sin6_port =
                    htons((short)remote_port);
                sprintf(remote_ip_escaped, "[%s]", remote_ip);
        }
	}

	if(gethostname(hostname,64) != 0) {
        ERROR_NO("Can't get local hostname in 'gethostname(hostname,64)'");
    }

    /* client和server端都执行 */
	/* Resolving the local IP */
    char            * local_host = NULL;
    struct addrinfo * local_addr;
    struct addrinfo   hints;

    if (!strlen(local_ip)) {
        local_host = (char *)hostname;
    } else {
        local_host = (char *)local_ip;
    }

    memset((char*)&hints, 0, sizeof(hints));
    hints.ai_flags  = AI_PASSIVE;
    hints.ai_family = PF_UNSPEC;

    /* Resolving local IP */
    if (getaddrinfo(local_host, NULL, &hints, &local_addr) != 0) {
        ERROR("Can't get local IP address in getaddrinfo, local_host='%s', local_ip='%s'",
              local_host,
              local_ip);
    }
    // store local addr info for rsa option
    getaddrinfo(local_host, NULL, &hints, &local_addr_storage);

    memset(&local_sockaddr,0,sizeof(struct sockaddr_storage));
    local_sockaddr.ss_family = local_addr->ai_addr->sa_family;

    if (!strlen(local_ip)) {
        strcpy(local_ip,
               get_inet_address(
                   _RCAST(struct sockaddr_storage *, local_addr->ai_addr)));
    } else {
        memcpy(&local_sockaddr,
               local_addr->ai_addr,
               SOCK_ADDR_SIZE(
                   _RCAST(struct sockaddr_storage *,local_addr->ai_addr)));
    }
    freeaddrinfo(local_addr);

    if (local_sockaddr.ss_family == AF_INET6) {
        local_ip_is_ipv6 = true;
        sprintf(local_ip_escaped, "[%s]", local_ip);
    } else {
        strcpy(local_ip_escaped, local_ip);
    }
	
    /* Creating and binding the local socket */
    if ((main_socket = new_sipp_socket(local_ip_is_ipv6, transport)) == NULL) {
        ERROR_NO("Unable to get the local socket");
    }

    sipp_customize_socket(main_socket);

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

    /* Do we have a complete SIP message? */
    if (!socket->ss_msglen) {
        //if (int msg_len = check_for_message(socket)) {
            //socket->ss_msglen = msg_len;
            pending_messages++;
        //}
    }
	return ret;
}

struct sipp_socket *sipp_allocate_socket(bool use_ipv6, int transport, int fd, int accepting) {
	struct sipp_socket *ret = (struct sipp_socket *)malloc(sizeof(struct sipp_socket));
	if (!ret) {
	    ERROR("Could not allocate a sipp_socket structure.");
	}
	memset(ret, 0, sizeof(struct sipp_socket));

	ret->ss_transport = transport;
	ret->ss_control = false;
	ret->ss_ipv6 = use_ipv6;
	ret->ss_fd = fd;
	ret->ss_comp_state = NULL;
	ret->ss_count = 1;
	ret->ss_changed_dest = false;

	/* Initialize all sockets with our destination address. */
	memcpy(&ret->ss_remote_sockaddr, &remote_sockaddr, sizeof(ret->ss_remote_sockaddr));

	ret->ss_in = NULL;
	ret->ss_out = NULL;
	ret->ss_msglen = 0;
	ret->ss_congested = false;
	ret->ss_invalid = false;

	/* Store this socket in the tables. */
	ret->ss_pollidx = pollnfds++;
	sockets[ret->ss_pollidx] = ret;

	pollfiles[ret->ss_pollidx].fd      = ret->ss_fd;
	pollfiles[ret->ss_pollidx].events  = POLLIN | POLLERR;
	pollfiles[ret->ss_pollidx].revents = 0;

    return ret;
}


static struct sipp_socket *sipp_allocate_socket(bool use_ipv6, int transport, int fd) {
    return sipp_allocate_socket(use_ipv6, transport, fd, 0);
}

int socket_fd(bool use_ipv6, int transport)
{
	int socket_type = -1;
    int protocol=0;
    int fd;

	
    switch(transport) {
	case T_UDP:
		socket_type = SOCK_DGRAM;
        protocol=IPPROTO_UDP;
        break;
    }

	if((fd = socket(use_ipv6 ? AF_INET6 : AF_INET, socket_type, protocol))== -1) {
        ERROR("Unable to get a %s socket (3)", TRANSPORT_TO_STRING(transport));
    }

	return fd;
}

struct sipp_socket *new_sipp_socket(bool use_ipv6, int transport) 
{
    struct sipp_socket *ret;
    int fd = socket_fd(use_ipv6, transport);

	ret  = sipp_allocate_socket(use_ipv6, transport, fd);
    if (!ret) {
        close(fd);
        ERROR("Could not allocate new socket structure!");
    }

	return ret;
}

void sipp_customize_socket(struct sipp_socket *socket)
{
    unsigned int buffsize = buff_size;

    /* Allows fast TCP reuse of the socket */
    if (socket->ss_transport == T_TCP || socket->ss_transport == T_TLS ||
            socket->ss_transport == T_SCTP) {

	}

	/* Increase buffer sizes for this sockets */
    if(setsockopt(socket->ss_fd,
                  SOL_SOCKET,
                  SO_SNDBUF,
                  &buffsize,
                  sizeof(buffsize))) {
        ERROR_NO("Unable to set socket sndbuf");
    }

    buffsize = buff_size;
    if(setsockopt(socket->ss_fd,
                  SOL_SOCKET,
                  SO_RCVBUF,
                  &buffsize,
                  sizeof(buffsize))) {
        ERROR_NO("Unable to set socket rcvbuf");
    }
}

char * get_inet_address(struct sockaddr_storage * addr)
{
    static char * ip_addr = NULL;

    if (!ip_addr) {
        ip_addr = (char *)malloc(1024*sizeof(char));
    }
    if (getnameinfo(_RCAST(struct sockaddr *, addr),
                    SOCK_ADDR_SIZE(addr),
                    ip_addr,
                    1024,
                    NULL,
                    0,
                    NI_NUMERICHOST) != 0) {
        strcpy(ip_addr, "addr not supported");
    }

    return ip_addr;
}


