////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinish.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_FINISH_H__
#define __CG_TRADE_FINISH_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ����� �� ������ �ڵ�
	CG_TRADE_FINISH_ACCEPT = 0,
	
	// ��ȯ�� �ź��� �� ������ �ڵ�
	CG_TRADE_FINISH_REJECT,

	// ��ȯ�� ������ �� ������ �ڵ�
	CG_TRADE_FINISH_RECONSIDER,


	CG_TRADE_FINISH_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinish;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinish : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_TRADE_FINISH; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "CGTradeFinish"; }
	string toString() ;
	
public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode()  { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; } 

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	BYTE       m_Code;           // ��ȯ �ڵ�
	

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinishFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinishFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTradeFinish(); }
	string getPacketName()  { return "CGTradeFinish"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinishHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinishHandler 
{
public:
	static void execute(CGTradeFinish* pPacket, Player* player) ;
	static void executeSlayer(CGTradeFinish* pPacket, Player* player) ;
	static void executeVampire(CGTradeFinish* pPacket, Player* player) ;
	static void executeOusters(CGTradeFinish* pPacket, Player* player) ;
	static void executeError(CGTradeFinish* pPacket, Player* player, BYTE ErrorCode) ;
};

#endif
