////////////////////////////////////////////////////////////////////////
//
// SocketImpl.h
//
// by Reiot
//
////////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_IMPL_H__
#define __SOCKET_IMPL_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Types.h"
#include "Exception.h"
#include "SocketAPI.h"

//////////////////////////////////////////////////
// forward declarations
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//
// class SocketImpl
//
// TCP Socket Implementation Class
//
////////////////////////////////////////////////////////////////////////

class SocketImpl {
	
//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketImpl ();
	SocketImpl (uint port);
	SocketImpl (const string & host, uint port);

	// copy constructor
	SocketImpl (const SocketImpl & impl);

	// virtual destructor
	virtual ~SocketImpl ();

//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// create socket
	void create ();
	
	// close connection
	void close ();
	
	// bind socket
	void bind ();
	void bind (uint port);
	
	// listen
	void listen (uint backlog);
	
	// connect to remote host
	void connect ();
	void connect (const string & host, uint port);
	
	// accept new connection 
	SocketImpl* accept ();
	
	// send data to peer
	uint send (const void* buf, uint len, uint flags = 0);
	
	// receive data from peer
	uint receive (void* buf, uint len, uint flags = 0);
	
	// how much available?
	uint available ();// ;
	

//////////////////////////////////////////////////
// socket option specific methods
//////////////////////////////////////////////////
public :

	// get/set socket's linger status
	uint getLinger ();
	void setLinger (uint lingertime);
	
	// get/set socket's reuse address status
	bool isReuseAddr ();
	void setReuseAddr (bool on = true);
	
	// get error
	bool isSockError();

	// get/set socket's nonblocking status
	bool isNonBlocking ();
	void setNonBlocking (bool on = true);
	
	// get/set receive buffer size
	uint getReceiveBufferSize ();
	void setReceiveBufferSize (uint size);
	
	// get/set send buffer size
	uint getSendBufferSize ();
	void setSendBufferSize (uint size);
	

//////////////////////////////////////////////////
// socket information specific methods
//////////////////////////////////////////////////
public :

    // get/set host address and port of this socket
    string getHost ()  { return m_Host; }
	uint getPort ()  { return m_Port; }
	IP_t getHostIP ()  { return (IP_t)(m_SockAddr.sin_addr.s_addr); }

	// check if socket is valid
	bool isValid ()  { return m_SocketID != INVALID_SOCKET; }

	// get socket descriptor
	SOCKET getSOCKET ()  { return m_SocketID; }

	//add by viva
	string getLocalHost();// ;


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////
protected :

    // get/set host address from socket address structure
    string _getHost ();
    void _setHost (const string & host);
			    
    // get/set port from socket address structure
	uint _getPort ();
	void _setPort (uint port);
	
	
//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
protected :
	
	// socket descriptor
	SOCKET m_SocketID;
	
	// socket address structure
	SOCKADDR_IN m_SockAddr;
	
	// peer host
	string m_Host;
	
	// peer port
	uint m_Port;
};

const static uint m_HashSize = 512;

#endif
