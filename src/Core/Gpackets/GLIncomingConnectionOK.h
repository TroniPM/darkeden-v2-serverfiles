//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLIncomingConnectionOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GL_INCOMING_CONNECTION_OK_H__
#define __GL_INCOMING_CONNECTION_OK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOK;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOK : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GL_INCOMING_CONNECTION_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_PlayerID.size() 
				+ szuint
				+ szDWORD; 
	}

	// get packet name
	string getPacketName()  { return "GLIncomingConnectionOK"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set player id
	string getPlayerID()  { return m_PlayerID; }
	void setPlayerID(string playerID) throw() { m_PlayerID = playerID; }

	// get/set tcp port
	uint getTCPPort()  { return m_TCPPort; }
	void setTCPPort(uint tcpPort) throw() { m_TCPPort = tcpPort; }

	// get/set auth key
	DWORD getKey()  { return m_Key; }
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
// class GLIncomingConnectionOKFactory;
//
// Factory for GLIncomingConnectionOK
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GLIncomingConnectionOK(); }

	// get packet name
	string getPacketName()  { return "GLIncomingConnectionOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GL_INCOMING_CONNECTION_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLIncomingConnectionOKPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + 20
				+ szuint
				+ szDWORD; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKHandler {
	
public :

	// execute packet's handler
	static void execute(GLIncomingConnectionOK* pPacket) throw(ProtocolException, Error);

};

#endif
