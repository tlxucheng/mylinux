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

    /* When should this call wake up? */
    virtual unsigned int wake();

public:
    static   int   maxDynamicId;    // max value for dynamicId; this value is reached !
    static   int   startDynamicId;  // offset for first dynamicId  FIXME:in CmdLine
    static   int   stepDynamicId;   // step of increment for dynamicId
    static   int   dynamicId;       // a counter for general use, incrementing  by  stepDynamicId starting at startDynamicId  wrapping at maxDynamicId  GLOBALY

private:
    /* This is the core constructor function. */
    void init(scenario * call_scenario, sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitCall);
    /* This this call for initialization? */
    bool initCall;

    scenario *call_scenario;

    unsigned int   number;

    int		msg_index;
    int		zombie;
    char *    realloc_ptr;

    /* Last message sent from scenario step (retransmitions do not
     * change this index. Only message sent from the scenario
     * are kept in this index.) */
    int		 last_send_index;
    char         * last_send_msg;
    int        last_send_len;

    /* How long until sending this message times out. */
    unsigned int   send_timeout;

    /* Last received message (expected,  not optional, and not
     * retransmitted) and the associated hash. Stills setted until a new
     * scenario steps sends a message */
    unsigned long    last_recv_hash;
    int		   last_recv_index;
    char           * last_recv_msg;

    /* Recv message characteristics when we sent a valid message
     *  (scneario, no retrans) just after a valid reception. This was
     * a cause relationship, so the next time this cookie will be recvd,
     * we will retransmit the same message we sent this time */
    unsigned long  recv_retrans_hash;
    int   recv_retrans_recv_index;
    int   recv_retrans_send_index;
    unsigned int   recv_timeout;

    /* holds the route set */
    char         * dialog_route_set;
    char         * next_req_url;

    /* cseq value for [cseq] keyword */
    unsigned int   cseq;
		
    struct sockaddr_storage call_peer;

    /* holds the auth header and if the challenge was 401 or 407 */
    char         * dialog_authentication;
    int            dialog_challenge_type;

    unsigned int   next_retrans;
    int   	 nb_retrans;
    unsigned int   nb_last_delay;

    unsigned int   paused_until;

    unsigned long  start_time;
    unsigned long long *start_time_rtd;
    bool           *rtd_done;

    char           *peer_tag;

    bool           call_established; // == true when the call is established
    // ie ACK received or sent
    // => init to false
    bool           ack_is_pending;   // == true if an ACK is pending

    struct sipp_socket *call_remote_socket;

    char * get_last_header(const char * name);
    char * get_last_request_uri();

	bool executeMessage(message *curmsg);
	
    char * send_scene(int index, int *send_status, int *msgLen);
    int send_raw(const char * msg, int index, int len);

    bool   use_ipv6;

    void queue_up(char *msg);
    char *queued_msg;

    // P_index use for message index in scenario and ctrl of CRLF
    // P_index = -2 No ctrl of CRLF
    // P_index = -1 Add crlf to end of message
    char* createSendingMessage(SendingMessage *src, int P_index, int *msgLen=NULL);
    char* createSendingMessage(char * src, int P_index, bool skip_sanity = false);
    char* createSendingMessage(SendingMessage *src, int P_index, char *msg_buffer, int buflen, int *msgLen=NULL);

    int    userId;

    /* rc == true means call not deleted by processing */
    bool next();

protected:
    int            call_port;
};

/* Default Message Functions. */
void init_default_messages();
void free_default_messages();
SendingMessage *get_default_message(const char *which);
void set_default_message(const char *which, char *message);

#endif

