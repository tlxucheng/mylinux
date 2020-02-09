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
int bind_socket(int sock_fd, struct sockaddr_in *pAddr, int local_port, char *pLocal_ip)
{
    struct sockaddr *addr = NULL; 

    set_sockaddr_in(pAddr, local_port,  pLocal_ip);
    addr = ((struct sockaddr *)pAddr);
    bind(sock_fd, addr, sizeof(struct sockaddr));

    return 0;
}

int main()
{
    int                   fd;
    struct sockaddr_in    addr;

    fd = create_socket(T_UDP);
    memset((char *)&addr, 0x0, sizeof(addr));
    bind_socket(fd, &addr, 5060, "192.168.0.105");

    while(1)
    {
        sleep(1000);
    }

    return 0;
}


