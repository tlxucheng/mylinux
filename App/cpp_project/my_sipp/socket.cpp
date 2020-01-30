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
        /* client��ִ�� */
		int temp_remote_port = 0;
        get_host_and_port(remote_host, remote_host, &temp_remote_port);
	    if (temp_remote_port != 0) {
            remote_port = temp_remote_port;   //remote_port Ĭ��5060
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

    /* client��server�˶�ִ�� */
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

    /* Trying to bind local port */
    char peripaddr[256];
    if(!user_port) {
        unsigned short l_port;
        for(l_port = DEFAULT_PORT;
                l_port < (DEFAULT_PORT + 60);
                l_port++) {

            // Bind socket to local_ip
#if 0            
            if (bind_local || peripsocket) {
                struct addrinfo * local_addr;
                struct addrinfo   hints;
                memset((char*)&hints, 0, sizeof(hints));
                hints.ai_flags  = AI_PASSIVE;
                hints.ai_family = PF_UNSPEC;

                if (peripsocket) {
                    // On some machines it fails to bind to the self computed local
                    // IP address.
                    // For the socket per IP mode, bind the main socket to the
                    // first IP address specified in the inject file.
                    inFiles[ip_file]->getField(0, peripfield, peripaddr, sizeof(peripaddr));
                    if (getaddrinfo(peripaddr,
                                    NULL,
                                    &hints,
                                    &local_addr) != 0) {
                        ERROR("Unknown host '%s'.\n"
                              "Use 'sipp -h' for details", peripaddr);
                    }
                } else {
                    if (getaddrinfo(local_ip,
                                    NULL,
                                    &hints,
                                    &local_addr) != 0) {
                        ERROR("Unknown host '%s'.\n"
                              "Use 'sipp -h' for details", peripaddr);
                    }
                }
                memcpy(&local_sockaddr,
                       local_addr->ai_addr,
                       SOCK_ADDR_SIZE(
                           _RCAST(struct sockaddr_storage *, local_addr->ai_addr)));
                freeaddrinfo(local_addr);
            }
#endif
            if (local_ip_is_ipv6) {
                (_RCAST(struct sockaddr_in6 *, &local_sockaddr))->sin6_port
                    = htons((short)l_port);
            } else {
                (_RCAST(struct sockaddr_in *, &local_sockaddr))->sin_port
                    = htons((short)l_port);
            }
            if(sipp_bind_socket(main_socket, &local_sockaddr, &local_port) == 0) {
                break;
            }
        }
    }

	return status;
}

int sipp_bind_socket(struct sipp_socket *socket, struct sockaddr_storage *saddr, int *port)
{
    int ret;
    int len;


#ifdef USE_SCTP
    if (transport==T_SCTP && multisocket==1 && *port==-1) {
        if (socket->ss_ipv6) {
            (_RCAST(struct sockaddr_in6 *, saddr))->sin6_port=0;
        } else {
            (_RCAST(struct sockaddr_in *, saddr))->sin_port=0;
        }
    }
#endif

    if (socket->ss_ipv6) {
        len = sizeof(struct sockaddr_in6);
    } else {
        len = sizeof(struct sockaddr_in);
    }

    if((ret = bind(socket->ss_fd, (sockaddr *)saddr, len))) {
        return ret;
    }

    if (!port) {
        return 0;
    }

    if ((ret = getsockname(socket->ss_fd, (sockaddr *)saddr, (sipp_socklen_t *) &len))) {
        return ret;
    }

    if (socket->ss_ipv6) {
        *port = ntohs((short)((_RCAST(struct sockaddr_in6 *, saddr))->sin6_port));
    } else {
        *port = ntohs((short)((_RCAST(struct sockaddr_in *, saddr))->sin_port));
    }

#ifdef USE_SCTP
    bool isany=false;

    if (socket->ss_ipv6) {
        if (memcmp(&(_RCAST(struct sockaddr_in6 *, saddr)->sin6_addr),&in6addr_any,sizeof(in6_addr))==0) isany=true;
    } else {
        isany= (_RCAST(struct sockaddr_in *, saddr)->sin_addr.s_addr==INADDR_ANY);
    }

    if (transport==T_SCTP && !isany) set_multihome_addr(socket,*port);
#endif

    return 0;
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
    struct timeval currentTime;
    GET_TIME (&currentTime);

    if (rc == len) {
        /* Everything is great. */
        if (useMessagef == 1) {
            TRACE_MSG("----------------------------------------------- %s\n"
                      "%s %smessage sent (%d bytes):\n\n%.*s\n",
                      CStat::formatTime(&currentTime, true),
                      TRANSPORT_TO_STRING(socket->ss_transport),
                      socket->ss_control ? "control " : "",
                      len, len, buffer);
        }

    } else if (rc <= 0) {
        if ((errno == EWOULDBLOCK) && (flags & WS_BUFFER)) {
            //buffer_write(socket, buffer, len, dest);
            //enter_congestion(socket, errno);
            return len;
        }
        if (useMessagef == 1) {
            TRACE_MSG("----------------------------------------------- %s\n"
                      "Error sending %s message:\n\n%.*s\n",
                      CStat::formatTime(&currentTime, true),
                      TRANSPORT_TO_STRING(socket->ss_transport),
                      len, buffer);
        }
        //return write_error(socket, errno);
    } else {
        /* We have a truncated message, which must be handled internally to the write function. */
        if (useMessagef == 1) {
            TRACE_MSG("----------------------------------------------- %s\n"
                      "Truncation sending %s message (%d of %d sent):\n\n%.*s\n",
                      CStat::formatTime(&currentTime, true),
                      TRANSPORT_TO_STRING(socket->ss_transport),
                      rc, len, len, buffer);
        }
        //buffer_write(socket, buffer + rc, len - rc, dest);
        //enter_congestion(socket, errno);
    }

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
    
    struct timeval currentTime;
    GET_TIME (&currentTime);

    printf("process_message\n");
    
    if (useMessagef == 1) {
        TRACE_MSG("----------------------------------------------- %s\n"
                  "%s %smessage received [%d] bytes :\n\n%s\n",
                  CStat::formatTime(&currentTime, true),
                  TRANSPORT_TO_STRING(socket->ss_transport),
                  socket->ss_control ? "control " : "",
                  msg_size, msg);
    }

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

/*************************** I/O functions ***************************/

/* Allocate a socket buffer. */
struct socketbuf *alloc_socketbuf(char *buffer, size_t size, int copy, struct sockaddr_storage *dest)
{
    struct socketbuf *socketbuf;

    socketbuf = (struct socketbuf *)malloc(sizeof(struct socketbuf));
    if (!socketbuf) {
        ERROR("Could not allocate socket buffer!\n");
    }
    memset(socketbuf, 0, sizeof(struct socketbuf));
    if (copy) {
        socketbuf->buf = (char *)malloc(size);
        if (!socketbuf->buf) {
            ERROR("Could not allocate socket buffer data!\n");
        }
        memcpy(socketbuf->buf, buffer, size);
    } else {
        socketbuf->buf = buffer;
    }
    socketbuf->len = size;
    socketbuf->offset = 0;
    if (dest) {
        memcpy(&socketbuf->addr, dest, SOCK_ADDR_SIZE(dest));
    }
    socketbuf->next = NULL;

    return socketbuf;
}

/* Free a poll buffer. */
void free_socketbuf(struct socketbuf *socketbuf)
{
    free(socketbuf->buf);
    free(socketbuf);
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
    socketbuf = alloc_socketbuf(buffer, readsize, NO_COPY, NULL);

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

    printf("recvfrom ret: %d\n", ret);
    printf("socket->ss_fd: %d\n", socket->ss_fd);
    
    buffer_read(socket, socketbuf);

    /* Do we have a complete SIP message? */
    if (!socket->ss_msglen) {
        //if (int msg_len = check_for_message(socket)) {
            socket->ss_msglen = ret;
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


