#include "server.h"

/* Global vars */
struct redisServer server;           /* Server global state */

void initServer(void)
{
    server.pid = getpid();
    server.current_client = NULL;
    server.clients_to_close = listCreate();
    server.unblocked_clients = listCreate();
    server.clients_waiting_acks = listCreate();
    server.system_memory_size = zmalloc_get_memory_size();

    return;
}

