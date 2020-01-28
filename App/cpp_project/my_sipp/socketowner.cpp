#include "sipp.hpp"

socket_owner_map_map socket_to_owners;

socketowner::socketowner()
{
}

socketowner::~socketowner()
{
}

struct sipp_socket *socketowner::associate_socket(struct sipp_socket *socket) {
    if (socket) {
        this->call_socket = socket;
        add_owner_to_socket(socket);
    }
    return socket;
}

void socketowner::add_owner_to_socket(struct sipp_socket *socket)
{
    socket_owner_map_map::iterator map_it = socket_to_owners.find(socket);
    /* No map defined for this socket. */
    if (map_it == socket_to_owners.end()) {
        socket_to_owners.insert(socket_map_pair(socket, new owner_map));
        map_it = socket_to_owners.find(socket);
        assert(map_it != socket_to_owners.end());
    }

    owner_map *socket_owner_map = (owner_map *) map_it->second;
    socket_owner_map->insert(long_owner_pair(this->ownerid, this));
}


