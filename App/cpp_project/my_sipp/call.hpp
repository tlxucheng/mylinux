#ifndef __CALL__
#define __CALL__

#include "sip_parser.hpp"

class call : virtual public task, virtual public listener, public virtual socketowner
{
public:
    call(const char *p_id, bool use_ipv6, int userId, struct sockaddr_storage *dest);
    call(const char *p_id, struct sipp_socket *socket, struct sockaddr_storage *dest);
    static call *add_call(int userId, bool ipv6, struct sockaddr_storage *dest);
    call(scenario * call_scenario, struct sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitCall);

    /* 先注释掉解决编译问题 */
    //virtual ~call();

    virtual bool process_incoming(char * msg, struct sockaddr_storage *src = NULL);

    virtual bool run();

private:
	bool initCall;
	
    scenario *call_scenario;
	
    struct sockaddr_storage call_peer;
	
    int		msg_index;

    struct sipp_socket *call_remote_socket;

	bool executeMessage(message *curmsg);
	
    char * send_scene(int index, int *send_status, int *msgLen);
    int send_raw(const char * msg, int index, int len);
};

/* Default Message Functions. */
void init_default_messages();
void free_default_messages();
SendingMessage *get_default_message(const char *which);
void set_default_message(const char *which, char *message);

#endif

