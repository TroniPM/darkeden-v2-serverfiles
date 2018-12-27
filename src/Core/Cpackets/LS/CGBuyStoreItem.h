////////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItem.h 
// Written By  : �輺��
// Description : 
// �÷��̾ ���� NPC�� ����â�� ����, ������ �����ϰ��� �� ��
// ������ ��Ŷ�̴�. ������ �÷��̾�� ����� ���� �κ��丮�� 
// �ڸ��� �ִ��� ������ ��, �÷��̾�� �������� �ѱ��.
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
