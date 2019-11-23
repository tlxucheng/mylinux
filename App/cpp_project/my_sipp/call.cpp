#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "sipp.hpp"

/******************* Call class implementation ****************/
call::call(const char *p_id, bool use_ipv6, int userId, struct sockaddr_storage *dest) : listener(p_id, true)
{
}

call::call(const char *p_id, struct sipp_socket *socket, struct sockaddr_storage *dest) : listener(p_id, true)
{

}

call::call(scenario * call_scenario, struct sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitialization) : listener(p_id, true)
{

}

int call::send_raw(const char * msg, int index, int len)
{	
    struct sipp_socket  *sock;
    int                 rc;
	
    sock = call_socket;

    /* server */
    if ((use_remote_sending_addr) && (sendMode == MODE_SERVER)) 
	{
        sock=call_remote_socket ;
    }
	else
	{
	}

    rc = write_socket(sock, msg, len, WS_BUFFER, &call_peer);

	return rc;
}

char * call::send_scene(int index, int *send_status, int *len)
{

}

bool call::executeMessage(message *curmsg)
{

}

bool call::run()
{	
    message *curmsg;
    if(initCall)
	{
        curmsg = call_scenario->initmessages[msg_index];
	}
	else 
	{
        curmsg = call_scenario->messages[msg_index];
	}

    return executeMessage(curmsg);
}


bool call::process_incoming(char * msg, struct sockaddr_storage *src)
{
	return true;
}


