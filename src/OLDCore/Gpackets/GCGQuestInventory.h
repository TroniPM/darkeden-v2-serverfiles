//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGQuestInventory.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GQUEST_INVENTORY_H__
#define __GC_GQUEST_INVENTORY_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include <list>

#define MAX_GQUEST_INVENTORY_ITEM_NUM	100

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestInventory;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCGQuestInventory : public Packet 
{
public:
	GCGQuestInventory() throw();
	~GCGQuestInventory() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_GQUEST_INVENTORY; }
	PacketSize_t getPacketSize() const throw() { return szBYTE + szItemType * m_ItemList.size(); }
	string getPacketName() const throw() { return "GCGQuestInventory"; }
	string toString() const throw();

public:
	list<ItemType_t>&	getItemList() { return m_ItemList; }
	const list<ItemType_t>&	getItemList() const { return m_ItemList; }

private:
	list<ItemType_t>	m_ItemList;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGQuestInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestInventoryFactory : public PacketFactory 
{
public :
	GCGQuestInventoryFactory() throw() {}
	virtual ~GCGQuestInventoryFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCGQuestInventory(); }
	string getPacketName() const throw() { return "GCGQuestInventory"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GQUEST_INVENTORY; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szItemType * MAX_GQUEST_INVENTORY_ITEM_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestInventoryHandler 
{
public:
	static void execute(GCGQuestInventory* pGCGQuestInventory, Player* pPlayer) throw(Error);

};

#endif
