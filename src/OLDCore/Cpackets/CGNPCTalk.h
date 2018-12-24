//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCTalk.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_TALK_H__
#define __CG_NPC_TALK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCTalk;
//
//--------------------------------------------------------------------------------

class CGNPCTalk : public Packet {

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_NPC_TALK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet name
	string getPacketName() const throw() { return "CGNPCTalk"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCTalkFactory;
//
// Factory for CGNPCTalk
//
//--------------------------------------------------------------------------------

class CGNPCTalkFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGNPCTalk(); }

	// get packet name
	string getPacketName() const throw() { return "CGNPCTalk"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_NPC_TALK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCTalkPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//--------------------------------------------------------------------------------
//
// class CGNPCTalkHandler;
//
//--------------------------------------------------------------------------------

class CGNPCTalkHandler {
	
public:

	// execute packet's handler
	static void execute(CGNPCTalk* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
