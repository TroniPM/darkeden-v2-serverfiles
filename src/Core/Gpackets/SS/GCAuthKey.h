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
// NPC �� ��縦 �ֺ��� PC �鿡�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class GCAuthKey : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_AUTH_KEY; }
	PacketSize_t getPacketSize() const throw() { return szDWORD; }
	string getPacketName() const throw() { return "GCAuthKey"; }
	string toString() const throw();

	DWORD getKey() const throw() { return m_Key; }
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
	string getPacketName() const throw() { return "GCAuthKey"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_AUTH_KEY; }
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAuthKeyHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAuthKeyHandler 
{
public:
	static void execute(GCAuthKey* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
