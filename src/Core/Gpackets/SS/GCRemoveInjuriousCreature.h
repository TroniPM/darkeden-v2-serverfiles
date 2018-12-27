//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_INJURIOUS_CREATURE_H__
#define __GC_REMOVE_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveInjuriousCreature;
//
// Ŭ���̾�Ʈ�� �������� ������ RemoveInjuriousCreature ��Ŷ�̴�.
// ���ο� RemoveInjuriousCreature String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreature : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_REMOVE_INJURIOUS_CREATURE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Name.size(); }

	// get packet name
	string getPacketName()  { return "GCRemoveInjuriousCreature"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Name
	string getName()  { return m_Name; }
	void setName(const string & Name)  { m_Name = Name; }

private :

	string m_Name;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveInjuriousCreatureFactory;
//
// Factory for GCRemoveInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GCRemoveInjuriousCreature(); }

	// get packet name
	string getPacketName()  { return "GCRemoveInjuriousCreature"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_REMOVE_INJURIOUS_CREATURE; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 10; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(GCRemoveInjuriousCreature* pPacket, Player* pPlayer) ;

};

#endif
