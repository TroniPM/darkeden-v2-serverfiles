//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestNewbieItem.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_NEWBIE_ITEM_H__
#define __CG_REQUEST_NEWBIE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItem;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketSize()  { return szBYTE; }
	string getPacketName()  { return "CGRequestNewbieItem"; }
	string toString() ;
	
public:
	BYTE getItemClass(void)  { return m_ItemClass; }
	void setItemClass(BYTE itemClass) throw() { m_ItemClass = itemClass; }

private:
	BYTE m_ItemClass;
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGRequestNewbieItem(); }
	string getPacketName()  { return "CGRequestNewbieItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemHandler 
{
public:
	static void execute(CGRequestNewbieItem* pPacket, Player* player) ;
};

#endif
