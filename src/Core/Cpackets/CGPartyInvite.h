//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyInvite.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_INVITE_H__
#define __CG_PARTY_INVITE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// 파티 가입 관련 코드
//////////////////////////////////////////////////////////////////////////////
enum
{
	CG_PARTY_INVITE_REQUEST = 0,
	CG_PARTY_INVITE_CANCEL,
	CG_PARTY_INVITE_ACCEPT,
	CG_PARTY_INVITE_REJECT,
	CG_PARTY_INVITE_BUSY,

	CG_PARTY_INVITE_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class CGPartyInvite
//////////////////////////////////////////////////////////////////////////////

class CGPartyInvite : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_PARTY_INVITE; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "CGPartyInvite"; }
	string toString() ;
	
public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode(void)  { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // 상대방의 OID
	BYTE       m_Code;           // 코드

};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyInviteFactory;
//////////////////////////////////////////////////////////////////////////////

class CGPartyInviteFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGPartyInvite(); }
	string getPacketName()  { return "CGPartyInvite"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_PARTY_INVITE; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyInviteHandler
//////////////////////////////////////////////////////////////////////////////

class CGPartyInviteHandler 
{
public:
	static void execute(CGPartyInvite* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeError(CGPartyInvite* pPacket, Player* player, BYTE ErrorCode) throw(ProtocolException, Error);
};

#endif
