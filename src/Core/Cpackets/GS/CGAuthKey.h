//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAuthKey.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_AUTH_KEY_H__
#define __CG_AUTH_KEY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAuthKey;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class CGAuthKey : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_AUTH_KEY; }
	PacketSize_t getPacketSize()  { return szDWORD; }
	string getPacketName()  { return "CGAuthKey"; }
	string toString() ;

	DWORD getKey()  { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private:
	DWORD		m_Key;
	
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthKeyFactory;
//////////////////////////////////////////////////////////////////////////////


class CGAuthKeyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAuthKey(); }
	string getPacketName()  { return "CGAuthKey"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_AUTH_KEY; }
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthKeyHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAuthKeyHandler 
{
public:
	static void execute(CGAuthKey* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
