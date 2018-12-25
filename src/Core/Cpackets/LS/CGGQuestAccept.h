//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGQuestAccept.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_GQUEST_ACCEPT_H__
#define __CG_GQUEST_ACCEPT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGGQuestAccept;
//////////////////////////////////////////////////////////////////////////////

class CGGQuestAccept : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_GQUEST_ACCEPT; }
	PacketSize_t getPacketSize()  { return szDWORD; }
	string getPacketName()  { return "CGGQuestAccept"; }
	string toString() ;

public:
	DWORD getQuestID()   { return m_QuestID; }
	void setQuestID(DWORD QuestID) throw() { m_QuestID = QuestID; }

private:
	DWORD       m_QuestID;  // 기술의 종류
};

//////////////////////////////////////////////////////////////////////
// class CGGQuestAcceptFactory;
//////////////////////////////////////////////////////////////////////

class CGGQuestAcceptFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGGQuestAccept(); }
	string getPacketName()  { return "CGGQuestAccept"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_GQUEST_ACCEPT; }
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////
// class CGGQuestAcceptHandler;
//////////////////////////////////////////////////////////////////////

class CGGQuestAcceptHandler 
{
public:
	static void execute(CGGQuestAccept* pCGGQuestAccept, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
