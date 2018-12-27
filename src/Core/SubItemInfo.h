//----------------------------------------------------------------------
//
// Filename    : SubItemInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_ITEM_INFO_H__
#define __SUB_ITEM_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// Inventory ������ ��� �ִ� ��ü.
//
// GCUpdateInfo ��Ŷ�� ��ܼ� Ŭ���̾�Ʈ���� ���۵ȴ�.
// �������̳� �ɷ��ִ� ���� ���� ������ ������� �ʴ�.
//
//----------------------------------------------------------------------

class SubItemInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) ;

	// get size of object
	static uint getSize () 
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get max size of object
	static uint getMaxSize () 
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get debug string
	string toString () ;

public :

	// get/set ObjectID
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID()  { return m_ObjectID; }

	// get/set ItemClass
	void setItemClass (BYTE IClass)  { m_IClass = IClass; }
	BYTE getItemClass ()  { return m_IClass; }

	// get/set ItemType
	void setItemType (ItemType_t ItemType)  { m_ItemType = ItemType; }
	ItemType_t getItemType()  { return m_ItemType; }

	// get/set ItemNum
	void setItemNum (ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum()  { return m_ItemNum; }

	// set/set SlotID
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }
	SlotID_t getSlotID()  { return m_SlotID; }

private :

	ObjectID_t m_ObjectID; 

	BYTE m_IClass;

	ItemType_t m_ItemType;

	ItemNum_t m_ItemNum;

	SlotID_t m_SlotID;

};

#endif
