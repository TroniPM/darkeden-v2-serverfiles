//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSilverCoating.h 
// Written By  : ±è¼º¹Î
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SILVER_COATING_H__
#define __CG_SILVER_COATING_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoating
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoating : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t   getPacketID()    { return PACKET_CG_SILVER_COATING; }
	PacketSize_t getPacketSize()  { return szObjectID; }
	string       getPacketName()  { return "CGSilverCoating"; }
	string       toString() ;
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private:
	ObjectID_t m_ObjectID; // Item Object ID

};


//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoatingFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoatingFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGSilverCoating(); }
	string getPacketName()  { return "CGSilverCoating"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SILVER_COATING; }
	PacketSize_t getPacketMaxSize()  { return szObjectID; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGSilverCoatingHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSilverCoatingHandler 
{
public:
	static void execute(CGSilverCoating* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
