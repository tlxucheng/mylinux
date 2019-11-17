#include <map>
#include <iterator>
#include <list>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#include "sipp.hpp"

listener_map listeners;

listener::listener(const char *id, bool listening)
{
    this->id = strdup(id);
    this->listening = false;
    if (listening) {
        startListening();
    }
}

void listener::startListening()
{
    assert(!listening);
    listeners.insert(pair<listener_map::key_type,listener *>(listener_map::key_type(id),this));
    listening = true;
}

void listener::stopListening()
{
    assert(listening);

    listener_map::iterator listener_it;
    listener_it = listeners.find(listener_map::key_type(id));
    listeners.erase(listener_it);

    listening = false;
}

char *listener::getId()
{
    return id;
}

listener::~listener()
{
    if (listening) {
        stopListening();
    }
    free(id);
    id = NULL;

}

listener *get_listener(const char *id)
{
    listener_map::iterator listener_it = listeners.find(listener_map::key_type(id));
    if (listener_it == listeners.end()) {
        return NULL;
    }
    return listener_it->second;
}

