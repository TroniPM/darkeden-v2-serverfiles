//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_INJURIOUS_CREATURE_H__
#define __GC_ADD_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreature;
//
// Ŭ���̾�Ʈ�� �������� ������ AddInjuriousCreature ��Ŷ�̴�.
// ���ο� AddInjuriousCreature String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreature : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_INJURIOUS_CREATURE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Name.size(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddInjuriousCreature"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set Name
	string getName() const throw() { return m_Name; }
	void setName(const string & Name) throw() { m_Name = Name; }

private :

	string m_Name;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureFactory;
//
// Factory for GCAddInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new GCAddInjuriousCreature(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddInjuriousCreature"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_INJURIOUS_CREATURE; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 10; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(GCAddInjuriousCreature* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
