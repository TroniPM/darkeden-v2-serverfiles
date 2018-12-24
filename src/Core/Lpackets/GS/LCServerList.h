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
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_SERVER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();
	
	// get packet's name
	string getPacketName() const throw() { return "LCServerList"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// ���� ���� �׷�
	ServerGroupID_t getCurrentServerGroupID() const throw() { return m_CurrentServerGroupID; }
	void setCurrentServerGroupID( ServerGroupID_t ServerGroupID ) throw() { m_CurrentServerGroupID = ServerGroupID; }

    BYTE getListNum() const throw() { return m_ServerGroupInfoList.size(); }

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
	string getPacketName() const throw() { return "LCServerList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_SERVER_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(LCServerList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
