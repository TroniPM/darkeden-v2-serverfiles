//////////////////////////////////////////////////////////////////////////////
// Filename    : InventoryInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// �κ��丮 �ȿ� �ִ� �����۵��� ���� ����Ʈ�̴�.
// �κ��丮 ���� ������ �����۵鿡 ���� ������ InventorySlotInfo�� ����.
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_INFO_H__
#define __INVENTORY_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "InventorySlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class InventoryInfo;
//////////////////////////////////////////////////////////////////////////////

class InventoryInfo 
{
public:
	InventoryInfo ();
	~InventoryInfo ();
	
public:
    void read (SocketInputStream & iStream);
    void write (SocketOutputStream & oStream) ;

	PacketSize_t getSize ();

	static uint getMaxSize() throw() 
	{
		return szBYTE + (InventorySlotInfo::getMaxSize()* 60);
	}

	string toString () ;

public:
	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	void addListElement(InventorySlotInfo* pInventorySlotInfo) throw() { m_InventorySlotInfoList.push_back(pInventorySlotInfo); }

	void clearList() throw() { m_InventorySlotInfoList.clear(); m_ListNum = 0; }

	InventorySlotInfo* popFrontListElement() throw() 
	{ 
		InventorySlotInfo* TempInventorySlotInfo = m_InventorySlotInfoList.front(); m_InventorySlotInfoList.pop_front(); return TempInventorySlotInfo; 
	}

private:
	BYTE m_ListNum; // number of item in inventory
	list<InventorySlotInfo*> m_InventorySlotInfoList; // actual item info

};

#endif
