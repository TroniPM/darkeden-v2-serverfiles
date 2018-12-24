//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyFail.h 
// Written By  : excel96
// Description :
// �÷��̾ �������� �������� �����Ϸ��� �ߴµ�, 
// �������� ���Ű� �������� ��쿡 �÷��̾�� ������ ��Ŷ.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOP_BUY_FAIL_H__
#define __GC_SHOP_BUY_FAIL_H__

#include "Packet.h"
#include "PacketFactory.h"

enum GCShopBuyFailCode
{
	// ���� ���ڶ���. 
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY = 0,

	// �ڸ��� ���ڶ���.
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE,

	// NPC�� �������� �ʴ´�.
	GC_SHOP_BUY_FAIL_NPC_NOT_EXIST,

	// NPC��� ������ ���� NPC�� �ƴϴ�.
	GC_SHOP_BUY_FAIL_NOT_NPC,

	// ������ ��ġ�� �������� �������� �ʴ´�.
	GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST,

	GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLACK_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_RED_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_BLUE_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_GREEN_STAR,
	GC_SHOP_BUY_FAIL_NOT_ENOUGH_CYAN_STAR,

	GC_SHOP_BUY_FAIL_MAX
};

const string GCShopBuyFailCode2String[] =
{
	"NOT_ENOUGH_MONEY",
	"NOT_ENOUGH_SPACE",
	"NPC_NOT_EXIST",
	"NOT_NPC",
	"ITEM_NOT_EXIST",
	"NOT_ENOUGH_BLACK_STAR",
	"NOT_ENOUGH_RED_STAR",
	"NOT_ENOUGH_BLUE_STAR",
	"NOT_ENOUGH_GREEN_STAR",
	"NOT_ENOUGH_CYAN_STAR",
	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFail;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFail : public Packet 
{
public:
	GCShopBuyFail();
	~GCShopBuyFail();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_BUY_FAIL; }
	PacketSize_t getPacketSize() const throw() { return szObjectID;}
	string getPacketName() const throw() { return "GCShopBuyFail"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	BYTE getCode(void) const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

	uint getAmount(void) const { return m_Amount; }
	void setAmount(uint amount) { m_Amount = amount; }

private :
	ObjectID_t m_ObjectID;
	BYTE       m_Code;
	uint       m_Amount;
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFailFactory;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFailFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCShopBuyFail(); }
	string getPacketName() const throw() { return "GCShopBuyFail"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_BUY_FAIL; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCShopBuyFailHandler;
//////////////////////////////////////////////////////////////////////////////
class GCShopBuyFailHandler 
{
public:
	static void execute(GCShopBuyFail* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
