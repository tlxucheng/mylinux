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
    /* What socket is this call bound to. */
    struct sipp_socket *call_socket;

private:
    void add_owner_to_socket(struct sipp_socket *socket);
};

#endif

