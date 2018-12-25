//////////////////////////////////////////////////////////////////////
// 
// Filename    : DatagramPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __DATAGRAM_PACKET_H__
#define __DATAGRAM_PACKET_H__

// include files
#include "Packet.h"
#include "Datagram.h"
#include "SocketAPI.h"


//////////////////////////////////////////////////////////////////////
//
// class DatagramPacket;
//
// �������� UDP ��ſ� ���Ǵ� ��Ŷ�� ���̽� Ŭ�����̴�.
// �⺻������ �� ��Ŷ���� ���� ���� �ּ�(address)�� ��Ʈ(port)�� ����
// �ϰ� �־�� �ϸ�, Datagram�� �а� ���� �޽�带 override �ؾ� �ϱ�
// ������ ���ԵǾ���.
//
//////////////////////////////////////////////////////////////////////

class DatagramPacket : public Packet {
	
public :
	
	// destructor
	virtual ~DatagramPacket () throw () {}

	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	// �����ͱ׷� ��Ŷ�� TCP �������� ���۵Ǿ� �Դٸ� �������� ������ �����Ѵ�.
	virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error) 
	{ 
		throw ProtocolException("datagram packet from TCP socket"); 
	}

	// Datagram ��ü���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	virtual void read (Datagram & iDatagram) throw (ProtocolException, Error) = 0;
	
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	// �����ͱ׷� ��Ŷ�� TCP �������� ����� �� ����.
	virtual void write (SocketOutputStream & oStream) 
	{ 
		throw Error("cannot write datagram-packet to TCP-socket-stream"); 
	}

	// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
	virtual void write (Datagram & oDatagram) ;
	
	// execute packet's handler
	virtual void execute (Player* pPlayer) throw (ProtocolException, Error) = 0;
	
	// get packet's DatagramPacketID	
	virtual PacketID_t getPacketID ()  = 0;

	// get packet's body size
	virtual PacketSize_t getPacketSize ()  = 0;

	// get packet's name
	virtual string getPacketName ()  = 0;
	
	// get packet's debug string
	virtual string toString ()  = 0;

	// get/set host
	string getHost ()  { return m_Host; }
	void setHost (const string& host) throw () { m_Host = host; }

	// get/set port
	uint getPort ()  { return m_Port; }
	void setPort (uint port) throw () { m_Port = port; }
	

protected :

	// sender's host
	string m_Host;

	// sender's port
	uint m_Port;
	
};

#endif
