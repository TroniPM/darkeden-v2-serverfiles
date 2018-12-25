//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_LEAVE_H__
#define __CG_PARTY_LEAVE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeave
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeave : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_PARTY_LEAVE; }
	PacketSize_t getPacketSize()  { return szBYTE + m_TargetName.size(); }
	string getPacketName()  { return "CGPartyLeave"; }
	string toString() ;
	
public:
	string getTargetName(void)  { return m_TargetName; }
	void setTargetName(const string& name) { m_TargetName = name; }

private:
	string m_TargetName;
};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeaveFactory;
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeaveFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGPartyLeave(); }
	string getPacketName()  { return "CGPartyLeave"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_PARTY_LEAVE; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + 10; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGPartyLeaveHandler
//////////////////////////////////////////////////////////////////////////////

class CGPartyLeaveHandler 
{
public:
	static void execute(CGPartyLeave* pPacket, Player* player) ;
};

#endif
