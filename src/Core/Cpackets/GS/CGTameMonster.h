//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGTameMonster 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_TAME_MONSTER_H__
#define __CG_TAME_MONSTER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGTameMonster;
//
//////////////////////////////////////////////////////////////////////

class CGTameMonster : public Packet {

public:
	CGTameMonster() throw();
	~CGTameMonster() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_TAME_MONSTER; }
	PacketSize_t getPacketSize()  { return szObjectID; }
	string getPacketName()  { return "CGTameMonster"; }
	string toString() ;
	
public:
	// get/set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	
private :
	
	ObjectID_t m_ObjectID;  // ObjectID
};


//////////////////////////////////////////////////////////////////////
//
// class CGTameMonsterFactory;
//
// Factory for CGTameMonster
//
//////////////////////////////////////////////////////////////////////

class CGTameMonsterFactory : public PacketFactory {

public:
	CGTameMonsterFactory() throw() {}
	virtual ~CGTameMonsterFactory() throw() {}

public:
	Packet* createPacket() throw() { return new CGTameMonster(); }
	string getPacketName()  { return "CGTameMonster"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_TAME_MONSTER; }
	PacketSize_t getPacketMaxSize()  { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////
//
// class CGTameMonsterHandler;
//
//////////////////////////////////////////////////////////////////////

class CGTameMonsterHandler {
	
public:
	static void execute(CGTameMonster* pCGTameMonster, Player* player) throw(Error);
};

#endif
