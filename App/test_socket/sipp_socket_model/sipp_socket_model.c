#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/epoll.h>

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

#define MSG_MAX_SIZE               4096

/* 问题 */
/* epoll模型，客户端连续快速发送，server第二个socket有时会收不到消息
 *
 /*

/* select和epoll client套用poll client， 暂未区分 */
#define SERVER_TAG                 "-s"
#define CLIENT_TAG                 "-c"
#define MUTIL_SERVER_TAG           "-ms"   /* poll server */
#define MUTIL_CLIENT_TAG           "-mc"
#define MUTIL_SERVER_SELECT_TAG    "-mss"  /* select server */
#define MUTIL_SERVER_EPOLL_TAG     "-mse"  /* epoll server */

/*********************poll**********************/
int g_pollnfds = 2;
int g_pollfd[2];
struct pollfd g_pollfiles[2];
/***********************************************/

/*********************epoll**********************/
int MAX_EVENT = 20;
int g_epollnfds = 2;
int g_epfd;
struct epoll_event g_epollfiles[20];
struct epoll_event g_epollevents[20];
int g_epollfd[2];
/***********************************************/

typedef enum cmd_mode
{
    SERVER_MODE = 1,
    CLIENT_MODE,
    MUTIL_SERVER_MODE,
    MUTIL_CLIENT_MODE,
    MUTIL_SERVER_SELECT_MODE,
    MUTIL_SERVER_EPOLL_MODE,
}CMD_MODE;

int max(int a, int b)
{
    return (a-b)>0? a:b;
}

int create_socket(int transport)
{
    int fd           = -1;
    int socket_type  = 0;
    int protocol     = 0;

    switch(transport)
    {
        case T_UDP:
            socket_type = SOCK_DGRAM;
            protocol = IPPROTO_UDP;
            break;
        case T_TCP:
            socket_type = SOCK_DGRAM;
            break;
        default:
            return -1;
    }

    fd = socket(AF_INET, socket_type, protocol);

    return fd;
}

void create_mutil_socket(int transport)
{
    int i = 0;

    for(i = 0; i < g_pollnfds; i++)
    {
        g_pollfd[i] = create_socket(transport);
    }

    return;
}

void create_mutil_epoll_socket(int transport)
{
    int i = 0;

    for(i = 0; i < g_epollnfds; i++)
    {
        g_epollfd[i] = create_socket(transport);
    }

    return;
}

void set_sockaddr_in(struct sockaddr_in *pAddr, int local_port, char *pLocal_ip)
{
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = htons(local_port);
    if(NULL == pLocal_ip)
    {
        pAddr->sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        pAddr->sin_addr.s_addr = inet_addr(pLocal_ip);
    }
    
    return;
}

/* sockaddr_in */
int bind_socket(int sock_fd, struct sockaddr_in *pAddr)
{
    struct sockaddr *addr = NULL; 

    addr = ((struct sockaddr *)pAddr);
    bind(sock_fd, addr, sizeof(struct sockaddr));

    return 0;
}

int recv_socket(int sock_fd, char *pBuf, int len, struct sockaddr *pSrc_addr, socklen_t addrlen)
{
    int ret = 0;
    
    ret = recvfrom(sock_fd, pBuf, len, 0, pSrc_addr, &addrlen);

    return ret;
}

int poll_socket(struct sockaddr_in *pMutil_addr)
{
    int i = 0;
    char buf[MSG_MAX_SIZE] = {0};
    int ret = 0;

    for(i == 0; i < g_pollnfds; i++)
    {
        g_pollfiles[i].fd = g_pollfd[i];
        g_pollfiles[i].events = POLLIN; /* POLLOUT 如何使用 */
    }


    /* 去掉while循环或者放到for循环处是否可以---可以，去掉只能接收一次消息 */
#if 0
    while(1)
    {
        if(poll(g_pollfiles, g_pollnfds, -1) < 0)
        {
            printf("poll error\n");
            return -1;
        }
         
        for(i = 0; i < g_pollnfds; i++)
        {
            if(g_pollfiles[i].revents & POLLIN)
            {
                ret = recv_socket(g_pollfiles[i].fd, buf, MSG_MAX_SIZE, (struct sockaddr *)pMutil_addr+i, sizeof(struct sockaddr_in));
                printf("index %d, fd: %d, recv: %s\n", i, g_pollfiles[i].fd, buf);
                memset(buf, 0x0, sizeof(buf));
            }
        }
    }
#endif

    if(poll(g_pollfiles, g_pollnfds, -1) < 0)
    {
        printf("poll error\n");
        return -1;
    }

    while(1)
    {
        for(i = 0; i < g_pollnfds; i++)
        {
            if(g_pollfiles[i].revents & POLLIN)
            {
                ret = recv_socket(g_pollfiles[i].fd, buf, MSG_MAX_SIZE, (struct sockaddr *)pMutil_addr+i, sizeof(struct sockaddr_in));
                printf("index %d, fd: %d, recv: %s\n", i, g_pollfiles[i].fd, buf);
                memset(buf, 0x0, sizeof(buf));
            }
        }
    }

    return 0;
}

int select_socket(struct sockaddr_in *pMutil_addr)
{
    int     maxfd;
    fd_set  rset;
    int     i = 0;
    char    buf[MSG_MAX_SIZE] = {0};
    int     ret = 0;

    FD_ZERO(&rset);
    while(1)
    {
        FD_SET(g_pollfd[0], &rset);
        FD_SET(g_pollfd[1], &rset);
        maxfd = max(g_pollfd[0], g_pollfd[1])+1;
        select(maxfd, &rset, NULL, NULL, NULL);

        for(i = 0; i < g_pollnfds; i++)
        {
            if(FD_ISSET(g_pollfd[i], &rset))
            {
                ret = recv_socket(g_pollfd[i], buf, MSG_MAX_SIZE, (struct sockaddr *)pMutil_addr+i, sizeof(struct sockaddr_in));
                printf("index %d, fd: %d, recv: %s\n", i, g_pollfiles[i].fd, buf);
                memset(buf, 0x0, sizeof(buf));
            }
        }
    }


    return 0;
}

int epoll_scoket(struct sockaddr_in *pMutil_addr)
{   
    int     i                 = 0;
    int     fds               = 0;
    char    buf[MSG_MAX_SIZE] = {0};
    int     ret               = 0;

    g_epfd = epoll_create(MAX_EVENT);
    for(i = 0; i < g_epollnfds; i++)
    {
        g_epollfiles[i].events = EPOLLIN;
        g_epollfiles[i].data.fd = g_epollfd[i];
        epoll_ctl(g_epfd, EPOLL_CTL_ADD, g_epollfd[i], &g_epollfiles[i]);
    }

    while(1)
    {
        fds = epoll_wait(g_epfd, g_epollevents, MAX_EVENT, -1);
        for(i = 0; i < fds; i++)
        {
            if(g_epollevents[i].events & EPOLLIN)
            {
                //ret = recv_socket(g_epollfd[i], buf, MSG_MAX_SIZE, (struct sockaddr *)pMutil_addr+i, sizeof(struct sockaddr_in));
                ret = recv_socket(g_epollevents[i].data.fd, buf, MSG_MAX_SIZE, (struct sockaddr *)pMutil_addr+i, sizeof(struct sockaddr_in));
                printf("index %d, fd: %d, epoll server recv: %s\n", i, g_epollfd[i], buf);
                memset(buf, 0x0, sizeof(buf));
                //close(g_epollevents[i].data.fd);
                g_epollevents[i].data.fd = -1;
            }
        }
    }
    
    return 0;
}

int send_socket(int sock_fd, char *pBuf, int len, struct sockaddr *pDest_addr, socklen_t addrlen)
{
    int ret = 0;

    ret = sendto(sock_fd, pBuf, len, 0, pDest_addr, addrlen);

    return 0;
}

int prase_cmd(char *pCmd)
{
    if(0 == strcmp(pCmd, SERVER_TAG))
    {
        return SERVER_MODE;
    }
    else if(0 == strcmp(pCmd, CLIENT_TAG))
    {
        return CLIENT_MODE;
    }
    else if(0 == strcmp(pCmd, MUTIL_SERVER_TAG))
    {
        return MUTIL_SERVER_MODE;
    }
    else if(0 == strcmp(pCmd, MUTIL_CLIENT_TAG))
    {
        return MUTIL_CLIENT_MODE;
    }
    else if(0 == strcmp(pCmd, MUTIL_SERVER_SELECT_TAG))
    {
        return MUTIL_SERVER_SELECT_MODE;
    }
    else if(0 == strcmp(pCmd, MUTIL_SERVER_EPOLL_TAG))
    {
        return MUTIL_SERVER_EPOLL_MODE;
    }    

    return 0;
}

int main(int argc, char *argv[])
{
    int                   fd;
    struct sockaddr_in    addr;
    int                   readsize = 0;
    char                  buf[MSG_MAX_SIZE]         = {0};
    int                   mode = 0;

    struct sockaddr_in    mutil_addr[g_pollnfds];
    int                   i                         = 0;

    mode = prase_cmd(argv[1]);

    if(CLIENT_MODE  == mode || SERVER_MODE == mode)
    {
        fd = create_socket(T_UDP);
        memset((char *)&addr, 0x0, sizeof(addr));
        set_sockaddr_in(&addr, 5060,  "192.168.0.105");
    }
    else if(MUTIL_CLIENT_MODE  == mode || MUTIL_SERVER_MODE == mode || MUTIL_SERVER_SELECT_MODE == mode)
    {
        create_mutil_socket(T_UDP);
        memset((char *)mutil_addr, 0x0, 2*sizeof(struct sockaddr_in));
        for(i = 0; i < g_pollnfds; i++)
        {     
            set_sockaddr_in(&mutil_addr[i], 5060+i,  "192.168.0.105");
        }
    }
    else if(MUTIL_SERVER_EPOLL_MODE == mode)
    {
        create_mutil_epoll_socket(T_UDP);
        memset((char *)mutil_addr, 0x0, 2*sizeof(struct sockaddr_in));
        for(i = 0; i < g_epollnfds; i++)
        {     
            set_sockaddr_in(&mutil_addr[i], 5060+i,  "192.168.0.105");
        }
    }

    if(SERVER_MODE == mode)
    {
        bind_socket(fd, &addr);
        recv_socket(fd, buf, sizeof(buf), (struct sockaddr *)&addr, sizeof(addr));
        printf("recv message from client: %s\n", buf);
    }
    else if(CLIENT_MODE == mode) 
    {
        strncpy(buf, "hello, I am is client!", sizeof(buf));
        send_socket(fd, buf, sizeof(buf), (struct sockaddr *)&addr, sizeof(addr));
    }
    else if(MUTIL_SERVER_MODE == mode)
    {
        for(i = 0; i < g_pollnfds; i++)
        {
            bind_socket(g_pollfd[i], &mutil_addr[i]);
        }

        poll_socket(mutil_addr);
    }
    else if(MUTIL_CLIENT_MODE == mode)
    {    
        for(i = 0; i < g_pollnfds; i++)
        {
            snprintf(buf, sizeof(buf), "hello, I am is client %d", i);            
            send_socket(g_pollfd[i], buf, sizeof(buf), (struct sockaddr *)&mutil_addr[i], sizeof(struct sockaddr_in));
            memset(buf, 0x0, sizeof(buf));
        }
    }
    else if(MUTIL_SERVER_SELECT_MODE == mode)
    {
        for(i = 0; i < g_pollnfds; i++)
        {
            bind_socket(g_pollfd[i], &mutil_addr[i]);
        }

        select_socket(mutil_addr);
    }
    else if(MUTIL_SERVER_EPOLL_MODE == mode)
    {
        for(i = 0; i < g_epollnfds; i++)
        {
            bind_socket(g_epollfd[i], &mutil_addr[i]);
        }
        
        epoll_scoket(mutil_addr);
    }

    if(SERVER_MODE == mode || MUTIL_SERVER_MODE == mode
       || MUTIL_SERVER_SELECT_MODE == mode || MUTIL_SERVER_EPOLL_MODE == mode)
    {
        while(1)
        {
            sleep(1000);
        }
    }

    return 0;
}


