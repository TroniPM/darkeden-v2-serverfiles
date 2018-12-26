//////////////////////////////////////////////////////////////////////
//
// Filename    : Datagram.h
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __DATAGRAM_H__
#define __DATAGRAM_H__

#include "Types.h"
#include "Exception.h"
#include "SocketAPI.h"
#include "Packet.h"

#if __LINUX__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
#elif __WINDOWS__
	#include <winsock.h>
#endif

// forward declaration
class DatagramPacket;

//////////////////////////////////////////////////////////////////////
//
// class Datagram;
//
// UDP �������κ��� �Է¹ްų� ����� ����Ÿ�� �����̴�.
// �� Datagram�� ���� �� �Ǵ� ���� ���� �ּҸ� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class Datagram {

public :

	// constructor
	Datagram ();

	// destructor
	~Datagram ();

	// read DatagramPacket from datagram's internal buffer
	void read (char* buf, uint len);
	void read (string & str, uint len);
	void read (DatagramPacket* & pPacket);

	void read (char   & buf)  { read((char*)&buf, szchar  ); }
    void read (uchar  & buf)  { read((char*)&buf, szuchar ); }
    void read (short  & buf)  { read((char*)&buf, szshort ); }
    void read (ushort & buf)  { read((char*)&buf, szushort); }
    void read (int    & buf)  { read((char*)&buf, szint   ); }
    void read (uint   & buf)  { read((char*)&buf, szuint  ); }
    void read (long   & buf)  { read((char*)&buf, szlong  ); }
    void read (ulong  & buf)  { read((char*)&buf, szulong ); }

	// write DatagramPacket into datagram's internal buffer
	void write ( const char* buf, uint len);
	void write ( string & buf);
	void write ( DatagramPacket* pPacket);

	void write (char   buf)  { write((char*)&buf, szchar  ); }
    void write (uchar  buf)  { write((char*)&buf, szuchar ); }
    void write (short  buf)  { write((char*)&buf, szshort ); }
    void write (ushort buf)  { write((char*)&buf, szushort); }
    void write (int    buf)  { write((char*)&buf, szint   ); }
    void write (uint   buf)  { write((char*)&buf, szuint  ); }
    void write (long   buf)  { write((char*)&buf, szlong  ); }
    void write (ulong  buf)  { write((char*)&buf, szulong ); }

	// get data
	char* getData ()  { return m_Data; }

	// set data
	void setData (char* data, uint len);
	void setData (uint len); 
	
	// get length
	uint getLength ()  { return m_Length; }

	// get address
	SOCKADDR* getAddress ()  { return (SOCKADDR*)&m_SockAddr; }

	// set address
	void setAddress (SOCKADDR_IN* pSockAddr);

	// get host
	string getHost ()  { return string(inet_ntoa(m_SockAddr.sin_addr)); }

	// set host
	void setHost (string & host)  { m_SockAddr.sin_addr.s_addr = inet_addr(host.c_str()); }

	// get port 
	uint getPort ()  { return ntohs(m_SockAddr.sin_port); }

	// set port
	void setPort (uint port)  { m_SockAddr.sin_port = htons(port); }

	string toString () ;

	//�ж��Ƿ���udp����
	bool isDatagram(PacketID_t packetID);

private :

	// buffer length
	uint m_Length;

	// reading/writing offset
	uint m_InputOffset;
	uint m_OutputOffset;

	// internal buffer
	char* m_Data;

	// socket address
	SOCKADDR_IN m_SockAddr;

};

#endif
