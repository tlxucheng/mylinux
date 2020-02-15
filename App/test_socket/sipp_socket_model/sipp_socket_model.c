#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define T_UDP                      0
#define T_TCP                      1
#define T_TLS                      2
#define T_SCTP                     3

#define MSG_MAX_SIZE               4096

#define SERVER_TAG                 "-s"
#define CLIENT_TAG                 "-c"

typedef enum cmd_mode
{
    SERVER_MODE = 1,
    CLIENT_MODE,
}CMD_MODE;

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

    return 0;
}

int main(int argc, char *argv[])
{
    int                   fd;
    struct sockaddr_in    addr;
    int                   readsize = 0;
    char                  buf[MSG_MAX_SIZE] = {0};
    int                   mode = 0;

    mode = prase_cmd(argv[1]);

    fd = create_socket(T_UDP);
    memset((char *)&addr, 0x0, sizeof(addr));
    set_sockaddr_in(&addr, 5060,  "192.168.0.105");

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

    if(SERVER_MODE == mode)
    {
        while(1)
        {
            sleep(1000);
        }
    }

    return 0;
}


