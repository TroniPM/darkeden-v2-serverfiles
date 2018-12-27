//----------------------------------------------------------------------
// 
// Filename    : LGIncomingConnection.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __LG_INCOMING_CONNECTION_H__
#define __LG_INCOMING_CONNECTION_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class LGIncomingConnection;
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

class LGIncomingConnection : public DatagramPacket {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LG_INCOMING_CONNECTION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return + szBYTE + m_PlayerID.size()	// Player ID
			+ szBYTE + m_PCName.size() 		// PC name
			+ szBYTE + m_ClientIP.size(); 	// client ip
	}

	// get packet name
	string getPacketName()  { return "LGIncomingConnection"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set playerID
	string getPlayerID()  { return m_PlayerID; }
	void setPlayerID(const string& playerID)  { m_PlayerID = playerID; }
	
	// get/set pcName
	string getPCName()  { return m_PCName; }
	void setPCName(const string& pcName)  { m_PCName = pcName; }
	
	// get/set client ip
	string getClientIP()  { return m_ClientIP; }
	void setClientIP(const string& ip)  { m_ClientIP = ip; }
	
private :

	// Player ID
	string m_PlayerID;

	// PC name
	string m_PCName;

	// Ŭ���̾�Ʈ�� IP
	string m_ClientIP;

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionFactory;
//
// Factory for LGIncomingConnection
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LGIncomingConnection(); }

	// get packet name
	string getPacketName()  { return "LGIncomingConnection"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LG_INCOMING_CONNECTION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return + szBYTE + 20 	// creature name
			+ szBYTE + 20 		// PC name
			+ szBYTE + 15; 		// client ip
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class LGIncomingConnectionHandler {
	
public:

	// execute packet's handler
	static void execute(LGIncomingConnection* pPacket) ;

};

#endif
