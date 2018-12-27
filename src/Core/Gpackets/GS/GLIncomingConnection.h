//----------------------------------------------------------------------
// 
// Filename    : GLIncomingConnection.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GL_INCOMING_CONNECTION_H__
#define __GL_INCOMING_CONNECTION_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GLIncomingConnection;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ��������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class GLIncomingConnection : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GL_INCOMING_CONNECTION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return + szBYTE + m_PlayerID.size()	// Player ID
			+ szBYTE + m_ClientIP.size(); 	// client ip
	}

	// get packet name
	string getPacketName()  { return "GLIncomingConnection"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set playerID
	const string& getPlayerID()  { return m_PlayerID; }
	void setPlayerID(const string& playerID)  { m_PlayerID = playerID; }
	
	// get/set client ip
	const string& getClientIP()  { return m_ClientIP; }
	void setClientIP(const string& ip)  { m_ClientIP = ip; }
	
private :

	// Player ID
	string m_PlayerID;

	// Ŭ���̾�Ʈ�� IP
	string m_ClientIP;

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionFactory;
//
// Factory for GLIncomingConnection
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GLIncomingConnection(); }

	// get packet name
	string getPacketName()  { return "GLIncomingConnection"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GL_INCOMING_CONNECTION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return + szBYTE + 20 	// creature name
			+ szBYTE + 15; 		// client ip
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionHandler {
	
public :

	// execute packet's handler
	static void execute(GLIncomingConnection* pPacket) ;

};

#endif
