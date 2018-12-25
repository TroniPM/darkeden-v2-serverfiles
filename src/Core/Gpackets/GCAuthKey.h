//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAuthKey.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_AUTH_KEY_H__
#define __GC_AUTH_KEY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAuthKey;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

class GCAuthKey : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_AUTH_KEY; }
	PacketSize_t getPacketSize()  { return szDWORD; }
	string getPacketName()  { return "GCAuthKey"; }
	string toString() ;

	DWORD getKey()  { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private:
	DWORD		m_Key;
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCAuthKeyFactory;
//////////////////////////////////////////////////////////////////////////////


class GCAuthKeyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAuthKey(); }
	string getPacketName()  { return "GCAuthKey"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_AUTH_KEY; }
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAuthKeyHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAuthKeyHandler 
{
public:
	static void execute(GCAuthKey* pPacket, Player* pPlayer) ;

};

#endif
