////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeMoney.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_MONEY_H__
#define __CG_TRADE_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ���� �׼��� �ø���.
	CG_TRADE_MONEY_INCREASE = 0,

	// ��ȯ�� ���� �׼��� ���δ�.
	CG_TRADE_MONEY_DECREASE
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeMoney;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeMoney : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_TRADE_MONEY; }
	PacketSize_t getPacketSize()  { return szObjectID + szGold + szBYTE; }
	string getPacketName()  { return "CGTradeMoney"; }
	string toString() ;
	
public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	Gold_t getAmount()  { return m_Gold; }
	void setAmount(Gold_t gold) throw() { m_Gold = gold; }

	BYTE getCode()  { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	Gold_t     m_Gold;           // ���ϴ� �׼�
	BYTE       m_Code;           // �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeMoneyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeMoneyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTradeMoney(); }
	string getPacketName()  { return "CGTradeMoney"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_TRADE_MONEY; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szGold + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeMoneyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeMoneyHandler 
{
public:
	static void execute(CGTradeMoney* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeSlayer(CGTradeMoney* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeVampire(CGTradeMoney* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOusters(CGTradeMoney* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeError(CGTradeMoney* pPacket, Player* player, BYTE ErrorCode) throw(ProtocolException, Error);
};

#endif
