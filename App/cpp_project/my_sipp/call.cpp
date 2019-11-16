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

