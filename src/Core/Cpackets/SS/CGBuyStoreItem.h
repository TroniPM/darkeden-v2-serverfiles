////////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItem.h 
// Written By  : 김성민
// Description : 
// 플레이어가 상점 NPC의 진열창을 보고, 물건을 구입하고자 할 때
// 보내는 패킷이다. 서버는 플레이어에게 충분한 돈과 인벤토리에 
// 자리가 있는지 검증한 후, 플레이어에게 아이템을 넘긴다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_BUY_STORE_ITEM_H__
#define __CG_BUY_STORE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGBuyStoreItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGBuyStoreItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_BUY_STORE_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID+szObjectID+szBYTE; }
	string getPacketName()  { return "CGBuyStoreItem"; }
	string toString() ;
	
public:
	ObjectID_t getOwnerObjectID()  { return m_OwnerObjectID; }
	void setOwnerObjectID(ObjectID_t ObjectID)  { m_OwnerObjectID = ObjectID; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t ObjectID)  { m_ItemObjectID = ObjectID; }

	BYTE getIndex(void)  { return m_Index; }
	void setIndex(BYTE index)  { m_Index = index;}

private:
	ObjectID_t		m_OwnerObjectID;
	ObjectID_t		m_ItemObjectID;
	BYTE			m_Index;
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGBuyStoreItemFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGBuyStoreItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGBuyStoreItem(); }
	string getPacketName()  { return "CGBuyStoreItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_BUY_STORE_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szObjectID+szObjectID+szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGBuyStoreItemHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGBuyStoreItemHandler 
{
public:
	static void execute(CGBuyStoreItem* pPacket, Player* player) ;
};

#endif
