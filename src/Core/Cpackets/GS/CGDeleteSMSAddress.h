//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDeleteSMSAddress.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DELETE_SMS_ADDRESS_H__
#define __CG_DELETE_SMS_ADDRESS_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGDeleteSMSAddress;
//////////////////////////////////////////////////////////////////////////////

class CGDeleteSMSAddress : public Packet 
{
public:
	CGDeleteSMSAddress() throw();
	~CGDeleteSMSAddress() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_DELETE_SMS_ADDRESS; }
	PacketSize_t getPacketSize()  { return szDWORD; }
	string getPacketName()  { return "CGDeleteSMSAddress"; }
	string toString() ;
	
public:
	DWORD	getElementID() const { return m_ElementID; }
	void	setElementID( DWORD eID ) { m_ElementID = eID; }

private:
	DWORD	m_ElementID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGDeleteSMSAddressFactory;
//////////////////////////////////////////////////////////////////////////////

class CGDeleteSMSAddressFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGDeleteSMSAddress(); }
	string getPacketName()  { return "CGDeleteSMSAddress"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DELETE_SMS_ADDRESS; }
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGDeleteSMSAddressHandler;
//////////////////////////////////////////////////////////////////////////////

class CGDeleteSMSAddressHandler 
{
public:
	static void execute(CGDeleteSMSAddress* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
