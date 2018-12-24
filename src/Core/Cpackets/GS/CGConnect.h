//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGConnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_CONNECT_H__
#define __CG_CONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGConnect;
//
// Ŭ���̾�Ʈ�� �������� ������ ���� ��Ŷ�̴�.
// ������ �̵��� ���Ǹ�, ���� ������ �� Key �� �� �������� �����ؼ�
// ������ �޴´�. ����, �� �������� ����� ũ��ó ���̵� ��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class CGConnect : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_CONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szDWORD 						// authentication key
			+ szPCType 						// Slayer or Vampire?
			+ szBYTE + m_PCName.size() + 6; 	// name
	}

	// get packet name
	string getPacketName() const throw() { return "CGConnect"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set key
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

	// get/set PCType
	PCType getPCType() const throw() { return m_PCType; }
	void setPCType(PCType pcType) throw() { m_PCType = pcType; }
	
	// get/set pc name
	string getPCName() const throw() { return m_PCName; }
	void setPCName(string pcName) throw() { m_PCName = pcName; }

	const BYTE* getMacAddress() const { return m_MacAddress; }

private :
	
	// authentication key
	DWORD m_Key;

	// Slayer or Vampire?
	PCType m_PCType;

	// PC�� �̸�
	string m_PCName;
	
	BYTE m_MacAddress[6];
};


//////////////////////////////////////////////////////////////////////
//
// class CGConnectFactory;
//
// Factory for CGConnect
//
//////////////////////////////////////////////////////////////////////

class CGConnectFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGConnect(); }

	// get packet name
	string getPacketName() const throw() { return "CGConnect"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_CONNECT; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return szDWORD 			// authentication key
			+ szPCType 			// Slayer or Vampire
			+ szBYTE + 20 + 6; 		// name
	}

};

//////////////////////////////////////////////////////////////////////
//
// class CGConnectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGConnectHandler {

public:

	// execute packet's handler
	static void execute(CGConnect* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
