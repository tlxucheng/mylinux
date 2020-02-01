#ifndef __SCENARIO__
#define __SCENARIO__

#include <map>
#include <sys/socket.h>
#include "message.hpp"

#define MSG_TYPE_SENDCMD   0
#define MSG_TYPE_RECVCMD   1

#define MSG_TYPE_SEND      2
#define MSG_TYPE_RECV      3
#define MSG_TYPE_PAUSE     4
#define MSG_TYPE_NOP       5

#define MODE_CLIENT        0
#define MODE_SERVER        1

#define MODE_3PCC_NONE		0
#define MODE_3PCC_CONTROLLER_A  2
#define MODE_3PCC_CONTROLLER_B  3
#define MODE_3PCC_A_PASSIVE     4

/* 3pcc extended mode*/
#define MODE_MASTER             5
#define MODE_MASTER_PASSIVE     6
#define MODE_SLAVE              7

class message
{
public:
    SendingMessage *send_scheme;

    /* If this is a pause */
    int		 pause_variable;

    int      M_type;


    typedef enum {
        ContentLengthNoPresent = 0,
        ContentLengthValueZero,
        ContentLengthValueNoZero
    } ContentLengthFlag;

    ContentLengthFlag   content_length_flag ;

    int            index;

    const char *   desc;

	message(int index, const char *desc);
    ~message();
};

typedef std::vector<message *> msgvec;

class scenario
{
public:
	scenario(char * filename, int deflt);
    ~scenario();

    void runInit();

	msgvec messages;
    msgvec initmessages;
    char *name;
	
    void computeSippMode();
    
    int get_var(const char *varName, const char *what);

private:
    void checkOptionalRecv(char *elem, unsigned int scenario_file_cursor);
    
    int msg_index;
    bool last_recv_optional;
};

int find_scenario(const char *scenario);

/* There are external variable containing the current scenario */
extern scenario      *main_scenario;

extern int           creationMode;
extern int           sendMode;

extern const char * default_scenario[12];

/* Useful utility functions for parsing integers, etc. */
long get_long(const char *ptr, const char *what);
unsigned long long get_long_long(const char *ptr, const char *what);

extern int get_cr_number(const char *msg);

#endif

