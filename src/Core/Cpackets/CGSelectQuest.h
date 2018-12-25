//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectQuest.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_QUEST_H__
#define __CG_SELECT_QUEST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuest;
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuest : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SELECT_QUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szQuestID + szObjectID; }

	// get packet name
	string getPacketName()  { return "CGSelectQuest"; }

	// get packet's debug string
	string toString() ;

	// get/set QuestID
	QuestID_t getQuestID()  { return m_QuestID; }
	void setQuestID( QuestID_t QuestID ) throw() { m_QuestID = QuestID; }

	ObjectID_t	getNPCObjectID() const { return m_NPCOID; }
	void		setNPCObjectID(ObjectID_t oid) { m_NPCOID = oid; }

private :

	// Quest ID
	QuestID_t m_QuestID;

	// NPC�� ObjectID
	ObjectID_t	m_NPCOID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuestFactory;
//
// Factory for CGSelectQuest
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuestFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectQuestFactory() throw() {}
	
	// destructor
	virtual ~CGSelectQuestFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSelectQuest(); }

	// get packet name
	string getPacketName()  { return "CGSelectQuest"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SELECT_QUEST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szQuestID + szObjectID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuestHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuestHandler {

public:

	// execute packet's handler
	static void execute(CGSelectQuest* pCGSelectQuest, Player* pPlayer);

};

#endif
