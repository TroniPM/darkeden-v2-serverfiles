//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGQuestCancel.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_GQUEST_CANCEL_H__
#define __CG_GQUEST_CANCEL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGGQuestCancel;
//////////////////////////////////////////////////////////////////////////////

class CGGQuestCancel : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_GQUEST_CANCEL; }
	PacketSize_t getPacketSize()  { return szDWORD; }
	string getPacketName()  { return "CGGQuestCancel"; }
	string toString() ;

public:
	DWORD getQuestID()   { return m_QuestID; }
	void setQuestID(DWORD QuestID) throw() { m_QuestID = QuestID; }

private:
	DWORD       m_QuestID;  // ����� ����
};

//////////////////////////////////////////////////////////////////////
// class CGGQuestCancelFactory;
//////////////////////////////////////////////////////////////////////

class CGGQuestCancelFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGGQuestCancel(); }
	string getPacketName()  { return "CGGQuestCancel"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_GQUEST_CANCEL; }
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////
// class CGGQuestCancelHandler;
//////////////////////////////////////////////////////////////////////

class CGGQuestCancelHandler 
{
public:
	static void execute(CGGQuestCancel* pCGGQuestCancel, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
