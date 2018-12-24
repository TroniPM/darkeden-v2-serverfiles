//////////////////////////////////////////////////////////////////////
// 
// Filename    : LGIncomingConnectionOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LG_INCOMING_CONNECTION_OK_H__
#define __LG_INCOMING_CONNECTION_OK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionOK;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionOK : public DatagramPacket {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LG_INCOMING_CONNECTION_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_PlayerID.size() 
				+ szuint
				+ szDWORD; 
	}

	// get packet name
	string getPacketName() const throw() { return "LGIncomingConnectionOK"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set player id
	string getPlayerID() const throw() { return m_PlayerID; }
	void setPlayerID(string playerID) throw() { m_PlayerID = playerID; }

	// get/set tcp port
	uint getTCPPort() const throw() { return m_TCPPort; }
	void setTCPPort(uint tcpPort) throw() { m_TCPPort = tcpPort; }

	// get/set auth key
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private :

	// � �÷��̾�� LCReconnect ��Ŷ�� ������ �ϴ����� �˾ƾ� �Ѵ�.
	string m_PlayerID;

	// ���� ������ �ڽ��� TCP ��Ʈ�� �˷������ν� 
	// �α��� ������ ���� ������ TCP ��Ʈ�� ���� �����ϴ�.
	uint m_TCPPort;

	// ���� �������� ������ ���� Ű
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionOKFactory;
//
// Factory for LGIncomingConnectionOK
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LGIncomingConnectionOK(); }

	// get packet name
	string getPacketName() const throw() { return "LGIncomingConnectionOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LG_INCOMING_CONNECTION_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionOKPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 20
				+ szuint
				+ szDWORD; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionOKHandler {
	
public:

	// execute packet's handler
	static void execute(LGIncomingConnectionOK* pPacket) throw(ProtocolException, Error);

};

#endif
