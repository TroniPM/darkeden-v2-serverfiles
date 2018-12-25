////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashList.h 
// Written By  : 김성민
// Description : 
// 클라이언트가 보관함 안에 들어있는 아이템의 리스트를 요구할 때 쓰이는
// 패킷이다. 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_LIST_H__
#define __CG_STASH_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashList;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashList : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_STASH_LIST; }
	PacketSize_t getPacketSize()  { return szObjectID; }
	string getPacketName()  { return "CGStashList"; }
	string toString() ;

public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t id) throw() { m_ObjectID = id; }

private:
	ObjectID_t m_ObjectID; // 플레이어 크리쳐의 object id

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashListFactory;
//
// Factory for CGStashList
//
////////////////////////////////////////////////////////////////////////////////

class CGStashListFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGStashList(); }
	string getPacketName()  { return "CGStashList"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_STASH_LIST; }
	PacketSize_t getPacketMaxSize()  { return szObjectID; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashListHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashListHandler 
{
public:
	static void execute(CGStashList* pPacket, Player* player) ;

};

#endif
