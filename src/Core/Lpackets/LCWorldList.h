//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCWorldList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_WORLD_LIST_H__
#define __LC_WORLD_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WorldInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCWorldList;
//
//////////////////////////////////////////////////////////////////////

class LCWorldList : public Packet {

public:

	// constructor
	// PCInfo* �迭�� ���� NULL�� �����Ѵ�.
	LCWorldList() throw();

	// destructor
	// PCInfo* �迭�� �Ҵ�� ��ü�� �����Ѵ�.
	~LCWorldList() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_WORLD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;
	
	// get packet's name
	string getPacketName()  { return "LCWorldList"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// ���� ����
	WorldID_t getCurrentWorldID()  { return m_CurrentWorldID; }
	void setCurrentWorldID( WorldID_t WorldID ) throw() { m_CurrentWorldID = WorldID; }

    BYTE getListNum()  { return m_WorldInfoList.size(); }

	// add / delete / clear S List
	void addListElement(WorldInfo* pWorldInfo) throw() { m_WorldInfoList.push_back(pWorldInfo); }

	// ClearList
	void clearList() throw() { m_WorldInfoList.clear(); }

	// pop front Element in Status List
	WorldInfo* popFrontListElement() throw()
	{
		WorldInfo* TempWorldInfo = m_WorldInfoList.front(); m_WorldInfoList.pop_front(); return TempWorldInfo;
	}

private : 

	// ���� WorldID
	WorldID_t m_CurrentWorldID;

	// ĳ���� ����
	list<WorldInfo*> m_WorldInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCWorldListFactory;
//
// Factory for LCWorldList
//
//////////////////////////////////////////////////////////////////////

class LCWorldListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCWorldList(); }

	// get packet name
	string getPacketName()  { return "LCWorldList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_WORLD_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  
	{ 
		// �����̾� ������ �����̾� �������� ����� ũ�� ������,
		// �� ��Ŷ�� �ִ� ũ��� �����̾� 3 ���� ����̴�.
		return szWorldID + WorldInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCWorldListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCWorldListHandler {

public:

	// execute packet's handler
	static void execute(LCWorldList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
