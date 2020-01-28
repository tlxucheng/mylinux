#ifndef __SOCKETOWNER__
#define __SOCKETOWNER__

class socketowner
{
public:
    socketowner();
    virtual ~socketowner();

    /* Associate/Dissociate this call with a socket. */
    struct sipp_socket *associate_socket(struct sipp_socket *socket);
	
protected:
    protected:
    /* What socket is this call bound to. */
    struct sipp_socket *call_socket;
    unsigned long ownerid;
    static unsigned long nextownerid;

private:
    void add_owner_to_socket(struct sipp_socket *socket);
};

typedef std::map<unsigned long, socketowner *> owner_map;
typedef std::pair<struct sipp_socket *,owner_map *> socket_map_pair;
typedef std::map<struct sipp_socket *, void *> socket_owner_map_map;
typedef std::list<socketowner *> owner_list;
typedef std::pair<unsigned long, socketowner *> long_owner_pair;
owner_list *get_owners_for_socket(struct sipp_socket *socket);

#endif

