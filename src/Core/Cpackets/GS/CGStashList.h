////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashList.h 
// Written By  : �輺��
// Description : 
// Ŭ���̾�Ʈ�� ������ �ȿ� ����ִ� �������� ����Ʈ�� �䱸�� �� ���̴�
// ��Ŷ�̴�. 
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
	ObjectID_t m_ObjectID; // �÷��̾� ũ������ object id

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
