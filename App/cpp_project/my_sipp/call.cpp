#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "sipp.hpp"

int call::dynamicId       = 0;
int call::maxDynamicId    = 10000+2000*4;      // FIXME both param to be in command line !!!!
int call::startDynamicId  = 10000;             // FIXME both param to be in command line !!!!
int call::stepDynamicId   = 4;                // FIXME both param to be in command line !!!!

/************** Call map and management routines **************/
static unsigned int next_number = 1;

/* When should this call wake up? */
unsigned int call::wake()
{
    unsigned int wake = 0;

    if (zombie) {
        return wake;
    }

    if (paused_until) {
        wake = paused_until;
    }

    if (next_retrans && (!wake || (next_retrans < wake))) {
        wake = next_retrans;
    }

    if (recv_timeout && (!wake || (recv_timeout < wake))) {
        wake = recv_timeout;
    }

    return wake;
}

/******************* Call class implementation ****************/
call::call(const char *p_id, bool use_ipv6, int userId, struct sockaddr_storage *dest) : listener(p_id, true)
{
    init(main_scenario, NULL, dest, p_id, userId, use_ipv6, false, false);
}

call::call(const char *p_id, struct sipp_socket *socket, struct sockaddr_storage *dest) : listener(p_id, true)
{
    init(main_scenario, socket, dest, p_id, 0 /* No User. */, socket->ss_ipv6, false /* Not Auto. */, false);
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

void call::init(scenario * call_scenario, struct sipp_socket *socket, struct sockaddr_storage *dest, const char * p_id, int userId, bool ipv6, bool isAutomatic, bool isInitCall)
{
    this->call_scenario = call_scenario;
    zombie = false;

    msg_index = 0;
    last_send_index = 0;
    last_send_msg = NULL;
    last_send_len = 0;

    last_recv_hash = 0;
    last_recv_index = -1;
    last_recv_msg = NULL;

    recv_retrans_hash = 0;
    recv_retrans_recv_index = -1;
    recv_retrans_send_index = -1;

    dialog_route_set = NULL;
    next_req_url = NULL;

    cseq = 0;

    next_retrans = 0;
    nb_retrans = 0;
    nb_last_delay = 0;

    paused_until = 0;

    call_port = 0;

    start_time = clock_tick;
    call_established=false ;
    ack_is_pending=false ;
    last_recv_msg = NULL;
    cseq = base_cseq;
    nb_last_delay = 0;
    use_ipv6 = ipv6;
    queued_msg = NULL;

    dialog_authentication = NULL;
    dialog_challenge_type = 0;

    
    call_remote_socket = NULL;
    if (socket) {
        associate_socket(socket);
        //socket->ss_count++;
    } else {
        call_socket = NULL;
    }
    if (dest) {
        memcpy(&call_peer, dest, sizeof(call_peer));
    } else {
        memset(&call_peer, 0, sizeof(call_peer));
    }

    this->initCall = isInitCall;

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
#define MAX_MSG_NAME_SIZE 30
    static char msg_name[MAX_MSG_NAME_SIZE];
    char *L_ptr1 ;
    char *L_ptr2 ;
    int uselen = 0;
    int tmplen;
    char *hdrbdry;

    assert(send_status);

    /* Socket port must be known before string substitution */
    /*
    if (!connect_socket_if_needed()) {
        *send_status = -2;
        return NULL;
    }
    */

    assert(call_socket);

    assert(call_scenario->messages[index]->send_scheme);

    if (!len) {
        len = &uselen;
    }

    char * dest;
    dest = createSendingMessage(call_scenario->messages[index] -> send_scheme, index, len);

    if (dest) {
        L_ptr1=msg_name ;
        L_ptr2=dest ;
        while ((*L_ptr2 != ' ') && (*L_ptr2 != '\n') && (*L_ptr2 != '\t'))  {
            *L_ptr1 = *L_ptr2;
            L_ptr1 ++;
            L_ptr2 ++;
        }
        *L_ptr1 = '\0' ;
    }

    if (strcmp(msg_name,"ACK") == 0) {
        call_established = true ;
        ack_is_pending = false ;
    }

    /* Fix: Remove extra "\r\n" if message body ends with "\r\n\r\n" */
    tmplen = (*len) - 1;
    if ((dest[tmplen] == dest[tmplen-2] && dest[tmplen] == '\n')
            && (dest[tmplen-1] == dest[tmplen-3] && dest[tmplen-1] == '\r'))  {
        hdrbdry = strstr(dest, "\r\n\r\n");
        if (NULL != hdrbdry &&  hdrbdry != dest+(tmplen-3))  {
            *len = (*len) - 2;
        }
    }

    *send_status = send_raw(dest, index, *len);

    return dest;
}

char* call::createSendingMessage(SendingMessage *src, int P_index, int *msgLen)
{
    static char msg_buffer[SIPP_MAX_MSG_SIZE+2];
    return createSendingMessage(src, P_index, msg_buffer, sizeof(msg_buffer), msgLen);
}

char* call::createSendingMessage(SendingMessage *src, int P_index, char *msg_buffer, int buf_len, int *msgLen)
{
    char * length_marker = NULL;
    char * auth_marker = NULL;
    MessageComponent *auth_comp = NULL;
    bool auth_comp_allocated = false;
    int    len_offset = 0;
    char *dest = msg_buffer;
    bool supresscrlf = false;

    *dest = '\0';

    for (int i = 0; i < src->numComponents(); i++) {
        MessageComponent *comp = src->getComponent(i);
        int left = buf_len - (dest - msg_buffer);
        switch(comp->type) {
        case E_Message_Literal:
            if (supresscrlf) {
                char *ptr = comp->literal;
                while (isspace(*ptr)) ptr++;
                dest += snprintf(dest, left, "%s", ptr);
                supresscrlf = false;
            } else {
                memcpy(dest, comp->literal, comp->literalLen);
                dest += comp->literalLen;
                *dest = '\0';
            }
            break;
        case E_Message_Remote_IP:
            dest += snprintf(dest, left, "%s", remote_ip_escaped);
            break;
        case E_Message_Remote_Host:
            dest += snprintf(dest, left, "%s", remote_host);
            break;
        case E_Message_Remote_Port:
            dest += snprintf(dest, left, "%d", remote_port + comp->offset);
            break;
        case E_Message_Local_IP:
            dest += snprintf(dest, left, "%s", local_ip_escaped);
            break;
        case E_Message_Local_Port:
            int port;
            if((transport == T_UDP) && (multisocket) && (sendMode != MODE_SERVER)) {
                port = call_port;
            } else {
                port =  local_port;
            }
            dest += snprintf(dest, left, "%d", port + comp->offset);
            break;
        case E_Message_Transport:
            dest += snprintf(dest, left, "%s", TRANSPORT_TO_STRING(transport));
            break;
        case E_Message_Local_IP_Type:
            dest += snprintf(dest, left, "%s", (local_ip_is_ipv6 ? "6" : "4"));
            break;
        case E_Message_Server_IP: {
            /* We should do this conversion once per socket creation, rather than
             * repeating it every single time. */
            struct sockaddr_storage server_sockaddr;

            sipp_socklen_t len = SOCK_ADDR_SIZE(&server_sockaddr);
            getsockname(call_socket->ss_fd,
                        (sockaddr *)(void *)&server_sockaddr, &len);

            if (server_sockaddr.ss_family == AF_INET6) {
                char * temp_dest;
                temp_dest = (char *) malloc(INET6_ADDRSTRLEN);
                memset(temp_dest,0,INET6_ADDRSTRLEN);
                inet_ntop(AF_INET6,
                          &((_RCAST(struct sockaddr_in6 *,&server_sockaddr))->sin6_addr),
                          temp_dest,
                          INET6_ADDRSTRLEN);
                dest += snprintf(dest, left, "%s",temp_dest);
            } else {
                dest += snprintf(dest, left, "%s",
                                 inet_ntoa((_RCAST(struct sockaddr_in *,&server_sockaddr))->sin_addr));
            }
        }
        break;
        case E_Message_Media_IP:
            dest += snprintf(dest, left, "%s", media_ip_escaped);
            break;
        case E_Message_Media_Port:
        case E_Message_Auto_Media_Port: {
            int port = media_port + comp->offset;
            if (comp->type == E_Message_Auto_Media_Port) {
                port = media_port + (4 * (number - 1)) % 10000 + comp->offset;
            }

            dest += sprintf(dest, "%u", port);
            break;
        }
        case E_Message_Media_IP_Type:
            dest += snprintf(dest, left, "%s", (media_ip_is_ipv6 ? "6" : "4"));
            break;
        case E_Message_Call_Number:
            dest += snprintf(dest, left, "%u", number);
            break;
        case E_Message_DynamicId:
            dest += snprintf(dest, left, "%u", call::dynamicId);
            // increment at each request
            dynamicId += stepDynamicId;
            if ( this->dynamicId > maxDynamicId ) {
                call::dynamicId = call::startDynamicId;
            } ;
            break;
        case E_Message_Call_ID:
            dest += snprintf(dest, left, "%s", id);
            break;
        case E_Message_CSEQ:
            dest += snprintf(dest, left, "%u", cseq + comp->offset);
            break;
        case E_Message_PID:
            dest += snprintf(dest, left, "%d", pid);
            break;
        case E_Message_Service:
            dest += snprintf(dest, left, "%s", service);
            break;
        case E_Message_Branch:
            /* Branch is magic cookie + call number + message index in scenario */
            if(P_index == -2) {
                dest += snprintf(dest, left, "z9hG4bK-%u-%u-%d", pid, number, msg_index-1 + comp->offset);
            } else {
                dest += snprintf(dest, left, "z9hG4bK-%u-%u-%d", pid, number, P_index + comp->offset);
            }
            break;
        case E_Message_Index:
            dest += snprintf(dest, left, "%d", P_index);
            break;
        case E_Message_Next_Url:
            if (next_req_url) {
                dest += sprintf(dest, "%s", next_req_url);
            }
            break;
        case E_Message_Len:
            length_marker = dest;
            dest += snprintf(dest, left, "     ");
            len_offset = comp->offset;
            break;
        case E_Message_Authentication:
            if (auth_marker) {
                ERROR("Only one [authentication] keyword is currently supported!\n");
            }
            auth_marker = dest;
            dest += snprintf(dest, left, "[authentication place holder]");
            auth_comp = comp;
            break;
        case E_Message_Peer_Tag_Param:
            if(peer_tag) {
                dest += snprintf(dest, left, ";tag=%s", peer_tag);
            }
            break;
        case E_Message_Routes:
            if (dialog_route_set) {
                dest += sprintf(dest, "Route: %s", dialog_route_set);
            } else if (*(dest - 1) == '\n') {
                supresscrlf = true;
            }
            break;
        case E_Message_ClockTick:
            dest += snprintf(dest, left, "%lu", clock_tick);
            break;
        case E_Message_Timestamp:
            struct timeval currentTime;
            gettimeofday(&currentTime, NULL);
            dest += snprintf(dest, left, "%s", CStat::formatTime(&currentTime));
            break;
        case E_Message_Users:
            dest += snprintf(dest, left, "%d", users);
            break;
        case E_Message_UserID:
            dest += snprintf(dest, left, "%d", userId);
            break;
        case E_Message_SippVersion:
            dest += snprintf(dest, left, "%s", SIPP_VERSION);
            break;
        /*
        case E_Message_Variable: {
            int varId = comp->varId;
            CCallVariable *var = M_callVariableTable->getVar(varId);
            if(var->isSet()) {
                if (var->isRegExp()) {
                    dest += sprintf(dest, "%s", var->getMatchingValue());
                } else if (var->isDouble()) {
                    dest += sprintf(dest, "%lf", var->getDouble());
                } else if (var->isString()) {
                    dest += sprintf(dest, "%s", var->getString());
                } else if (var->isBool()) {
                    dest += sprintf(dest, "true");
                }
            } else if (var->isBool()) {
                dest += sprintf(dest, "false");
            }
            if (*(dest - 1) == '\n') {
                supresscrlf = true;
            }
            break;
        }
        */
        /*
        case E_Message_Fill: {
            int varId = comp->varId;
            int length = (int) M_callVariableTable->getVar(varId)->getDouble();
            if (length < 0) {
                length = 0;
            }
            char *filltext = comp->literal;
            int filllen = strlen(filltext);
            if (filllen == 0) {
                ERROR("Internal error: [fill] keyword has zero-length text.");
            }
            for (int i = 0, j = 0; i < length; i++, j++) {
                *dest++ = filltext[j % filllen];
            }
            *dest = '\0';
            break;
        }
        */
        case E_Message_File: {
            char buffer[MAX_HEADER_LEN];
            createSendingMessage(comp->comp_param.filename, -2, buffer, sizeof(buffer));
            FILE *f = fopen(buffer, "r");
            if (!f) {
                ERROR("Could not open '%s': %s\n", buffer, strerror(errno));
            }
            int ret;
            while ((ret = fread(dest, 1, left, f)) > 0) {
                left -= ret;
                dest += ret;
            }
            if (ret < 0) {
                ERROR("Error reading '%s': %s\n", buffer, strerror(errno));
            }
            fclose(f);
            break;
        }
        /*
        case E_Message_Injection: {
            char *orig_dest = dest;
            getFieldFromInputFile(comp->comp_param.field_param.filename, comp->comp_param.field_param.field, comp->comp_param.field_param.line, dest);
            if (char *tmp = strstr(orig_dest, "[authentication")) {
                if (auth_marker) {
                    ERROR("Only one [authentication] keyword is currently supported!\n");
                }
                auth_marker = tmp;
                auth_comp = (struct MessageComponent *)calloc(1, sizeof(struct MessageComponent));
                if (!auth_comp) {
                    ERROR("Out of memory!");
                }
                auth_comp_allocated = true;

                tmp = strchr(auth_marker, ']');
                char c = *tmp;
                *tmp = '\0';
                SendingMessage::parseAuthenticationKeyword(call_scenario, auth_comp, auth_marker);
                *tmp = c;
            }
            if (*(dest - 1) == '\n') {
                supresscrlf = true;
            }
            break;
        }
        */
        /*
        case E_Message_Last_Header: {
            char * last_header = get_last_header(comp->literal);
            if(last_header) {
                dest += sprintf(dest, "%s", last_header);
            }
            if (*(dest - 1) == '\n') {
                supresscrlf = true;
            }
            break;
        }
        */
        case E_Message_Custom: {
            dest += comp->comp_param.fxn(this, comp, dest, left);
            break;
        }
        case E_Message_Last_Message:
            if(last_recv_msg && strlen(last_recv_msg)) {
                dest += sprintf(dest, "%s", last_recv_msg);
            }
            break;
        /*
        case E_Message_Last_Request_URI: {
            char * last_request_uri = get_last_request_uri();
            dest += sprintf(dest, "%s", last_request_uri);
            free(last_request_uri);
            break;
        }
        */
        /*
        case E_Message_Last_CSeq_Number: {
            int last_cseq = 0;

            char *last_header = get_last_header("CSeq:");
            if(last_header) {
                last_header += 5;
                while(isspace(*last_header)) last_header++;
                sscanf(last_header,"%d", &last_cseq);
            }
            dest += sprintf(dest, "%d", last_cseq + comp->offset);
            break;
        }
        */
        /*
        case E_Message_TDM_Map:
            if (!use_tdmmap)
                ERROR("[tdmmap] keyword without -tdmmap parameter on command line");
            dest += snprintf(dest, left, "%d.%d.%d/%d",
                             tdm_map_x+(int((tdm_map_number)/((tdm_map_b+1)*(tdm_map_c+1))))%(tdm_map_a+1),
                             tdm_map_h,
                             tdm_map_y+(int((tdm_map_number)/(tdm_map_c+1)))%(tdm_map_b+1),
                             tdm_map_z+(tdm_map_number)%(tdm_map_c+1)
                            );
            break;
        */
        }
    }
    /* Need the body for length and auth-int calculation */
    char *body;
    const char *auth_body = NULL;
    if (length_marker || auth_marker) {
        body = strstr(msg_buffer, "\r\n\r\n");
        if (body) {
            auth_body = body;
            auth_body += strlen("\r\n\r\n");
        }
    }

    /* Fix up the length. */
    if (length_marker) {
        if (auth_marker > body) {
            ERROR("The authentication keyword should appear in the message header, not the body!");
        }

        if (body && dest - body > 4 && dest - body < 100004) {
            char tmp = length_marker[5];
            sprintf(length_marker, "%5u", (unsigned)(dest - body - 4 + len_offset));
            length_marker[5] = tmp;
        } else {
            // Other cases: Content-Length is 0
            sprintf(length_marker, "    0\r\n\r\n");
        }
    }

    if (msgLen) {
        *msgLen = dest - msg_buffer;
    }

    return msg_buffer;
}

int g_test_one_send = 0;

bool call::executeMessage(message *curmsg)
{
    //if (curmsg->pause_distribution || curmsg->pause_variable != -1)
    if(0)
    {
    }
    else if(curmsg -> M_type == MSG_TYPE_SENDCMD)
    {
    }
    else if(curmsg -> M_type == MSG_TYPE_NOP)
    {
    }
    /* client send invite */
    else if(curmsg -> send_scheme)
    {
        char * msg_snd;
        int msgLen;
        int send_status;

        //if(g_test_one_send)
        //{
        //    return false;
        //}
        //g_test_one_send = 1;

         /* Do not send a new message until the previous one which had
         * retransmission enabled is acknowledged */

        if(next_retrans) {
            setPaused();
            return true;
        }

        /* Handle counters and RTDs for this message. */
        //do_bookkeeping(curmsg);

        /* decide whether to increment cseq or not
         * basically increment for anything except response, ACK or CANCEL
         * Note that cseq is only used by the [cseq] keyword, and
         * not by default
         */

        int incr_cseq = 0;
        if (!curmsg->send_scheme->isAck() &&
                !curmsg->send_scheme->isCancel() &&
                !curmsg->send_scheme->isResponse()) {
            ++cseq;
            incr_cseq = 1;
        }

        msg_snd = send_scene(msg_index, &send_status, &msgLen);
        if(send_status < 0 && errno == EWOULDBLOCK) 
        {
        }

        /* We have sent the message, so the timeout is no longer needed. */
        send_timeout = 0;

        last_send_index = curmsg->index;
        last_send_len = msgLen;
        realloc_ptr = (char *) realloc(last_send_msg, msgLen+1);
        if (realloc_ptr) {
            last_send_msg = realloc_ptr;
        } else {
            free(last_send_msg);
            ERROR("Out of memory!");
            return false;
        }
        memcpy(last_send_msg, msg_snd, msgLen);
        last_send_msg[msgLen] = '\0';

        /* Update retransmission information */
        /*
        if(curmsg -> retrans_delay) {
            if((transport == T_UDP) && (retrans_enabled)) {
                next_retrans = clock_tick + curmsg -> retrans_delay;
                nb_retrans = 0;
                nb_last_delay = curmsg->retrans_delay;
            }
        } else {
            next_retrans = 0;
        }
        */
        
        // executeAction(msg_snd, curmsg);
        
        /* Update scenario statistics */
        //curmsg -> nb_sent++;
        
        return next();
    }
    else if(curmsg->M_type == MSG_TYPE_RECV
            || curmsg->M_type == MSG_TYPE_RECVCMD)
    {
        if (queued_msg) {
            char *msg = queued_msg;
            queued_msg = NULL;
            bool ret = process_incoming(msg);
            free(msg);
            return ret;
        }
        else
        {
            /* We are going to wait forever. */
            setPaused();
        }    
    }
 
    return true;
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
    int             reply_code;
    static char     request[65];
    char            responsecseqmethod[65];
    char            txn[MAX_HEADER_LEN];
    unsigned long   cookie = 0;
    char          * ptr;
    int             search_index;
    bool            found = false;
    //T_ActionResult  actionResult;

    //getmilliseconds();

    setRunning();

    /* Ignore the messages received during a pause if -pause_msg_ign is set */
    if(call_scenario->messages[msg_index] -> M_type == MSG_TYPE_PAUSE && pause_msg_ign) return(true);

    /* Get our destination if we have none. */
    if (call_peer.ss_family == AF_UNSPEC && src) {
        memcpy(&call_peer, src, SOCK_ADDR_SIZE(src));
    }

    /* Authorize nop as a first command, even in server mode */
    #if 0
    if((msg_index == 0) && (call_scenario->messages[msg_index] -> M_type == MSG_TYPE_NOP)) {
        queue_up (msg);
        paused_until = 0;
        return run();
    }
    #endif
    
    responsecseqmethod[0] = '\0';

    /* Is it a response ? */
    if((msg[0] == 'S') &&
            (msg[1] == 'I') &&
            (msg[2] == 'P') &&
            (msg[3] == '/') &&
            (msg[4] == '2') &&
            (msg[5] == '.') &&
            (msg[6] == '0')    )
    {
        reply_code = get_reply_code(msg);
        if(!reply_code) {
            //if (!process_unexpected(msg)) {
            //    return false; // Call aborted by unexpected message handling
            }
       /* It is a response: update peer_tag */
        ptr = get_peer_tag(msg);
        if (ptr) {
            if(strlen(ptr) > (MAX_HEADER_LEN - 1)) {
                ERROR("Peer tag too long. Change MAX_HEADER_LEN and recompile sipp");
            }
            if(peer_tag) {
                free(peer_tag);
            }
            peer_tag = strdup(ptr);
            if (!peer_tag) {
                ERROR("Out of memory allocating peer tag.");
            }
        }
        request[0]=0;
        // extract the cseq method from the response
        //extract_cseq_method (responsecseqmethod, msg);
        //extract_transaction (txn, msg);
    }
    else if((ptr = strchr(msg, ' ')))
    {
        if((ptr - msg) < 64) {
            memcpy(request, msg, ptr - msg);
            request[ptr - msg] = 0;
            // Check if we received an ACK => call established
            if (strcmp(request,"ACK")==0) {
                call_established=true;
            }
            reply_code = 0;
        } else {
            ERROR("SIP method too long in received message '%s'",
                  msg);
        }
    }

    /* Try to find it in the expected non mandatory responses
     * until the first mandatory response  in the scenario */
    for(search_index = msg_index;
            search_index < (int)call_scenario->messages.size();
            search_index++) {
        //if(!matches_scenario(search_index, reply_code, request, responsecseqmethod, txn)) {
        //    if(call_scenario->messages[search_index] -> optional) {
        //        continue;
        //    }
            /* The received message is different for the expected one */
        //    break;
        //}

        found = true;
        /* TODO : this is a little buggy: If a 100 trying from an INVITE
         * is delayed by the network until the BYE is sent, it may
         * stop BYE transmission erroneously, if the BYE also expects
         * a 100 trying. */
        break;
    }

    int test = (!found) ? -1 : call_scenario->messages[search_index]->test;
    /* test==0: No branching"
     * test==-1 branching without testing"
     * test>0   branching with testing
     */

    // Action treatment
    if (found) 
    {
    }

    if (*request) { // update [cseq] with received CSeq
        unsigned long int rcseq = get_cseq_value(msg);
        if (rcseq > cseq) cseq = rcseq;
    }

    /* This is an ACK/PRACK or a response, and its index is greater than the
     * current active retransmission message, so we stop the retrans timer.
     * True also for CANCEL and BYE that we also want to answer to */
    if(((reply_code) ||
            ((!strcmp(request, "ACK")) ||
             (!strcmp(request, "CANCEL")) || (!strcmp(request, "BYE")) ||
             (!strcmp(request, "PRACK"))))  &&
            (search_index > last_send_index)) {
        /*
         * We should stop any retransmission timers on receipt of a provisional response only for INVITE
         * transactions. Non INVITE transactions continue to retransmit at T2 until a final response is
         * received
         */
        if ( (0 == reply_code) || // means this is a request.
                (200 <= reply_code) ||  // final response
                ((0 != reply_code) && (0 == strncmp (responsecseqmethod, "INVITE", strlen(responsecseqmethod)))) ) { // prov for INVITE
            next_retrans = 0;
        } else {
            /*
             * We are here due to a provisional response for non INVITE. Update our next retransmit.
             */
            //next_retrans = clock_tick + global_t2;
            //nb_last_delay = global_t2;

        }
    }

    /* This is a response with 200 so set the flag indicating that an
     * ACK is pending (used to prevent from release a call with CANCEL
     * when an ACK+BYE should be sent instead)                         */
    if (reply_code == 200) {
        ack_is_pending = true;
    }

    /* Store last received message information for all messages so that we can
     * correctly identify retransmissions, and use its body for inclusion
     * in our messages. */
    last_recv_index = search_index;
    last_recv_hash = cookie;
    realloc_ptr = (char *) realloc(last_recv_msg, strlen(msg) + 1);
    if (realloc_ptr) {
        last_recv_msg = realloc_ptr;
    } else {
        free(last_recv_msg);
        ERROR("Out of memory!");
        return false;
    }

    strcpy(last_recv_msg, msg);

    /* If this was a mandatory message, or if there is an explicit next label set
    * we must update our state machine.  */
    if(-1 == test)
    {
        /* If we are paused, then we need to wake up so that we properly go through the state machine. */
        paused_until = 0;
        msg_index = search_index;
        return next();
    }
    else
    {
        setPaused();
    }

	return true;
}

bool call::next()
{
    msgvec * msgs = &call_scenario->messages;
    if (initCall) {
        msgs = &call_scenario->initmessages;
    }

    int test = (*msgs)[msg_index]->test;
    /* What is the next message index? */
    /* Default without branching: use the next message */
    int new_msg_index = msg_index+1;
    /* If branch needed, overwrite this default */
    #if 0
    if ( ((*msgs)[msg_index]->next >= 0) &&
            ((test == -1) || M_callVariableTable->getVar(test)->isSet())
       ) {
        int chance = (*msgs)[msg_index]->chance;
        if ((chance <= 0) || (rand() > chance )) {
            new_msg_index = (*msgs)[msg_index]->next;
        }
    }
    #endif
    msg_index=new_msg_index;
    recv_timeout = 0;
    //if(msg_index >= (int)((*msgs).size())) {
    //    terminate(CStat::E_CALL_SUCCESSFULLY_ENDED);
    //    return false;
    //}

    return run();
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

