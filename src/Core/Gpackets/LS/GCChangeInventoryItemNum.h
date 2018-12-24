//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeInventoryItemNum.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CHANGE_INVENTORY_ITEM_NUM_H__
#define __GC_CHANGE_INVENTORY_ITEM_NUM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCChangeInventoryItemNum;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCChangeInventoryItemNum {

public :
	
	// constructor
	GCChangeInventoryItemNum() throw();
	
	// destructor
	~GCChangeInventoryItemNum() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getPacketSize() const throw() { return szBYTE + szObjectID* m_ChangedItemListNum + szItemNum*m_ChangedItemListNum;} 

	// get packet's debug string
	string toString() const throw();

	// get / set ListNumber
	BYTE getChangedItemListNum() const throw() { return m_ChangedItemListNum; }
	void setChangedItemListNum(BYTE ListNum) throw() { m_ChangedItemListNum = ListNum; }

	// add / delete / clear S List
	void addChangedItemListElement(ObjectID_t objectID, BYTE itemNum) throw(); 

	// ClearList
	void clearChangedItemList() throw() { m_ChangedItemList.clear(); m_ChangedItemNumList.clear(); m_ChangedItemListNum = 0; }

	// pop front Element in Object List
	ObjectID_t popFrontChangedItemListElement() throw() { ObjectID_t item = m_ChangedItemList.front(); m_ChangedItemList.pop_front(); return item; }
	ItemNum_t popFrontChangedItemNumListElement() throw() { ItemNum_t itemNum = m_ChangedItemNumList.front(); m_ChangedItemNumList.pop_front(); return itemNum; }

protected:
	
	// List Element Number
	BYTE m_ChangedItemListNum;

	// �������� ����� Inventory���� Item List
	list<ObjectID_t> m_ChangedItemList;		// ����� Item object id
	list<ItemNum_t> m_ChangedItemNumList;	// ����� Item object id�� ���� ����.


};

#endif
