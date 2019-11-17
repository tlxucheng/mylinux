#ifndef __SOCKETOWNER__
#define __SOCKETOWNER__

class socketowner
{
public:
    socketowner();
    virtual ~socketowner();
	
protected:
    /* What socket is this call bound to. */
    struct sipp_socket *call_socket;

#endif

