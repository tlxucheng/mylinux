#include "sipp.hpp"

/* This mode setting refers to whether we open calls autonomously (MODE_CLIENT)
 * or in response to requests (MODE_SERVER). */
int           creationMode  = MODE_CLIENT;
/* Send mode. Do we send to a fixed address or to the last one we got. */
int           sendMode  = MODE_CLIENT;
/* This describes what our 3PCC behavior is. */
int	      thirdPartyMode = MODE_3PCC_NONE;

/************************ Class Constructor *************************/

message::message(int index, const char *desc)
{
    this->index = index;
    this->desc = desc;
    pause_variable = -1;
	
    M_type = 0;

    send_scheme = NULL; // delete on exit
}


/******** Global variables which compose the scenario file **********/

scenario      *main_scenario;
scenario      *ooc_scenario;
scenario      *aa_scenario;
scenario      *display_scenario;

/*************** Helper functions for various types *****************/
long get_long(const char *ptr, const char *what)
{
    char *endptr;
    long ret;

    ret = strtol(ptr, &endptr, 0);
    if (*endptr) {
        ERROR("%s, \"%s\" is not a valid integer!\n", what, ptr);
    }
    return ret;
}

unsigned long long get_long_long(const char *ptr, const char *what)
{
    char *endptr;
    unsigned long long ret;

    ret = strtoull(ptr, &endptr, 0);
    if (*endptr) {
        ERROR("%s, \"%s\" is not a valid integer!\n", what, ptr);
    }
    return ret;
}

const char *scenario_table[] = {
    "uac",
    "uas",
    "regexp",
    "3pcc-C-A",
    "3pcc-C-B",
    "3pcc-A",
    "3pcc-B",
    "branchc",
    "branchs",
    "uac_pcap",
    "ooc_default",
    "ooc_dummy",
};

int find_scenario(const char *scenario)
{
    int i, max;
    max = sizeof(scenario_table)/sizeof(scenario_table[0]);

    for (i = 0; i < max; i++) {
        if (!strcmp(scenario_table[i], scenario)) {
            return i;
        }
    }

    ERROR("Invalid default scenario name '%s'.\n", scenario);

    return -1;
}

int get_cr_number(const char *src)
{
    int res=0;
    while(*src) {
        if(*src == '\n') res++;
        src++;
    }
    return res;
}

char *clean_cdata(char *ptr, int *removed_crlf = NULL)
{
    char * msg;

    while((*ptr == ' ') || (*ptr == '\t') || (*ptr == '\n')) ptr++;

    msg = (char *) malloc(strlen(ptr) + 3);
    if(!msg) {
        ERROR("Memory Overflow");
    }
    strcpy(msg, ptr);

    ptr = msg + strlen(msg);
    ptr --;

    while((ptr >= msg) &&
            ((*ptr == ' ')  ||
             (*ptr == '\t') ||
             (*ptr == '\n'))) {
        if(*ptr == '\n' && removed_crlf) {
            (*removed_crlf)++;
        }
        *ptr-- = 0;
    }

    if(!strstr(msg, "\n\n")) {
        strcat(msg, "\n\n");
    }

    if(ptr == msg) {
        ERROR("Empty cdata in xml scenario file");
    }
    while ((ptr = strstr(msg, "\n "))) {
        memmove(ptr + 1, ptr + 2, strlen(ptr) - 1);
    }
    while ((ptr = strstr(msg, " \n"))) {
        memmove(ptr, ptr + 1, strlen(ptr));
    }
    while ((ptr = strstr(msg, "\n\t"))) {
        memmove(ptr + 1, ptr + 2, strlen(ptr) - 1);
    }
    while ((ptr = strstr(msg, "\t\n"))) {
        memmove(ptr, ptr + 1, strlen(ptr));
    }

    return msg;
}

/********************** Scenario File analyser **********************/
void scenario::checkOptionalRecv(char *elem, unsigned int scenario_file_cursor)
{
    if (last_recv_optional) {
        ERROR("<recv> before <%s> sequence without a mandatory message. Please remove one 'optional=true' (element %d).", elem, scenario_file_cursor);
    }
    last_recv_optional = false;
}

scenario::scenario(char * filename, int deflt)
{
    char *              elem = NULL;
    const char*         cptr;
    unsigned int        scenario_file_cursor = 0;
    int                 L_content_length = 0 ;

	if(filename)
	{
	    if(!xp_set_xml_buffer_from_file(filename)) 
	    {
            ERROR("Unable to load or parse '%s' xml scenario file", filename);
        }
	}
	else
	{
        if(!xp_set_xml_buffer_from_string(default_scenario[deflt]))
		{
            ERROR("Unable to load default xml scenario file");
        }
	}

	elem = xp_open_element(0);
    if (!elem) {
        ERROR("No element in xml scenario file");
    }

	if(strcmp("scenario", elem)) {
        ERROR("No 'scenario' section in xml scenario file");
    }

	if ((cptr = xp_get_value("name"))) {
        name = strdup(cptr);
    } else {
        name = strdup("");
    }

	while ((elem = xp_open_element(scenario_file_cursor))) 
    {    
        char * ptr;
        scenario_file_cursor ++;

		if(!strcmp(elem, "CallLengthRepartition")) {

		}
		else /* Message Case */
		{
			message *curmsg = new message(messages.size(), name ? name : "unknown scenario");
			messages.push_back(curmsg);

			if(!strcmp(elem, "send"))
			{
			    checkOptionalRecv(elem, scenario_file_cursor);
				curmsg->M_type = MSG_TYPE_SEND;           
                /* Sent messages descriptions */
                if(!(ptr = xp_get_cdata())) {
                    ERROR("No CDATA in 'send' section of xml scenario file");
                }

                int removed_clrf = 0;
                char * msg = clean_cdata(ptr, &removed_clrf);

                L_content_length = xp_get_content_length(msg);
                switch (L_content_length) {
                case  -1 :
                    // the msg does not contain content-length field
                    break ;
                case  0 :
                    curmsg -> content_length_flag =
                        message::ContentLengthValueZero;   // Initialize to No present
                    break ;
                default :
                    curmsg -> content_length_flag =
                        message::ContentLengthValueNoZero;   // Initialize to No present
                    break ;
                }

                if((msg[strlen(msg) - 1] != '\n') && (removed_clrf)) {
                    strcat(msg, "\n");
                }
                char *tsrc = msg;
                while(*tsrc++);
                curmsg -> send_scheme = new SendingMessage(this, msg);
                free(msg);
			}
			else if(!strcmp(elem, "recv"))
			{
				curmsg->M_type = MSG_TYPE_RECV;
			}
		}

		xp_close_element();
    }
}

void scenario::runInit()
{
    call *initcall;
    if (initmessages.size() > 0) {
        initcall = new call(main_scenario, NULL, NULL, "///main-init", 0, false, false, true);
        initcall->run();
    }
}

// Determine in which mode the sipp tool has been
// launched (client, server, 3pcc client, 3pcc server, 3pcc extended master or slave)
void scenario::computeSippMode()
{
    unsigned int i = 0;

    creationMode = -1;
	sendMode = -1;	

	TRACE_MSG("computeSippMode messages.size: %d\n", messages.size());

	//assert(messages.size() > 0);

	for(i = 0; i < messages.size(); i++)
	{
		switch(messages[i]->M_type)
		{
			case MSG_TYPE_SEND:
				if(-1 == sendMode)
				{
					sendMode = MODE_CLIENT;
				}
				if(-1 == creationMode)
				{
					creationMode = MODE_CLIENT;
				}
				break;
			case MSG_TYPE_RECV:
				if(-1 == sendMode)
				{
					sendMode = MODE_SERVER;
				}
				if(-1 == creationMode)
				{
					creationMode = MODE_SERVER;
				}
				break;
		    default:
				break;
		}
	}
	
	TRACE_MSG("computeSippMode sendMode, creationMode: %d %d\n", sendMode, creationMode);
}

const char * default_scenario [] = {
    /************* Default_scenario[0] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'uac' scenario.                       -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"Basic Sipstone UAC\">\n"
    "  <!-- In client mode (sipp placing calls), the Call-ID MUST be         -->\n"
    "  <!-- generated by sipp. To do so, use [call_id] keyword.                -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag00[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\"\n"
    "        optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"180\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"183\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- By adding rrs=\"true\" (Record Route Sets), the route sets         -->\n"
    "  <!-- are saved and used for following messages sent. Useful to test   -->\n"
    "  <!-- against stateful SIP proxies/B2BUAs.                             -->\n"
    "  <recv response=\"200\" rtd=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- Packet lost can be simulated in any send/recv message by         -->\n"
    "  <!-- by adding the 'lost = \"10\"'. Value can be [1-100] percent.       -->\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      ACK sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag00[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- This delay can be customized by the -d command-line option       -->\n"
    "  <!-- or by adding a 'milliseconds = \"value\"' option here.             -->\n"
    "  <pause/>\n"
    "\n"
    "  <!-- The 'crlf' option inserts a blank line in the statistics report. -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag00[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n"
    ,

    /************* Default_scenario[1] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'uas' scenario.                       -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"Basic UAS responder\">\n"
    "  <!-- By adding rrs=\"true\" (Record Route Sets), the route sets         -->\n"
    "  <!-- are saved and used for following messages sent. Useful to test   -->\n"
    "  <!-- against stateful SIP proxies/B2BUAs.                             -->\n"
    "  <recv request=\"INVITE\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- The '[last_*]' keyword is replaced automatically by the          -->\n"
    "  <!-- specified header if it was present in the last message received  -->\n"
    "  <!-- (except if it was a retransmission). If the header was not       -->\n"
    "  <!-- present or if no message has been received, the '[last_*]'       -->\n"
    "  <!-- keyword is discarded, and all bytes until the end of the line    -->\n"
    "  <!-- are also discarded.                                              -->\n"
    "  <!--                                                                  -->\n"
    "  <!-- If the specified header was present several times in the         -->\n"
    "  <!-- message, all occurences are concatenated (CRLF separated)        -->\n"
    "  <!-- to be used in place of the '[last_*]' keyword.                   -->\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 180 Ringing\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag01[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag01[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv request=\"ACK\"\n"
    "        optional=\"true\"\n"
    "        rtd=\"true\"\n"
    "        crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv request=\"BYE\">\n"
    "  </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Keep the call open for a while in case the 200 is lost to be     -->\n"
    "  <!-- able to retransmit it if we receive the BYE again.               -->\n"
    "  <timewait milliseconds=\"4000\"/>\n"
    "\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[2] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'regexp client' scenario.             -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"Client with regexp scenario\">\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag02[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\"\n"
    "        optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"180\" optional=\"true\">\n"
    "  </recv>\n"
    "  <recv response=\"183\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"200\" start_rtd=\"true\">\n"
    "    <!-- Definition of regexp in the action tag. The regexp must follow -->\n"
    "    <!-- the Posix Extended standard (POSIX 1003.2), see:               -->\n"
    "    <!--                                                                -->\n"
    "    <!--   http://www.opengroup.org/onlinepubs/007908799/xbd/re.html    -->\n"
    "    <!--                                                                -->\n"
    "    <!-- regexp    : Contain the regexp to use for matching the         -->\n"
    "    <!--             received message                                   -->\n"
    "    <!--             MANDATORY                                          -->\n"
    "    <!-- search_in : msg (try to match against the entire message)      -->\n"
    "    <!--           : hdr (try to match against a specific SIP header    -->\n"
    "    <!--             (passed in the header tag)                         -->\n"
    "    <!--             OPTIONAL - default value : msg                     -->\n"
    "    <!-- header    : Header to try to match against.                    -->\n"
    "    <!--             Only used when the search_in tag is set to hdr     -->\n"
    "    <!--             MANDATORY IF search_in is equal to hdr             -->\n"
    "    <!-- check_it  : if set to true, the call is marked as failed if    -->\n"
    "    <!--             the regexp doesn't match.                          -->\n"
    "    <!--             OPTIONAL - default value : false                   -->\n"
    "    <!-- assign_to : contain the variable id (integer) or a list of     -->\n"
    "    <!--             variable id which will be used to store the        -->\n"
    "    <!--             result of the matching process between the regexp  -->\n"
    "    <!--             and the message. This variable can be re-used at   -->\n"
    "    <!--             a later time in the scenario using '[$n]' syntax   -->\n"
    "    <!--             where n is the variable id.                        -->\n"
    "    <!--             MANDATORY                                          -->\n"
    "    <action>\n"
    "      <ereg regexp=\"[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[:][0-9]{1,5}\" \n"
    "            search_in=\"msg\" \n"
    "            check_it=\"true\" \n"
    "            assign_to=\"1\"/>\n"
    "      <ereg regexp=\".*\" \n"
    "            search_in=\"hdr\" \n"
    "            header=\"Contact:\" \n"
    "            check_it=\"true\" \n"
    "            assign_to=\"6\"/>\n"
    "      <ereg regexp=\"o=([[:alnum:]]*) ([[:alnum:]]*) ([[:alnum:]]*)\"\n"
    "            search_in=\"msg\" \n"
    "            check_it=\"true\" \n"
    "            assign_to=\"3,4,5,8\"/>\n"
    "    </action>\n"
    "  </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "      ACK sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag02[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      retrievedIp: [$1]\n"
    "      retrievedContact:[$6]\n"
    "      retrievedSdpOrigin:[$3]\n"
    "      retrievedSdpOrigin-username:[$4]\n"
    "      retrievedSdpOrigin-session-id:[$5]\n"
    "      retrievedSdpOrigin-version:[$8]\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- This delay can be customized by the -d command-line option       -->\n"
    "  <!-- or by adding a 'milliseconds = \"value\"' option here.           -->\n"
    "  <pause milliseconds = \"1000\"/>\n"
    "\n"
    "  <!-- The 'crlf' option inserts a blank line in the statistics report. -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag02[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\" rtd=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"1000, 1040, 1080, 1120, 1160, 1200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"1000, 1100, 1200, 1300, 1400\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[3] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 3PCC - Controller - A side                         -->\n"
    "<!--                                                                    -->\n"
    "<!--             A              Controller               B              -->\n"
    "<!--             |(1) INVITE no SDP  |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(2) 200 offer1     |                   |              -->\n"
    "<!--             |==================>|                   |              -->\n"
    "<!--             |                   |(3) INVITE offer1  |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |                   |(4) 200 OK answer1 |              -->\n"
    "<!--             |                   |<==================|              -->\n"
    "<!--             |                   |(5) ACK            |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |(6) ACK answer1    |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(7) RTP            |                   |              -->\n"
    "<!--             |.......................................|              -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"3PCC Controller - A side\">\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag03[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\" optional=\"true\"> </recv>\n"
    "  <recv response=\"180\" optional=\"true\"> </recv>\n"
    "  <recv response=\"183\" optional=\"true\"> </recv>\n"
    "  <recv response=\"200\" crlf=\"true\" start_rtd=\"true\">\n"
    "    <action>\n"
    "       <ereg regexp=\"Content-Type:.*\" \n"
    "             search_in=\"msg\"  \n"
    "             assign_to=\"1\" /> \n"
    "    </action>\n"
    "  </recv>\n"
    "\n"
    "  <sendCmd>\n"
    "    <![CDATA[\n"
    "      Call-ID: [call_id]\n"
    "      [$1]\n"
    "\n"
    "     ]]>\n"
    "  </sendCmd>\n"
    "  \n"
    "  <recvCmd>\n"
    "    <action>\n"
    "       <ereg regexp=\"Content-Type:.*\"  \n"
    "             search_in=\"msg\"  \n"
    "             assign_to=\"2\" /> \n"
    "    </action>\n"
    "  \n"
    "  </recvCmd>\n"
    "  \n"
    "  <send rtd=\"true\">\n"
    "    <![CDATA[\n"
    "\n"
    "      ACK sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag03[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      [$2]\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <pause milliseconds=\"1000\"/>\n"
    "\n"
    "  <!-- The 'crlf' option inserts a blank line in the statistics report. -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag03[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\"> </recv>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[4] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 3PCC - Controller - B side                         -->\n"
    "<!--                                                                    -->\n"
    "<!--             A              Controller               B              -->\n"
    "<!--             |(1) INVITE no SDP  |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(2) 200 offer1     |                   |              -->\n"
    "<!--             |==================>|                   |              -->\n"
    "<!--             |                   |(3) INVITE offer1  |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |                   |(4) 200 OK answer1 |              -->\n"
    "<!--             |                   |<==================|              -->\n"
    "<!--             |                   |(5) ACK            |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |(6) ACK answer1    |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(7) RTP            |                   |              -->\n"
    "<!--             |.......................................|              -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "\n"
    "<scenario name=\"3PCC Controller - B side\">\n"
    "\n"
    "<recvCmd>\n"
    "  <action>\n"
    "       <ereg regexp=\"Content-Type:.*\"  \n"
    "             search_in=\"msg\"  \n"
    "             assign_to=\"1\" /> \n"
    "  </action>\n"
    "</recvCmd>\n"
    "\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag04[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      [$1]\n"
    "\n"
    "     ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\" optional=\"true\"> </recv>\n"
    "  <recv response=\"180\" optional=\"true\"> </recv>\n"
    "  <recv response=\"183\" optional=\"true\"> </recv>\n"
    "  <recv response=\"200\" crlf=\"true\">\n"
    "    <action>\n"
    "       <ereg regexp=\"Content-Type:.*\"  \n"
    "             search_in=\"msg\"  \n"
    "             assign_to=\"2\" /> \n"
    "    </action>\n"
    "  </recv>\n"
    "  \n"
    "    \n"
    "  <send start_rtd=\"true\">\n"
    "    <![CDATA[\n"
    "\n"
    "      ACK sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag04[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <sendCmd>\n"
    "    <![CDATA[\n"
    "      Call-ID: [call_id]\n"
    "      [$2]\n"
    "\n"
    "    ]]>\n"
    "  </sendCmd>\n"
    " \n"
    "  <pause milliseconds=\"1000\"/>\n"
    "\n"
    "\n"
    "  <!-- The 'crlf' option inserts a blank line in the statistics report. -->\n"
    "  <send retrans=\"500\" rtd=\"true\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag04[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[5] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 3PCC - A side emulator                             -->\n"
    "<!--                                                                    -->\n"
    "<!--             A              Controller               B              -->\n"
    "<!--             |(1) INVITE no SDP  |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(2) 200 offer1     |                   |              -->\n"
    "<!--             |==================>|                   |              -->\n"
    "<!--             |                   |(3) INVITE offer1  |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |                   |(4) 200 OK answer1 |              -->\n"
    "<!--             |                   |<==================|              -->\n"
    "<!--             |                   |(5) ACK            |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |(6) ACK answer1    |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(7) RTP            |                   |              -->\n"
    "<!--             |.......................................|              -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "\n"
    "<scenario name=\"3PCC A side\">\n"
    "  <recv request=\"INVITE\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag05[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv request=\"ACK\" rtd=\"true\" crlf=\"true\"> </recv>\n"
    "\n"
    "  <!-- RTP flow starts from here! -->\n"
    "\n"
    "  <recv request=\"BYE\" crlf=\"true\"> </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Keep the call open for a while in case the 200 is lost to be     -->\n"
    "  <!-- able to retransmit it if we receive the BYE again.               -->\n"
    "  <timewait milliseconds=\"2000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[6] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 3PCC - B side emulator                             -->\n"
    "<!--                                                                    -->\n"
    "<!--             A              Controller               B              -->\n"
    "<!--             |(1) INVITE no SDP  |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(2) 200 offer1     |                   |              -->\n"
    "<!--             |==================>|                   |              -->\n"
    "<!--             |                   |(3) INVITE offer1  |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |                   |(4) 200 OK answer1 |              -->\n"
    "<!--             |                   |<==================|              -->\n"
    "<!--             |                   |(5) ACK            |              -->\n"
    "<!--             |                   |==================>|              -->\n"
    "<!--             |(6) ACK answer1    |                   |              -->\n"
    "<!--             |<==================|                   |              -->\n"
    "<!--             |(7) RTP            |                   |              -->\n"
    "<!--             |.......................................|              -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "\n"
    "\n"
    "<scenario name=\"3PCC B side\">\n"
    "  <recv request=\"INVITE\" crlf=\"true\"> </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag06[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv request=\"ACK\" rtd=\"true\" crlf=\"true\"> </recv>\n"
    "\n"
    "  <!-- RTP flow starts from here! -->\n"
    "\n"
    "  <recv request=\"BYE\"> </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Keep the call open for a while in case the 200 is lost to be     -->\n"
    "  <!-- able to retransmit it if we receive the BYE again.               -->\n"
    "  <timewait milliseconds=\"2000\"/>\n"
    "\n"
    "</scenario>\n",

    /************* Default_scenario[7] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'branchc' scenario.                   -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"branch_client\">\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      REGISTER sip:CA.cym.com SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: ua1 <sip:ua1@nnl.cym:[local_port]>;tag=[pid]SIPpTag07[call_number]\n"
    "      To: ua1 <sip:ua1@nnl.cym:[local_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 REGISTER\n"
    "      Contact: sip:ua1@[local_ip]:[local_port]\n"
    "      Content-Length: 0\n"
    "      Expires: 300\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- simple case - just jump over a line   -->\n"
    "  <recv response=\"200\" rtd=\"true\" next=\"5\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"200\">\n"
    "  </recv>\n"
    "\n"
    "  <label id=\"5\"/>\n"
    "\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:ua2@CA.cym.com SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: ua[call_number] <sip:ua1@nnl.cym:[local_port]>;tag=[pid]SIPpTag07b[call_number]\n"
    "      To: ua2 <sip:ua2@nnl.cym:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:ua1@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"180\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"183\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- Do something different on an optional receive   -->\n"
    "  <recv response=\"403\" optional=\"true\" next=\"1\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"200\">\n"
    "    <action>\n"
    "      <ereg regexp=\"ua25\"\n"
    "            search_in=\"hdr\"\n"
    "            header=\"From: \"\n"
    "            assign_to=\"8\"/>\n"
    "    </action>\n"
    "  </recv>\n"
    "\n"
    "  <!-- set variable 8 above on 25th call, send the ACK but skip the pause for it   -->\n"
    "  <send next=\"1\" test=\"8\">\n"
    "    <![CDATA[\n"
    "\n"
    "      ACK sip:ua2@CA.cym.com SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: ua1 <sip:ua1@nnl.cym:[local_port]>;tag=[pid]SIPpTag07b[call_number]\n"
    "      To: ua2 <sip:ua2@nnl.cym:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      Contact: sip:ua1@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <pause milliseconds=\"5000\"/>\n"
    "\n"
    "  <label id=\"1\"/>\n"
    "\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:ua2@CA.cym.com SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: ua1 <sip:ua1@nnl.cym:[local_port]>;tag=[pid]SIPpTag07b[call_number]\n"
    "      To: ua2 <sip:ua2@nnl.cym:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:ua1@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <pause milliseconds=\"4000\"/>\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /************* Default_scenario[8] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'branchs' scenario.                   -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"branch_server\">\n"
    "  <recv request=\"REGISTER\">\n"
    "  </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag08[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "      Expires: 300\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Set variable 3 if the ua is of the form ua2... -->\n"
    "  <recv request=\"INVITE\" crlf=\"true\">\n"
    "    <action>\n"
    "      <ereg regexp=\"ua2\"\n"
    "            search_in=\"hdr\"\n"
    "            header=\"From: \"\n"
    "            assign_to=\"3\"/>\n"
    "    </action>\n"
    "  </recv>\n"
    "\n"
    "  <!-- send 180 then trying if variable 3 is set -->\n"
    "  <send next=\"1\" test=\"3\">\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 180 Ringing\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag08b[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- if not, send a 403 error then skip to wait for a BYE -->\n"
    "  <send next=\"2\">\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 403 Error\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag08b[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <label id=\"1\"/>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 100 Trying\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag08b[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:];tag=[pid]SIPpTag08b[call_number]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[media_ip_type] [media_ip]\n"
    "      t=0 0\n"
    "      m=audio [media_port] RTP/AVP 0\n"
    "      a=rtpmap:0 PCMU/8000\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv request=\"ACK\"\n"
    "        optional=\"true\"\n"
    "        rtd=\"true\"\n"
    "        crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <label id=\"2\"/>\n"
    "\n"
    "  <recv request=\"BYE\">\n"
    "  </recv>\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Keep the call open for a while in case the 200 is lost to be     -->\n"
    "  <!-- able to retransmit it if we receive the BYE again.               -->\n"
    "  <timewait milliseconds=\"4000\"/>\n"
    "\n"
    "  <!-- Definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- Definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",

    /* Although this scenario will not work without pcap play enabled, there is no
     * harm in including it in the binary anyway, because the user could have
     * dumped it and passed it with -sf. */

    /************* Default_scenario[9] ***************/
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp 'uac' scenario with pcap (rtp) play           -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"UAC with media\">\n"
    "  <!-- In client mode (sipp placing calls), the Call-ID MUST be         -->\n"
    "  <!-- generated by sipp. To do so, use [call_id] keyword.                -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      INVITE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag09[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 INVITE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Type: application/sdp\n"
    "      Content-Length: [len]\n"
    "\n"
    "      v=0\n"
    "      o=user1 53655765 2353687637 IN IP[local_ip_type] [local_ip]\n"
    "      s=-\n"
    "      c=IN IP[local_ip_type] [local_ip]\n"
    "      t=0 0\n"
    "      m=audio [auto_media_port] RTP/AVP 8 101\n"
    "      a=rtpmap:8 PCMA/8000\n"
    "      a=rtpmap:101 telephone-event/8000\n"
    "      a=fmtp:101 0-11,16\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"100\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <recv response=\"180\" optional=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- By adding rrs=\"true\" (Record Route Sets), the route sets         -->\n"
    "  <!-- are saved and used for following messages sent. Useful to test   -->\n"
    "  <!-- against stateful SIP proxies/B2BUAs.                             -->\n"
    "  <recv response=\"200\" rtd=\"true\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- Packet lost can be simulated in any send/recv message by         -->\n"
    "  <!-- by adding the 'lost = \"10\"'. Value can be [1-100] percent.       -->\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "\n"
    "      ACK sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag09[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 1 ACK\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Play a pre-recorded PCAP file (RTP stream)                       -->\n"
    "  <nop>\n"
    "    <action>\n"
    "      <exec play_pcap_audio=\"pcap/g711a.pcap\"/>\n"
    "    </action>\n"
    "  </nop>\n"
    "\n"
    "  <!-- Pause 8 seconds, which is approximately the duration of the      -->\n"
    "  <!-- PCAP file                                                        -->\n"
    "  <pause milliseconds=\"8000\"/>\n"
    "\n"
    "  <!-- Play an out of band DTMF '1'                                     -->\n"
    "  <nop>\n"
    "    <action>\n"
    "      <exec play_pcap_audio=\"pcap/dtmf_2833_1.pcap\"/>\n"
    "    </action>\n"
    "  </nop>\n"
    "\n"
    "  <pause milliseconds=\"1000\"/>\n"
    "\n"
    "  <!-- The 'crlf' option inserts a blank line in the statistics report. -->\n"
    "  <send retrans=\"500\">\n"
    "    <![CDATA[\n"
    "\n"
    "      BYE sip:[service]@[remote_ip]:[remote_port] SIP/2.0\n"
    "      Via: SIP/2.0/[transport] [local_ip]:[local_port];branch=[branch]\n"
    "      From: sipp <sip:sipp@[local_ip]:[local_port]>;tag=[pid]SIPpTag09[call_number]\n"
    "      To: [service] <sip:[service]@[remote_ip]:[remote_port]>[peer_tag_param]\n"
    "      Call-ID: [call_id]\n"
    "      CSeq: 2 BYE\n"
    "      Contact: sip:sipp@[local_ip]:[local_port]\n"
    "      Max-Forwards: 70\n"
    "      Subject: Performance Test\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <recv response=\"200\" crlf=\"true\">\n"
    "  </recv>\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n"
    "\n",
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'uas' scenario.                       -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"Out-of-call UAS\">\n"
    "  <recv request=\".*\" regexp_match=\"true\" />\n"
    "\n"
    "  <send>\n"
    "    <![CDATA[\n"
    "      SIP/2.0 200 OK\n"
    "      [last_Via:]\n"
    "      [last_From:]\n"
    "      [last_To:]\n"
    "      [last_Call-ID:]\n"
    "      [last_CSeq:]\n"
    "      Contact: <sip:[local_ip]:[local_port];transport=[transport]>\n"
    "      Content-Length: 0\n"
    "\n"
    "    ]]>\n"
    "  </send>\n"
    "\n"
    "  <!-- Keep the call open for a while in case the 200 is lost to be     -->\n"
    "  <!-- able to retransmit it if we receive the BYE again.               -->\n"
    "  <timewait milliseconds=\"4000\"/>\n"
    "\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n",
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n"
    "<!DOCTYPE scenario SYSTEM \"sipp.dtd\">\n"
    "\n"
    "<!-- This program is free software; you can redistribute it and/or      -->\n"
    "<!-- modify it under the terms of the GNU General Public License as     -->\n"
    "<!-- published by the Free Software Foundation; either version 2 of the -->\n"
    "<!-- License, or (at your option) any later version.                    -->\n"
    "<!--                                                                    -->\n"
    "<!-- This program is distributed in the hope that it will be useful,    -->\n"
    "<!-- but WITHOUT ANY WARRANTY; without even the implied warranty of     -->\n"
    "<!-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      -->\n"
    "<!-- GNU General Public License for more details.                       -->\n"
    "<!--                                                                    -->\n"
    "<!-- You should have received a copy of the GNU General Public License  -->\n"
    "<!-- along with this program; if not, write to the                      -->\n"
    "<!-- Free Software Foundation, Inc.,                                    -->\n"
    "<!-- 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA             -->\n"
    "<!--                                                                    -->\n"
    "<!--                 Sipp default 'uas' scenario.                       -->\n"
    "<!--                                                                    -->\n"
    "\n"
    "<scenario name=\"Out-of-call UAS\">\n"
    "  <recv request=\"DUMMY\" />\n"
    "\n"
    "  <!-- definition of the response time repartition table (unit is ms)   -->\n"
    "  <ResponseTimeRepartition value=\"10, 20, 30, 40, 50, 100, 150, 200\"/>\n"
    "\n"
    "  <!-- definition of the call length repartition table (unit is ms)     -->\n"
    "  <CallLengthRepartition value=\"10, 50, 100, 500, 1000, 5000, 10000\"/>\n"
    "\n"
    "</scenario>\n",


};


