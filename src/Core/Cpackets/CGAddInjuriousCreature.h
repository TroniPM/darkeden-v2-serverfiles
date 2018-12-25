//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_INJURIOUS_CREATURE_H__
#define __CG_ADD_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGAddInjuriousCreature;
//
// Ŭ���̾�Ʈ�� �������� ������ AddInjuriousCreature ��Ŷ�̴�.
// ���ο� AddInjuriousCreature String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGAddInjuriousCreature : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_ADD_INJURIOUS_CREATURE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Name.size() + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "CGAddInjuriousCreature"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Name
	string getName()  { return m_Name; }
	void setName(const string & Name) throw() { m_Name = Name; }

private :

	string m_Name;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGAddInjuriousCreatureFactory;
//
// Factory for CGAddInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class CGAddInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGAddInjuriousCreature(); }

	// get packet name
	string getPacketName()  { return "CGAddInjuriousCreature"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_INJURIOUS_CREATURE; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 10; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGAddInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class CGAddInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(CGAddInjuriousCreature* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
