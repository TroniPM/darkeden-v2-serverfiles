////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGWithdrawPet.h 
// Written By  : �輺�� 
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_WITHDRAW_PET_H__
#define __CG_WITHDRAW_PET_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGWithdrawPet;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPet : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_WITHDRAW_PET; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "CGWithdrawPet"; }
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
// class CGWithdrawPetFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPetFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGWithdrawPet(); }
	string getPacketName()  { return "CGWithdrawPet"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_WITHDRAW_PET; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGWithdrawPetHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPetHandler {
	
public:

	// execute packet's handler
	static void execute(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeSlayer(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeVampire(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
