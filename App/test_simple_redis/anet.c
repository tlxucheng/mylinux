#include "anet.h"

static void anetSetError(char *err, const char *fmt, ...)
{
    va_list ap;

    if(!err)
    {
        return;
    }
    va_start(ap, fmt);
    vsnprintf(err, ANET_ERR_LEN, ap);
    va_end(ap);

    return;
}

static int _anetTcpServer(char *err, int port, char *bindaddr, int af, int backlog)
{
    int  s = -1;
    int  rv;
    char _port[6];    
    struct addrinfo hints;
    struct addrinfo servinfo;

    snprintf(_port, 6, "%d", port);
    memset(&hints, 0x0, sizeof(hints));

    hints.ai_family = af;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    /* No effect if bindaddr != NULL */

    if ((rv = getaddrinfo(bindaddr,_port,&hints,&servinfo)) != 0) {
        anetSetError(err, "%s", gai_strerror(rv));
    }

    return s;
}

