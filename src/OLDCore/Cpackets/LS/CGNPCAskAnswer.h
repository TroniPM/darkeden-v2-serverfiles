//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCAskAnswer.h 
// Written By  : �輺��
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_ASKANSWER_H__
#define __CG_NPC_ASKANSWER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswer;
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswer : public Packet {

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_NPC_ASK_ANSWER; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szScriptID + szAnswerID; }

	// get packet name
	string getPacketName() const throw() { return "CGNPCAskAnswer"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	
	ScriptID_t getScriptID() throw() { return m_ScriptID;}
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID;}
	
	AnswerID_t getAnswerID() throw() { return m_AnswerID;}
	void setAnswerID(AnswerID_t answerID) throw() { m_AnswerID = answerID;}

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
	ScriptID_t m_ScriptID;
	AnswerID_t m_AnswerID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerFactory;
//
// Factory for CGNPCAskAnswer
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGNPCAskAnswer(); }

	// get packet name
	string getPacketName() const throw() { return "CGNPCAskAnswer"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_NPC_ASK_ANSWER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szScriptID + szAnswerID; }

};


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerHandler;
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswerHandler {
	
public:

	// execute packet's handler
	static void execute(CGNPCAskAnswer* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
