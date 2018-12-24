//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_LOGIN_H__
#define __GC_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLogin;
//
// �α��� �������� ������ �ް�, ĳ���͸� ������ Ŭ���̾�Ʈ�� ���,
// ĳ���Ͱ� ���� ���ῡ �����ߴ� ���� �˾Ƴ���, �� ���� �����ϴ�
// ���� ������ �������϶�� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLogin : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RECONNECT_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_LoginServerIP.size() 	// ���� ���� ������
			+ szuint							// ���� ���� ��Ʈ
			+ szDWORD; 							// ���� Ű
	}

	// get packet name
	string getPacketName() const throw() { return "GCReconnectLogin"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set game server's ip
	string getLoginServerIP() const throw() { return m_LoginServerIP; }
	void setLoginServerIP(const string & ip) throw() { m_LoginServerIP = ip; }

	// get/set game server's port
	uint getLoginServerPort() const throw() { return m_LoginServerPort; }
	void setLoginServerPort(uint port) throw() { m_LoginServerPort = port; }

	// get/set key
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private :
	
	// New LoginServer's IP
	string m_LoginServerIP;

	// New LoginServer's TCP Port
	uint m_LoginServerPort;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginFactory;
//
// Factory for GCReconnectLogin
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCReconnectLogin(); }

	// get packet name
	string getPacketName() const throw() { return "GCReconnectLogin"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RECONNECT_LOGIN; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectLoginPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + 15 	// ���� ���� ������
			+ szuint		// ���� ���� ��Ʈ
			+ szDWORD; 		// ���� Ű
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectLoginHandler {

public :

	// execute packet's handler
	static void execute(GCReconnectLogin* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
