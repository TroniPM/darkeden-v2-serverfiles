//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_H__
#define __GC_RECONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnect;
//
// ������ �̵���, ���� ������ Ŭ���̾�Ʈ���� ���� ������ �����϶�� 
// �ϸ鼭 ������ ������ �ϴ� ��Ŷ�̴�. Ŭ���̾�Ʈ�� �� ��Ŷ�� ������,
// �������� ������ ���� ��Ŷ�� ��� ������ IP/Port �� �����ϸ� �ȴ�.
//
//////////////////////////////////////////////////////////////////////

class GCReconnect : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_RECONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_Name.size() 		// ĳ���� �̸�
			+ szPCType 						// �����̾� or �����̾�?
			+ szBYTE + m_ServerIP.size() 	// ���� ������ ���� ���� IP
			+ szDWORD; 						// ���� Ű
	}

	// get packet name
	string getPacketName()  { return "GCReconnect"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set creature name
	string getName()  { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; }

	// get/set pc type
	PCType getPCType()  { return m_PCType; }
	void setPCType(PCType pcType) throw() { m_PCType = pcType; }

	// get/set server ip
	string getServerIP()  { return m_ServerIP; }
	void setServerIP(const string & serverIP) throw() { m_ServerIP = serverIP; }

	// get/set key
	DWORD getKey()  { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private :
	
	// creature name
	string m_Name;

	// pc type
	PCType m_PCType;
	
	// New Server IP
	string m_ServerIP;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectFactory;
//
// Factory for GCReconnect
//
//////////////////////////////////////////////////////////////////////

class GCReconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCReconnect(); }

	// get packet name
	string getPacketName()  { return "GCReconnect"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_RECONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() 
	{
		return szBYTE + 20 		 		// ĳ���� �̸�
			+ szPCType 					// �����̾� or �����̾�?
			+ szBYTE + 15			 	// ���� ������ ���� ���� IP
			+ szDWORD; 					// ���� Ű
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectHandler {

public :

	// execute packet's handler
	static void execute(GCReconnect* pPacket, Player* pPlayer) ;

};

#endif
