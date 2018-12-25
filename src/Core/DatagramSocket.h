//////////////////////////////////////////////////////////////////////
//
// Filename   : DatagramSocket.h
// Written By : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __DATAGRAM_SOCKET_H__
#define __DATAGRAM_SOCKET_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketAPI.h"
#include "Datagram.h"

//////////////////////////////////////////////////////////////////////
//
// class DatagramSocket;
//
// ���� �����ͱ׷� ������ ���� ���۰� �����ͱ׷� ��Ŷ�� �ִ� ũ�⺸��
// ũ�ٸ�, �Ƹ��� ��Ŷ�� �߸��� ���� ���� ���̴�.
//
//////////////////////////////////////////////////////////////////////

const uint DATAGRAM_SOCKET_BUFFER_LEN = 65536;

class DatagramSocket {

public :

	// constructor for UDP Client Socket
	DatagramSocket () throw (Error, BindException);

	// constructor for UDP Server Socket
	DatagramSocket (uint port) throw (Error, BindException);

	// destructor
	~DatagramSocket ();

	// send datagram to peer
	uint send (Datagram* pDatagram) throw (ConnectException, Error);

	// receive datagram from peer
	Datagram* receive () throw (ConnectException, Error);
	
	// get socket descriptor
	SOCKET getSOCKET ()  { return m_SocketID; }

private :

	// socket descriptor
	SOCKET m_SocketID;

	// socket address
	SOCKADDR_IN m_SockAddr;

	// internal socket input buffer
	char m_Buffer[DATAGRAM_SOCKET_BUFFER_LEN];

};

#endif
