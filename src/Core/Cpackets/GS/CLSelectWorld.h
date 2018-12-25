//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLSelectWorld.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_SELECT_WORLD_H__
#define __CL_SELECT_WORLD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorld;
//
//////////////////////////////////////////////////////////////////////

class CLSelectWorld : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_SELECT_WORLD; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szWorldID; }

	// get packet name
	string getPacketName()  { return "CLSelectWorld"; }

	// get / set WorldID
	WorldID_t getWorldID()  { return m_WorldID; }
	void setWorldID(WorldID_t WorldID) throw() { m_WorldID = WorldID; }
	
	// get packet's debug string
	string toString()  { return "CLSelectWorld"; }

private :

	WorldID_t m_WorldID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorldFactory;
//
// Factory for CLSelectWorld
//
//////////////////////////////////////////////////////////////////////

class CLSelectWorldFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLSelectWorld(); }

	// get packet name
	string getPacketName()  { return "CLSelectWorld"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_SELECT_WORLD; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szWorldID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorldHandler;
//
//////////////////////////////////////////////////////////////////////

class CLSelectWorldHandler {

public:

	// execute packet's handler
	static void execute(CLSelectWorld* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
