#define GLOBALS_FULL_DEFINITION

#include "sipp.hpp"
#include "sip_parser.hpp"
#include "socket.hpp"
#include "assert.h"

/* start command
 * server: ./sipp -sn uas
 * clent:  ./sipp -sn uac 127.0.0.1
 *
 * 有限次数运行命令
 * server: ./sipp -sn uas
 * clent:  ./sipp -sn uac 127.0.0.1 -m 1
 *
 * 消息写入日志
 * server: ./sipp -sn uas -trace_msg
 * client: ./sipp -sn uac 127.0.0.1 -m 1 -trace_msg
 *
 * 进程启动流程
 * 1. 命令行解析
 * 2. 调用构造函数scenario(解析默认xml---->构造SendingMessage类----->解析出来需要替换的关键字)
 * 3. 调用main_scenario->runInit()，构造call类
 * 4. 初始化 CallGenerationTask 类, 根据rate创建任务
 * 5. open_connections();
 * 6. setup_ctrl_socket(); 用于接收进程运行时的命令
 * 7. traffic_thread(); 循环执行已构造的任务
 */

/* open_connections()函数流程分析
 * 解析命令函数的IP和Port
 * client端生成 local_sockaddr ----->创建 main_socket
 * erver端创建 socket--->local_sockaddr--->创建 main_socket
 */

/* setup_ctrl_socket()流程分析 
 */

/* 
 * 发包流程分析
 * main_scenario->runInit()---> connect_socket_if_needed()---->associate_socket(new_sipp_call_socket)
 * new call()-----> executeMessage()--->send_scene()--->send_raw()
 * call::init ---> associate_socket();
 * CallGenerationTask::run ---> call_ptr->associate_socket(main_socket);
 */

/*
 * logger流程分析
 * TRACE_MSG()
 */

/******************** Recv Poll Processing *********************/

extern struct sipp_socket  *sockets[SIPP_MAXFDS];

#define GLOBALS_FULL_DEFINITION

/***************** Option Handling Table *****************/
struct sipp_option {
    const char *option;
    const char *help;
    int type;
    void *data;
    /* Pass 0: Help and other options that should exit immediately. */
    /* Pass 1: All other options. */
    /* Pass 2: Scenario parsing. */
    int pass;
};

#define SIPP_OPTION_HELP	   1
#define SIPP_OPTION_INT		   2
#define SIPP_OPTION_SETFLAG	   3
#define SIPP_OPTION_UNSETFLAG	   4
#define SIPP_OPTION_STRING	   5
#define SIPP_OPTION_ARGI 	   6
#define SIPP_OPTION_TIME_SEC	   7
#define SIPP_OPTION_FLOAT	   8
#define SIPP_OPTION_BOOL	  10
#define SIPP_OPTION_VERSION	  11
#define SIPP_OPTION_TRANSPORT	  12
#define SIPP_OPTION_NEED_SSL	  13
#define SIPP_OPTION_IP		  14
#define SIPP_OPTION_MAX_SOCKET	  15
#define SIPP_OPTION_CSEQ	  16
#define SIPP_OPTION_SCENARIO	  17
#define SIPP_OPTION_RSA		  18
#define SIPP_OPTION_LIMIT	  19
#define SIPP_OPTION_USERS	  20
#define SIPP_OPTION_KEY		  21
#define SIPP_OPTION_3PCC	  22
#define SIPP_OPTION_TDMMAP	  23
#define SIPP_OPTION_TIME_MS	  24
#define SIPP_OPTION_SLAVE_CFG     25
#define SIPP_OPTION_3PCC_EXTENDED 26
#define SIPP_OPTION_INPUT_FILE	  27
#define SIPP_OPTION_TIME_MS_LONG  28
#define SIPP_OPTION_LONG          29
#define SIPP_OPTION_LONG_LONG     30
#define SIPP_OPTION_DEFAULTS      31
#define SIPP_OPTION_OOC_SCENARIO  32
#define SIPP_OPTION_INDEX_FILE    33
#define SIPP_OPTION_VAR		  34
#define SIPP_OPTION_RTCHECK	  35
#define SIPP_OPTION_LFNAME	  36
#define SIPP_OPTION_LFOVERWRITE	  37
#define SIPP_OPTION_PLUGIN	  38
#define SIPP_OPTION_NEED_SCTP	  39
#define SIPP_HELP_TEXT_HEADER	  255

/* Put each option, its help text, and type in this table. */
struct sipp_option options_table[] = {
    {"h", NULL, SIPP_OPTION_HELP, NULL, 0},
    {"help", NULL, SIPP_OPTION_HELP, NULL, 0},

    {"", "Scenario file options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"sd", "Dumps a default scenario (embedded in the SIPp executable)", SIPP_OPTION_SCENARIO, NULL, 0},
    {"sf", "Loads an alternate XML scenario file.  To learn more about XML scenario syntax, use the -sd option to dump embedded scenarios. They contain all the necessary help.", SIPP_OPTION_SCENARIO, NULL, 2},
    {"oocsf", "Load out-of-call scenario.", SIPP_OPTION_OOC_SCENARIO, NULL, 2},
    {"oocsn", "Load out-of-call scenario.", SIPP_OPTION_OOC_SCENARIO, NULL, 2},
    {
        "sn", "Use a default scenario (embedded in the SIPp executable). If this option is omitted, the Standard SipStone UAC scenario is loaded.\n"
        "Available values in this version:\n\n"
        "- 'uac'      : Standard SipStone UAC (default).\n"
        "- 'uas'      : Simple UAS responder.\n"
        "- 'regexp'   : Standard SipStone UAC - with regexp and variables.\n"
        "- 'branchc'  : Branching and conditional branching in scenarios - client.\n"
        "- 'branchs'  : Branching and conditional branching in scenarios - server.\n\n"
        "Default 3pcc scenarios (see -3pcc option):\n\n"
        "- '3pcc-C-A' : Controller A side (must be started after all other 3pcc scenarios)\n"
        "- '3pcc-C-B' : Controller B side.\n"
        "- '3pcc-A'   : A side.\n"
        "- '3pcc-B'   : B side.\n", SIPP_OPTION_SCENARIO, NULL, 2
    },

    {"", "IP, port and protocol options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
        {
        "t", "Set the transport mode:\n"
        "- u1: UDP with one socket (default),\n"
        "- un: UDP with one socket per call,\n"
        "- ui: UDP with one socket per IP address. The IP addresses must be defined in the injection file.\n"
        "- t1: TCP with one socket,\n"
        "- tn: TCP with one socket per call,\n"
#ifdef _USE_OPENSSL
        "- l1: TLS with one socket,\n"
        "- ln: TLS with one socket per call,\n"
#endif
#ifdef USE_SCTP
        "- s1: SCTP with one socket,\n"
        "- sn: SCTP with one socket per call,\n"
#endif
        "- c1: u1 + compression (only if compression plugin loaded),\n"
        "- cn: un + compression (only if compression plugin loaded).  This plugin is not provided with SIPp.\n"
        , SIPP_OPTION_TRANSPORT, NULL, 1
    },
    {"i", "Set the local IP address for 'Contact:','Via:', and 'From:' headers. Default is primary host IP address.\n", SIPP_OPTION_IP, local_ip, 1},
    {"p", "Set the local port number.  Default is a random free port chosen by the system.", SIPP_OPTION_INT, &user_port, 1},
    {"bind_local", "Bind socket to local IP address, i.e. the local IP address is used as the source IP address.  If SIPp runs in server mode it will only listen on the local IP address instead of all IP addresses.", SIPP_OPTION_SETFLAG, &bind_local, 1},
    {"ci", "Set the local control IP address", SIPP_OPTION_IP, control_ip, 1},
    {"cp", "Set the local control port number. Default is 8888.", SIPP_OPTION_INT, &control_port, 1},
    {"max_socket", "Set the max number of sockets to open simultaneously. This option is significant if you use one socket per call. Once this limit is reached, traffic is distributed over the sockets already opened. Default value is 50000", SIPP_OPTION_MAX_SOCKET, NULL, 1},
    {"max_reconnect", "Set the the maximum number of reconnection.", SIPP_OPTION_INT, &reset_number, 1},
    {"reconnect_close", "Should calls be closed on reconnect?", SIPP_OPTION_BOOL, &reset_close, 1},
    {"reconnect_sleep", "How long (in milliseconds) to sleep between the close and reconnect?", SIPP_OPTION_TIME_MS, &reset_sleep, 1},
    {"rsa", "Set the remote sending address to host:port for sending the messages.", SIPP_OPTION_RSA, NULL, 1},

   #ifdef _USE_OPENSSL
    {"tls_cert", "Set the name for TLS Certificate file. Default is 'cacert.pem", SIPP_OPTION_STRING, &tls_cert_name, 1},
    {"tls_key", "Set the name for TLS Private Key file. Default is 'cakey.pem'", SIPP_OPTION_STRING, &tls_key_name, 1},
    {"tls_crl", "Set the name for Certificate Revocation List file. If not specified, X509 CRL is not activated.", SIPP_OPTION_STRING, &tls_crl_name, 1},
#else
    {"tls_cert", NULL, SIPP_OPTION_NEED_SSL, NULL, 1},
    {"tls_key", NULL, SIPP_OPTION_NEED_SSL, NULL, 1},
    {"tls_crl", NULL, SIPP_OPTION_NEED_SSL, NULL, 1},
#endif

#ifdef USE_SCTP
    {"multihome", "Set multihome address for SCTP", SIPP_OPTION_IP, multihome_ip, 1},
    {"heartbeat", "Set heartbeat interval in ms for SCTP", SIPP_OPTION_INT, &heartbeat, 1},
    {"assocmaxret", "Set association max retransmit counter for SCTP", SIPP_OPTION_INT, &assocmaxret, 1},
    {"pathmaxret", "Set path max retransmit counter for SCTP", SIPP_OPTION_INT, &pathmaxret, 1},
    {"pmtu", "Set path MTU for SCTP", SIPP_OPTION_INT, &pmtu, 1},
    {"gracefulclose", "If true, SCTP association will be closed with SHUTDOWN (default).\n If false, SCTP association will be closed by ABORT.\n", SIPP_OPTION_BOOL, &gracefulclose, 1},
#else
    {"multihome", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
    {"heartbeat", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
    {"assocmaxret", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
    {"pathmaxret", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
    {"pmtu", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
    {"gracefulclose", NULL, SIPP_OPTION_NEED_SCTP, NULL, 1},
#endif


   {"", "SIPp overall behavior options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
   {"v", "Display version and copyright information.", SIPP_OPTION_VERSION, NULL, 0},
   {"bg", "Launch SIPp in background mode.", SIPP_OPTION_SETFLAG, &backgroundMode, 1},
   {"nostdin", "Disable stdin.\n", SIPP_OPTION_SETFLAG, &nostdin, 1},
   {"plugin", "Load a plugin.", SIPP_OPTION_PLUGIN, NULL, 1},
   {"sleep", "How long to sleep for at startup. Default unit is seconds.", SIPP_OPTION_TIME_SEC, &sleeptime, 1},
   {"skip_rlimit", "Do not perform rlimit tuning of file descriptor limits.  Default: false.", SIPP_OPTION_SETFLAG, &skip_rlimit, 1},
   {"buff_size", "Set the send and receive buffer size.", SIPP_OPTION_INT, &buff_size, 1},
   {"sendbuffer_warn", "Produce warnings instead of errors on SendBuffer failures.", SIPP_OPTION_BOOL, &sendbuffer_warn, 1},
   {"lost", "Set the number of packets to lose by default (scenario specifications override this value).", SIPP_OPTION_FLOAT, &global_lost, 1},
   {"key", "keyword value\nSet the generic parameter named \"keyword\" to \"value\".", SIPP_OPTION_KEY, NULL, 1},
   {"set", "variable value\nSet the global variable parameter named \"variable\" to \"value\".", SIPP_OPTION_VAR, NULL, 3},
   {"tdmmap", "Generate and handle a table of TDM circuits.\n"
    "A circuit must be available for the call to be placed.\n"
    "Format: -tdmmap {0-3}{99}{5-8}{1-31}", SIPP_OPTION_TDMMAP, NULL, 1},
   {"dynamicStart", "variable value\nSet the start offset of dynamic_id variable",  SIPP_OPTION_INT, &startDynamicId, 1},
   {"dynamicMax",   "variable value\nSet the maximum of dynamic_id variable     ",   SIPP_OPTION_INT, &maxDynamicId,   1},
   {"dynamicStep",  "variable value\nSet the increment of dynamic_id variable",      SIPP_OPTION_INT, &stepDynamicId,  1},


    {"", "Call behavior options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"aa", "Enable automatic 200 OK answer for INFO, UPDATE and NOTIFY messages.", SIPP_OPTION_SETFLAG, &auto_answer, 1},
    {"base_cseq", "Start value of [cseq] for each call.", SIPP_OPTION_CSEQ, NULL, 1},
    {"cid_str", "Call ID string (default %u-%p@%s).  %u=call_number, %s=ip_address, %p=process_number, %%=% (in any order).", SIPP_OPTION_STRING, &call_id_string, 1},
    {"d", "Controls the length of calls. More precisely, this controls the duration of 'pause' instructions in the scenario, if they do not have a 'milliseconds' section. Default value is 0 and default unit is milliseconds.", SIPP_OPTION_TIME_MS, &duration, 1},
    {"deadcall_wait", "How long the Call-ID and final status of calls should be kept to improve message and error logs (default unit is ms).", SIPP_OPTION_TIME_MS, &deadcall_wait, 1},
    {"auth_uri", "Force the value of the URI for authentication.\n"
     "By default, the URI is composed of remote_ip:remote_port.", SIPP_OPTION_STRING, &auth_uri, 1},
    {"au", "Set authorization username for authentication challenges. Default is taken from -s argument", SIPP_OPTION_STRING, &auth_username, 1},
    {"ap", "Set the password for authentication challenges. Default is 'password'", SIPP_OPTION_STRING, &auth_password, 1},
    {"s", "Set the username part of the request URI. Default is 'service'.", SIPP_OPTION_STRING, &service, 1},
    {"default_behaviors", "Set the default behaviors that SIPp will use.  Possbile values are:\n"
     "- all\tUse all default behaviors\n"
     "- none\tUse no default behaviors\n"
     "- bye\tSend byes for aborted calls\n"
     "- abortunexp\tAbort calls on unexpected messages\n"
     "- pingreply\tReply to ping requests\n"
     "If a behavior is prefaced with a -, then it is turned off.  Example: all,-bye\n",
     SIPP_OPTION_DEFAULTS, &default_behaviors, 1},
    {"nd", "No Default. Disable all default behavior of SIPp which are the following:\n"
     "- On UDP retransmission timeout, abort the call by sending a BYE or a CANCEL\n"
     "- On receive timeout with no ontimeout attribute, abort the call by sending a BYE or a CANCEL\n"
     "- On unexpected BYE send a 200 OK and close the call\n"
     "- On unexpected CANCEL send a 200 OK and close the call\n"
     "- On unexpected PING send a 200 OK and continue the call\n"
     "- On any other unexpected message, abort the call by sending a BYE or a CANCEL\n",
     SIPP_OPTION_UNSETFLAG, &default_behaviors, 1},
    {"pause_msg_ign", "Ignore the messages received during a pause defined in the scenario ", SIPP_OPTION_SETFLAG, &pause_msg_ign, 1},


    {"", "Injection file options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"inf", "Inject values from an external CSV file during calls into the scenarios.\n"
     "First line of this file say whether the data is to be read in sequence (SEQUENTIAL), random (RANDOM), or user (USER) order.\n"
     "Each line corresponds to one call and has one or more ';' delimited data fields. Those fields can be referred as [field0], [field1], ... in the xml scenario file.  Several CSV files can be used simultaneously (syntax: -inf f1.csv -inf f2.csv ...)", SIPP_OPTION_INPUT_FILE, NULL, 1},
    {"infindex", "file field\nCreate an index of file using field.  For example -inf users.csv -infindex users.csv 0 creates an index on the first key.", SIPP_OPTION_INDEX_FILE, NULL, 1 },
    {"ip_field", "Set which field from the injection file contains the IP address from which the client will send its messages.\n"
     "If this option is omitted and the '-t ui' option is present, then field 0 is assumed.\n"
     "Use this option together with '-t ui'", SIPP_OPTION_INT, &peripfield, 1},


    {"", "RTP behaviour options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"mi", "Set the local media IP address (default: local primary host IP address)", SIPP_OPTION_IP, media_ip, 1},
    {"rtp_echo", "Enable RTP echo. RTP/UDP packets received on port defined by -mp are echoed to their sender.\n"
     "RTP/UDP packets coming on this port + 2 are also echoed to their sender (used for sound and video echo).",
     SIPP_OPTION_SETFLAG, &rtp_echo_enabled, 1},
    {"mb", "Set the RTP echo buffer size (default: 2048).", SIPP_OPTION_INT, &media_bufsize, 1},
    {"mp", "Set the local RTP echo port number. Default is 6000.", SIPP_OPTION_INT, &user_media_port, 1},
#ifdef RTP_STREAM
	{"min_rtp_port", "Minimum port number for RTP socket range.", SIPP_OPTION_INT, &min_rtp_port, 1},
	{"max_rtp_port", "Maximum port number for RTP socket range.", SIPP_OPTION_INT, &max_rtp_port, 1},
	{"rtp_payload", "RTP default payload type.", SIPP_OPTION_INT, &rtp_default_payload, 1},
	{"rtp_threadtasks", "RTP number of playback tasks per thread.", SIPP_OPTION_INT, &rtp_tasks_per_thread, 1},
	{"rtp_buffsize", "Set the rtp socket send/receive buffer size.", SIPP_OPTION_INT, &rtp_buffsize, 1},
#endif

    {"", "Call rate options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"r", "Set the call rate (in calls per seconds).  This value can be"
     "changed during test by pressing '+','_','*' or '/'. Default is 10.\n"
     "pressing '+' key to increase call rate by 1 * rate_scale,\n"
     "pressing '-' key to decrease call rate by 1 * rate_scale,\n"
     "pressing '*' key to increase call rate by 10 * rate_scale,\n"
     "pressing '/' key to decrease call rate by 10 * rate_scale.\n",
     SIPP_OPTION_FLOAT, &rate, 1},
    {"rp", "Specify the rate period for the call rate.  Default is 1 second and default unit is milliseconds.  This allows you to have n calls every m milliseconds (by using -r n -rp m).\n"
     "Example: -r 7 -rp 2000 ==> 7 calls every 2 seconds.\n         -r 10 -rp 5s => 10 calls every 5 seconds.", SIPP_OPTION_TIME_MS, &rate_period_ms, 1},
    {"rate_scale", "Control the units for the '+', '-', '*', and '/' keys.", SIPP_OPTION_FLOAT, &rate_scale, 1},

    {"rate_increase", "Specify the rate increase every -fd units (default is seconds).  This allows you to increase the load for each independent logging period.\n"
     "Example: -rate_increase 10 -fd 10s\n"
     "  ==> increase calls by 10 every 10 seconds.", SIPP_OPTION_INT, &rate_increase, 1},
    {"rate_max", "If -rate_increase is set, then quit after the rate reaches this value.\n"
     "Example: -rate_increase 10 -rate_max 100\n"
     "  ==> increase calls by 10 until 100 cps is hit.", SIPP_OPTION_INT, &rate_max, 1},
    {"no_rate_quit", "If -rate_increase is set, do not quit after the rate reaches -rate_max.", SIPP_OPTION_UNSETFLAG, &rate_quit, 1},

    {"l", "Set the maximum number of simultaneous calls. Once this limit is reached, traffic is decreased until the number of open calls goes down. Default:\n"
     "  (3 * call_duration (s) * rate).", SIPP_OPTION_LIMIT, NULL, 1},
    {"m", "Stop the test and exit when 'calls' calls are processed", SIPP_OPTION_LONG, &stop_after, 1},
    {"users", "Instead of starting calls at a fixed rate, begin 'users' calls at startup, and keep the number of calls constant.", SIPP_OPTION_USERS, NULL, 1},


    {"", "Retransmission and timeout options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"recv_timeout", "Global receive timeout. Default unit is milliseconds. If the expected message is not received, the call times out and is aborted.", SIPP_OPTION_TIME_MS_LONG, &defl_recv_timeout, 1},
    {"send_timeout", "Global send timeout. Default unit is milliseconds. If a message is not sent (due to congestion), the call times out and is aborted.", SIPP_OPTION_TIME_MS_LONG, &defl_send_timeout, 1},
    {"timeout", "Global timeout. Default unit is seconds.  If this option is set, SIPp quits after nb units (-timeout 20s quits after 20 seconds).", SIPP_OPTION_TIME_SEC, &global_timeout, 1},
    {"timeout_error", "SIPp fails if the global timeout is reached is set (-timeout option required).", SIPP_OPTION_SETFLAG, &timeout_error, 1},
    {"max_retrans", "Maximum number of UDP retransmissions before call ends on timeout.  Default is 5 for INVITE transactions and 7 for others.", SIPP_OPTION_INT, &max_udp_retrans, 1},
    {"max_invite_retrans", "Maximum number of UDP retransmissions for invite transactions before call ends on timeout.", SIPP_OPTION_INT, &max_invite_retrans, 1},
    {"max_non_invite_retrans", "Maximum number of UDP retransmissions for non-invite transactions before call ends on timeout.", SIPP_OPTION_INT, &max_non_invite_retrans, 1},
    {"nr", "Disable retransmission in UDP mode.", SIPP_OPTION_UNSETFLAG, &retrans_enabled, 1},
    {"rtcheck", "Select the retransmission detection method: full (default) or loose.", SIPP_OPTION_RTCHECK, &rtcheck, 1},
    {"T2", "Global T2-timer in milli seconds", SIPP_OPTION_TIME_MS, &global_t2, 1},


    {"", "Third-party call control options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"3pcc", "Launch the tool in 3pcc mode (\"Third Party call control\"). The passed IP address depends on the 3PCC role.\n"
     "- When the first twin command is 'sendCmd' then this is the address of the remote twin socket.  SIPp will try to connect to this address:port to send the twin command (This instance must be started after all other 3PCC scenarios).\n"
     "    Example: 3PCC-C-A scenario.\n"
     "- When the first twin command is 'recvCmd' then this is the address of the local twin socket. SIPp will open this address:port to listen for twin command.\n"
     "    Example: 3PCC-C-B scenario.", SIPP_OPTION_3PCC, NULL, 1},
    {"master","3pcc extended mode: indicates the master number", SIPP_OPTION_3PCC_EXTENDED, &master_name, 1},
    {"slave", "3pcc extended mode: indicates the slave number", SIPP_OPTION_3PCC_EXTENDED, &slave_number, 1},
    {"slave_cfg", "3pcc extended mode: indicates the file where the master and slave addresses are stored", SIPP_OPTION_SLAVE_CFG, NULL, 1},

    {"", "Performance and watchdog options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"timer_resol", "Set the timer resolution. Default unit is milliseconds.  This option has an impact on timers precision."
     "Small values allow more precise scheduling but impacts CPU usage."
     "If the compression is on, the value is set to 50ms. The default value is 10ms.", SIPP_OPTION_TIME_MS, &timer_resolution, 1},
    {"max_recv_loops", "Set the maximum number of messages received read per cycle. Increase this value for high traffic level.  The default value is 1000.", SIPP_OPTION_INT, &max_recv_loops, 1},
    {"max_sched_loops", "Set the maximum number of calls run per event loop. Increase this value for high traffic level.  The default value is 1000.", SIPP_OPTION_INT, &max_sched_loops, 1},

    {"watchdog_interval", "Set gap between watchdog timer firings.  Default is 400.", SIPP_OPTION_TIME_MS, &watchdog_interval, 1},
    {"watchdog_reset", "If the watchdog timer has not fired in more than this time period, then reset the max triggers counters.  Default is 10 minutes.", SIPP_OPTION_TIME_MS, &watchdog_reset, 1},
    {"watchdog_minor_threshold", "If it has been longer than this period between watchdog executions count a minor trip.  Default is 500.", SIPP_OPTION_TIME_MS, &watchdog_minor_threshold, 1},
    {"watchdog_major_threshold", "If it has been longer than this period between watchdog executions count a major trip.  Default is 3000.", SIPP_OPTION_TIME_MS, &watchdog_major_threshold, 1},
    {"watchdog_major_maxtriggers", "How many times the major watchdog timer can be tripped before the test is terminated.  Default is 10.", SIPP_OPTION_INT, &watchdog_major_maxtriggers, 1},
    {"watchdog_minor_maxtriggers", "How many times the minor watchdog timer can be tripped before the test is terminated.  Default is 120.", SIPP_OPTION_INT, &watchdog_minor_maxtriggers, 1},


    {"", "Tracing, logging and statistics options:", SIPP_HELP_TEXT_HEADER, NULL, 0},
    {"f", "Set the statistics report frequency on screen. Default is 1 and default unit is seconds.", SIPP_OPTION_TIME_SEC, &report_freq, 1},

    {"trace_stat", "Dumps all statistics in <scenario_name>_<pid>.csv file. Use the '-h stat' option for a detailed description of the statistics file content.", SIPP_OPTION_SETFLAG, &dumpInFile, 1},
    {"stat_delimiter", "Set the delimiter for the statistics file", SIPP_OPTION_STRING, &stat_delimiter, 1},
    {"stf", "Set the file name to use to dump statistics", SIPP_OPTION_ARGI, &argiFileName, 1},
    {"fd", "Set the statistics dump log report frequency. Default is 60 and default unit is seconds.", SIPP_OPTION_TIME_SEC, &report_freq_dumpLog, 1},
    {"periodic_rtd", "Reset response time partition counters each logging interval.", SIPP_OPTION_SETFLAG, &periodic_rtd, 1},

    {"trace_msg", "Displays sent and received SIP messages in <scenario file name>_<pid>_messages.log", SIPP_OPTION_SETFLAG, &useMessagef, 1},
    {"message_file", "Set the name of the message log file.", SIPP_OPTION_LFNAME, &message_lfi, 1},
    {"message_overwrite", "Overwrite the message log file (default true).", SIPP_OPTION_LFOVERWRITE, &message_lfi, 1},

    {"trace_shortmsg", "Displays sent and received SIP messages as CSV in <scenario file name>_<pid>_shortmessages.log", SIPP_OPTION_SETFLAG, &useShortMessagef, 1},
    {"shortmessage_file", "Set the name of the short message log file.", SIPP_OPTION_LFNAME, &shortmessage_lfi, 1},
    {"shortmessage_overwrite", "Overwrite the short message log file (default true).", SIPP_OPTION_LFOVERWRITE, &shortmessage_lfi, 1},

    {"trace_counts", "Dumps individual message counts in a CSV file.", SIPP_OPTION_SETFLAG, &useCountf, 1},

    {"trace_err", "Trace all unexpected messages in <scenario file name>_<pid>_errors.log.", SIPP_OPTION_SETFLAG, &print_all_responses, 1},
    {"error_file", "Set the name of the error log file.", SIPP_OPTION_LFNAME, &error_lfi, 1},
    {"error_overwrite", "Overwrite the error log file (default true).", SIPP_OPTION_LFOVERWRITE, &error_lfi, 1},

    {"trace_error_codes", "Dumps the SIP response codes of unexpected messages to <scenario file name>_<pid>_error_codes.log.", SIPP_OPTION_SETFLAG, &useErrorCodesf, 1},
//	{"trace_timeout", "Displays call ids for calls with timeouts in <scenario file name>_<pid>_timeout.log", SIPP_OPTION_SETFLAG, &useTimeoutf, 1},

    {"trace_calldebug", "Dumps debugging information about aborted calls to <scenario_name>_<pid>_calldebug.log file.", SIPP_OPTION_SETFLAG, &useCallDebugf, 1},
    {"calldebug_file", "Set the name of the call debug file.", SIPP_OPTION_LFNAME, &calldebug_lfi, 1},
    {"calldebug_overwrite", "Overwrite the call debug file (default true).", SIPP_OPTION_LFOVERWRITE, &calldebug_lfi, 1},

    {"trace_screen", "Dump statistic screens in the <scenario_name>_<pid>_screens.log file when quitting SIPp. Useful to get a final status report in background mode (-bg option).", SIPP_OPTION_SETFLAG, &useScreenf, 1},

    {"trace_rtt", "Allow tracing of all response times in <scenario file name>_<pid>_rtt.csv.", SIPP_OPTION_SETFLAG, &dumpInRtt, 1},
    {"rtt_freq", "freq is mandatory. Dump response times every freq calls in the log file defined by -trace_rtt. Default value is 200.",
     SIPP_OPTION_LONG, &report_freq_dumpRtt, 1},


    {"trace_logs", "Allow tracing of <log> actions in <scenario file name>_<pid>_logs.log.", SIPP_OPTION_SETFLAG, &useLogf, 1},
    {"log_file", "Set the name of the log actions log file.", SIPP_OPTION_LFNAME, &log_lfi, 1},
    {"log_overwrite", "Overwrite the log actions log file (default true).", SIPP_OPTION_LFOVERWRITE, &log_lfi, 1},

    {"ringbuffer_files", "How many error, message, shortmessage and calldebug files should be kept after rotation?", SIPP_OPTION_INT, &ringbuffer_files, 1},
    {"ringbuffer_size", "How large should error, message, shortmessage and calldebug files be before they get rotated?", SIPP_OPTION_LONG_LONG, &ringbuffer_size, 1},
    {"max_log_size", "What is the limit for error, message, shortmessage and calldebug file sizes.", SIPP_OPTION_LONG_LONG, &max_log_size, 1},

};

void help()
{
	printf("need two para.");
}

struct sipp_option *find_option(const char *option) {
    int i;
    int max = sizeof(options_table)/sizeof(options_table[0]);

    /* Allow options to start with '-' or '--' */
    if (option[0] != '-') {
        return NULL;
    }
    option++;
    if (option[0] == '-') {
        option++;
    }

    for (i = 0; i < max; i++) {
        if (!strcmp(options_table[i].option, option)) {
            return &(options_table[i]);
        }
    }

    return NULL;
};


void pollset_process(int wait)
{	
    int loops = max_recv_loops;
	
    static int 			      read_index;
	char                      msg[SIPP_MAX_MSG_SIZE];
	struct sockaddr_storage   src;
	
	ssize_t len = read_message(sockets[read_index], msg, sizeof(msg), &src);
	if (len > 0) {
		process_message(sockets[read_index], msg, len, &src);
	} else {
		assert(0);
	}

}

void traffic_thread()
{
	while(1)
	{
	    /*
		while (sockets_pending_reset.begin() != sockets_pending_reset.end())
		{
            reset_connection(*(sockets_pending_reset.begin()));
            sockets_pending_reset.erase(sockets_pending_reset.begin());
        }
        */
		
        /* Schedule all pending calls and process their timers */
        task_list *running_tasks;

        /* We should never get so busy with running calls that we can't process some messages. */
        int loops = max_sched_loops;

		/* Now we process calls that are on the run queue. */
        running_tasks = get_running_tasks();

		task * last = NULL;

        task_list::iterator iter;
        for(iter = running_tasks->begin(); iter != running_tasks->end(); iter++) {
            if(last) {
                last -> run();
                if (sockets_pending_reset.begin() != sockets_pending_reset.end()) {
                    last = NULL;
                    break;
                }
            }
            last = *iter;
            if (--loops <= 0) {
                break;
            }
        }
        if(last) {
            last -> run();
        }

		/*
        while (sockets_pending_reset.begin() != sockets_pending_reset.end()) {
            reset_connection(*(sockets_pending_reset.begin()));
            sockets_pending_reset.erase(sockets_pending_reset.begin());
        }
        */
		
        pollset_process(running_tasks->empty());
	}
}

int main(int argc, char *argv[])
{
    int 				argi 	= 0;
	int 				i    	= 0;
    int 				pass 	= 0;
	struct  sipp_option *option = NULL;

    if(argc < 2)
	{
		help();
		exit(EXIT_OTHER);
    }

    for(pass = 0 ; pass <= 3; pass++)
    {
		for(argi = 1; argi < argc; argi++)
		{
		    option = find_option(argv[argi]);
            if(!option)
        	{
        		if (argv[argi][0] != '-') {
                    strncpy(remote_host, argv[argi], sizeof(remote_host) - 1);
                    continue;
        		}

				help();
				ERROR("Invalid argument: '%s'.\n"
                      "Use 'sipp -h' for details", argv[argi]);
        	}

			switch(option->type)
			{
				case SIPP_OPTION_HELP:
					exit(EXIT_OTHER);
				case SIPP_OPTION_INT:
					break;
				case SIPP_OPTION_TRANSPORT:
					break;
				case SIPP_OPTION_SCENARIO:
					if(main_scenario)
					{
						ERROR("Internal error, main_scenario already set");
					}
					else if(!strcmp(argv[argi - 1], "-sn"))
					{
						i = find_scenario(argv[argi]);
						//set_scenario(argv[argi]);
						main_scenario = new scenario(0, i);
						 //main_scenario->stats->setFileName(scenario_file, ".csv");
						
					}
					else 
					{
			        	ERROR("Internal error, I don't recognize %s as a scenario option\n", argv[argi] - 1);
			        }
					break;
				case SIPP_OPTION_INT:
					break;
				case SIPP_OPTION_LONG:
					*((long*)option->data) = get_long(argv[argi], argv[argi-1]);
					break;
		        case SIPP_OPTION_SETFLAG:
					*((bool *)option->data) = true;
					break;
				default
					ERROR("Internal error: I don't recognize the option type for %s", argv[argi]);				   
			}
		}
    }

	/* 操作log相关 */
	if(useMessagef == 1) {
		rotate_messagef();
	}

	/* 是否需要调用 */
    init_default_messages();

	main_scenario->runInit();
	
	main_scenario->computeSippMode();
	
	if (creationMode == MODE_CLIENT) 
    {	    	
		CallGenerationTask::initialize();
		CallGenerationTask::set_rate(rate);
    }

	open_connections();

	setup_ctrl_socket();

	traffic_thread();

    return 0;
}

