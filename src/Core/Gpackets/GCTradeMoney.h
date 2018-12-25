////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeMoney.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_MONEY_H__
#define __GC_TRADE_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ������ ��ȯ�� ���� �׼��� �÷ȴ�.
	GC_TRADE_MONEY_INCREASE = 0,

	// ������ ��ȯ�� ���� �׼��� �ٿ���.
	GC_TRADE_MONEY_DECREASE,

	// ������ �κ��丮���� ���� �ݾ�
	GC_TRADE_MONEY_INCREASE_RESULT,

	// ������ �κ��丮���� ���� �ݾ�
	GC_TRADE_MONEY_DECREASE_RESULT
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoney;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoney : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_TRADE_MONEY; }
	PacketSize_t getPacketSize()  { return szObjectID + szGold + szBYTE ; }
	string getPacketName()  { return "GCTradeMoney"; }
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
// class GCTradeMoneyFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeMoney(); }
	string getPacketName()  { return "GCTradeMoney"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TRADE_MONEY; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szGold + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeMoneyHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeMoneyHandler 
{
public:
	static void execute(GCTradeMoney* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
