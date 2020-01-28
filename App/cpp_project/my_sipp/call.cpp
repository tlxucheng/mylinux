#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "sipp.hpp"

/************** Call map and management routines **************/
static unsigned int next_number = 1;

/******************* Call class implementation ****************/
call::call(const char *p_id, bool use_ipv6, int userId, struct sockaddr_storage *dest) : listener(p_id, true)
{
}

call::call(const char *p_id, struct sipp_socket *socket, struct sockaddr_storage *dest) : listener(p_id, true)
{

}

call::call(scenario * call_scenario, struct sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitialization) : listener(p_id, true)
{
    init(call_scenario, socket, dest, p_id, userId, ipv6, isAutomatic, isInitialization);
}

call *call::add_call(int userId, bool ipv6, struct sockaddr_storage *dest)
{
    static char call_id[MAX_HEADER_LEN];

    const char * src = call_id_string;
    int count = 0;

    if(!next_number) {
        next_number ++;
    }

    while (*src && count < MAX_HEADER_LEN-1) {
        if (*src == '%') {
            ++src;
            switch(*src++) {
            case 'u':
                count += snprintf(&call_id[count], MAX_HEADER_LEN-count-1,"%u", next_number);
                break;
            case 'p':
                count += snprintf(&call_id[count], MAX_HEADER_LEN-count-1,"%u", pid);
                break;
            case 's':
                count += snprintf(&call_id[count], MAX_HEADER_LEN-count-1,"%s", local_ip);
                break;
            default:      // treat all unknown sequences as %%
                call_id[count++] = '%';
                break;
            }
        } else {
            call_id[count++] = *src++;
        }
    }
    call_id[count] = 0;

    return new call(main_scenario, NULL, dest, call_id, userId, ipv6, false /* Not Auto. */, false);
}

void call::init(scenario * call_scenario, struct sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitialization)
{
	this->call_scenario = call_scenario;
	
    call_port = 0;
    call_remote_socket = NULL;
    if (socket) {
        //associate_socket(socket);
        //socket->ss_count++;
    } else {
        call_socket = NULL;
    }
    if (dest) {
        memcpy(&call_peer, dest, sizeof(call_peer));
    } else {
        memset(&call_peer, 0, sizeof(call_peer));
    }

    setRunning();
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

const char *default_message_names[] = {
    "3pcc_abort",
    "ack",
    "ack2",
    "bye",
    "cancel",
    "200",
};
const char *default_message_strings[] = {
    /* 3pcc_abort */
    "call-id: [call_id]\ninternal-cmd: abort_call\n\n",
    /* ack */
    "ACK [last_Request_URI] SIP/2.0\n"
    "[last_Via]\n"
    "[last_From]\n"
    "[last_To]\n"
    "Call-ID: [call_id]\n"
    "CSeq: [last_cseq_number] ACK\n"
    "Contact: <sip:sipp@[local_ip]:[local_port];transport=[transport]>\n"
    "Max-Forwards: 70\n"
    "Subject: Performance Test\n"
    "Content-Length: 0\n\n",
    /* ack2, the only difference is Via, I don't quite know why. */
    "ACK [last_Request_URI] SIP/2.0\n"
    "Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "[last_From]\n"
    "[last_To]\n"
    "Call-ID: [call_id]\n"
    "CSeq: [last_cseq_number] ACK\n"
    "Contact: <sip:sipp@[local_ip]:[local_port];transport=[transport]>\n"
    "Max-Forwards: 70\n"
    "Subject: Performance Test\n"
    "Content-Length: 0\n\n",
    /* bye */
    "BYE [last_Request_URI] SIP/2.0\n"
    "Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "[last_From]\n"
    "[last_To]\n"
    "Call-ID: [call_id]\n"
    "CSeq: [last_cseq_number+1] BYE\n"
    "Max-Forwards: 70\n"
    "Contact: <sip:sipp@[local_ip]:[local_port];transport=[transport]>\n"
    "Content-Length: 0\n\n",
    /* cancel */
    "CANCEL [last_Request_URI] SIP/2.0\n"
    "[last_Via]\n"
    "[last_From]\n"
    "[last_To]\n"
    "Call-ID: [call_id]\n"
    "CSeq: [last_cseq_number] CANCEL\n"
    "Max-Forwards: 70\n"
    "Contact: <sip:sipp@[local_ip]:[local_port];transport=[transport]>\n"
    "Content-Length: 0\n\n",
    /* 200 */
    "SIP/2.0 200 OK\n"
    "[last_Via:]\n"
    "[last_From:]\n"
    "[last_To:]\n"
    "[last_Call-ID:]\n"
    "[last_CSeq:]\n"
    "Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "Content-Length: 0\n\n"
};

SendingMessage **default_messages;

void init_default_messages()
{
    int messages = sizeof(default_message_strings)/sizeof(default_message_strings[0]);
    default_messages = new SendingMessage* [messages];
    for (int i = 0; i < messages; i++) {
        default_messages[i] = new SendingMessage(main_scenario, const_cast<char*>(default_message_strings[i]));
    }
}

void free_default_messages()
{
    int messages = sizeof(default_message_strings)/sizeof(default_message_strings[0]);
    if (!default_messages) {
        return;
    }
    for (int i = 0; i < messages; i++) {
        delete default_messages[i];
    }
    delete [] default_messages;
}

SendingMessage *get_default_message(const char *which)
{
    int messages = sizeof(default_message_names)/sizeof(default_message_names[0]);
    for (int i = 0; i < messages; i++) {
        if (!strcmp(which, default_message_names[i])) {
            return default_messages[i];
        }
    }
    ERROR("Internal Error: Unknown default message: %s!", which);
}

void set_default_message(const char *which, char *msg)
{
    int messages = sizeof(default_message_names)/sizeof(default_message_names[0]);
    for (int i = 0; i < messages; i++) {
        if (!strcmp(which, default_message_names[i])) {
            default_message_strings[i] = msg;
            return;
        }
    }
    ERROR("Internal Error: Unknown default message: %s!", which);
}

