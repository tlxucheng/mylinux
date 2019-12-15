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


class message
{
public:
    /* If this is a pause */
    int		 pause_variable;

    int      M_type;

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

private:
   int msg_index;
	
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

#endif

