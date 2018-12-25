//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSubInventoryInfo.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SUB_INVENTORY_INFO_H__
#define __GC_SUB_INVENTORY_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

#include "InventoryInfo.h"

class GCSubInventoryInfo : public Packet
{
public:
	GCSubInventoryInfo() throw();
	~GCSubInventoryInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_SUB_INVENTORY_INFO; }
	PacketSize_t getPacketSize()  { return szObjectID + m_pInventoryInfo->getSize(); }	
	string getPacketName()  { return "GCSubInventoryInfo"; }
	string toString() ;
public:
	void		setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	ObjectID_t	getObjectID() const { return m_ObjectID; }

	void		setInventoryInfo(InventoryInfo* pInventoryInfo) { m_pInventoryInfo = pInventoryInfo; }
	InventoryInfo*	getInventoryInfo() const { return m_pInventoryInfo; }
private:
	ObjectID_t	m_ObjectID;
	InventoryInfo*	m_pInventoryInfo;
};

class GCSubInventoryInfoFactory : public PacketFactory {

public :
	
	Packet* createPacket() throw() { return new GCSubInventoryInfo(); }	
	string getPacketName()  { return "GCSubInventoryInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SUB_INVENTORY_INFO; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + InventoryInfo::getMaxSize(); }
};

class GCSubInventoryInfoHandler {
	
public :
	static void execute(GCSubInventoryInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif // __GC_SUB_INVENTORY_INFO_H__

