//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNotifyWin.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NOTIFY_WIN_H__
#define __GC_NOTIFY_WIN_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWin;
// NPC �� ��縦 �ֺ��� PC �鿡�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWin : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketSize()  { return szDWORD + szBYTE + m_Name.size(); }
	string getPacketName()  { return "GCNotifyWin"; }
	string toString() ;

	DWORD getGiftID()  { return m_GiftID; }
	void setGiftID(DWORD gID)  { m_GiftID = gID; }

	string getName()  { return m_Name; }
	void setName(const string & msg)  { m_Name = msg; }

private:
	DWORD		m_GiftID; // NPC's object id
	string		m_Name;  // chatting message
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinFactory;
//////////////////////////////////////////////////////////////////////////////


class GCNotifyWinFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCNotifyWin(); }
	string getPacketName()  { return "GCNotifyWin"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketMaxSize()  { return szDWORD + szBYTE + 2048 ; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWinHandler 
{
public:
	static void execute(GCNotifyWin* pPacket, Player* pPlayer) ;

};

#endif
