//////////////////////////////////////////////////////////////////////
// 
// Filename    : SerialDatagramPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SERIAL_DATAGRAM_PACKET_H__
#define __SERIAL_DATAGRAM__PACKET_H__

// include files
#include "Packet.h"
#include "SerialDatagram.h"
#include "SocketAPI.h"


//////////////////////////////////////////////////////////////////////
//
// class SerialDatagramPacket;
//
// �������� UDP ��ſ� ���Ǵ� ��Ŷ�� ���̽� Ŭ�����̴�.
// �⺻������ �� ��Ŷ���� ���� ���� �ּ�(address)�� ��Ʈ(port)�� ����
// �ϰ� �־�� �ϸ�, SerialDatagram�� �а� ���� �޽�带 override �ؾ� �ϱ�
// ������ ���ԵǾ���.
//
//////////////////////////////////////////////////////////////////////

class SerialDatagramPacket : public Packet {
	
public :
	
	// destructor
	virtual ~SerialDatagramPacket ()  {}

	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	// �����ͱ׷� ��Ŷ�� TCP �������� ���۵Ǿ� �Դٸ� �������� ������ �����Ѵ�.
	virtual void read (SocketInputStream & iStream)  
	{ 
		throw ProtocolException("datagram packet from TCP socket"); 
	}

	// SerialDatagram ��ü���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	virtual void read (SerialDatagram & iDatagram) ;
	
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	// �����ͱ׷� ��Ŷ�� TCP �������� ����� �� ����.
	virtual void write (SocketOutputStream & oStream) 
	{ 
		throw Error("cannot write datagram-packet to TCP-socket-stream"); 
	}

	// SerialDatagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
	virtual void write (SerialDatagram & oDatagram) ;
	
	// execute packet's handler
	virtual void execute (Player* pPlayer) ;
	
	// get packet's SerialDatagramPacketID	
	virtual PacketID_t getPacketID ()  = 0;

	// get packet's body size
	virtual PacketSize_t getPacketSize ()  = 0;

	// get packet's name
	virtual string getPacketName ()  = 0;
	
	// get packet's debug string
	virtual string toString ()  = 0;

	// get/set host
	string getHost ()  { return m_Host; }
	void setHost (string host) { m_Host = host; }

	// get/set port
	uint getPort ()  { return m_Port; }
	void setPort (uint port)  { m_Port = port; }

	// get/set serial number
	uint getSerial()  { return m_Serial; }
	void setSerial( uint serial ) { m_Serial = serial; }
	

protected :

	// sender's host
	string m_Host;

	// sender's port
	uint m_Port;

	// Packet Serial Number
	uint m_Serial;
	
};

#endif
