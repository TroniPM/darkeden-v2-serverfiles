////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDepositPet.h 
// Written By  : ±è¼º¹Î 
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DEPOSIT_PET_H__
#define __CG_DEPOSIT_PET_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPet;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPet : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_DEPOSIT_PET; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "CGDepositPet"; }
	string toString() ;
	
public:
	ObjectID_t	getObjectID() const { return m_ObjectID; }
	void		setObjectID( ObjectID_t objectID ) { m_ObjectID = objectID; }

	BYTE		getIndex(void) const { return m_Index;}
	void		setIndex(BYTE index) { m_Index = index;}

private:
	ObjectID_t	m_ObjectID;
	BYTE		m_Index;

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPetFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPetFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGDepositPet(); }
	string getPacketName()  { return "CGDepositPet"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DEPOSIT_PET; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPetHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPetHandler {
	
public:

	// execute packet's handler
	static void execute(CGDepositPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeSlayer(CGDepositPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeVampire(CGDepositPet* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
