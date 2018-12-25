//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCServerList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SERVER_LIST_H__
#define __LC_SERVER_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "ServerGroupInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCServerList;
//
//////////////////////////////////////////////////////////////////////

class LCServerList : public Packet {

public:

	// constructor
	// PCInfo* �迭�� ���� NULL�� �����Ѵ�.
	LCServerList() throw();

	// destructor
	// PCInfo* �迭�� �Ҵ�� ��ü�� �����Ѵ�.
	~LCServerList() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_SERVER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;
	
	// get packet's name
	string getPacketName()  { return "LCServerList"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// ���� ���� �׷�
	ServerGroupID_t getCurrentServerGroupID()  { return m_CurrentServerGroupID; }
	void setCurrentServerGroupID( ServerGroupID_t ServerGroupID ) throw() { m_CurrentServerGroupID = ServerGroupID; }

    BYTE getListNum()  { return m_ServerGroupInfoList.size(); }

	// add / delete / clear S List
	void addListElement(ServerGroupInfo* pServerGroupInfo) throw() { m_ServerGroupInfoList.push_back(pServerGroupInfo); }

	// ClearList
	void clearList() throw() { m_ServerGroupInfoList.clear(); }

	// pop front Element in Status List
	ServerGroupInfo* popFrontListElement() throw()
	{
		ServerGroupInfo* TempServerGroupInfo = m_ServerGroupInfoList.front(); m_ServerGroupInfoList.pop_front(); return TempServerGroupInfo;
	}

private : 

	// ���� ���� �׷�
	ServerGroupID_t m_CurrentServerGroupID;

	// ĳ���� ����
	list<ServerGroupInfo*> m_ServerGroupInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCServerListFactory;
//
// Factory for LCServerList
//
//////////////////////////////////////////////////////////////////////

class LCServerListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCServerList(); }

	// get packet name
	string getPacketName()  { return "LCServerList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_SERVER_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  
	{ 
		// �����̾� ������ �����̾� �������� ����� ũ�� ������,
		// �� ��Ŷ�� �ִ� ũ��� �����̾� 3 ���� ����̴�.
		return szServerGroupID + ServerGroupInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCServerListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCServerListHandler {

public:

	// execute packet's handler
	static void execute(LCServerList* pPacket, Player* pPlayer) ;

};

#endif
