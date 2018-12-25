
//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRemoveStoreItem.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_REMOVE_STORE_ITEM_H__
#define __GC_REMOVE_STORE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItem;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItem : public Packet
{
public:
	GCRemoveStoreItem() throw() { }
	virtual ~GCRemoveStoreItem() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_REMOVE_STORE_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "GCRemoveStoreItem"; }
	string toString() ;

	ObjectID_t	getOwnerObjectID() const { return m_OwnerObjectID; }
	void		setOwnerObjectID(ObjectID_t oid) { m_OwnerObjectID = oid; }

	BYTE		getIndex() const { return m_Index; }
	void		setIndex(BYTE index) { m_Index = index; }

private:
	ObjectID_t	m_OwnerObjectID;
	BYTE		m_Index;
};

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCRemoveStoreItem(); }
	string getPacketName()  { return "GCRemoveStoreItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_REMOVE_STORE_ITEM; }
	PacketSize_t getPacketMaxSize() 
	{
		return szObjectID + szBYTE;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCRemoveStoreItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCRemoveStoreItemHandler 
{
public:
	static void execute(GCRemoveStoreItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
