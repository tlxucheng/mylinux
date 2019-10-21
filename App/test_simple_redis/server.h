#ifndef __REDIS_H
#define __REDIS_H

#include <unistd.h>

#include "adlist.h"  /* Linked lists */

#define LRU_BITS 24

typedef struct redisObject
{
    unsigned type:4;
    unsigned encoding:4;
    unsigned lru:LRU_BITS; /* LRU time (relative to global lru_clock) or
                            * LFU data (least significant 8 bits frequency
                            * and most significant 16 bits access time). */
    int refcount;
    void *ptr;
}robj;

typedef struct client
{
    int fd;                 /* Client socket. */    
    robj *name;             /* As set by CLIENT SETNAME. */
    list *reply;            /* List of reply objects to send to the client. */
}client;

struct redisServer
{
    pid_t pid;                  /* Main process pid. */
    client *current_client;     /* Current client, only used on crash report */
    list *clients;              /* List of active clients */
    list *clients_to_close;     /* Clients to close asynchronously */
    list *unblocked_clients;    /* list of clients to unblock before next loop */
    list *clients_waiting_acks; /* Clients waiting in WAIT command. */
    size_t system_memory_size;  /* Total memory in system as reported by OS */

};

#endif


