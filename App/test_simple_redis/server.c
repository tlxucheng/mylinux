#include "server.h"

/* Global vars */
struct redisServer server;           /* Server global state */

void initServer(void)
{
    server.pid = getpid();
    server.current_client = NULL;

    return;
}

