#ifndef __LISTENER__
#define __LISTENER__

#include <map>
#include <iterator>
#include <list>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include "sipp.hpp"


class listener
{
public:
    listener(const char *id, bool listening);
    virtual ~listener();
    char *getId();
    virtual bool process_incoming(char * msg, struct sockaddr_storage *src) = 0;
    virtual bool process_twinSippCom(char * msg) = 0;

protected:
    void startListening();
    void stopListening();

    char *id;
    bool listening;
};

typedef std::map<std::string, listener *> listener_map;
listener * get_listener(const char *);

#endif

