//////////////////////////////////////////////////////////////////////////////
// Filename    : Inventory.h
// Written By  : elca@ewestsoft.com
// Revised By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Types.h"
#include "Item.h"
#include "VolumeInfo.h"
#include "InventorySlot.h"
#include <list>

class PetItem;

#define MAX_INVEN_WIDTH		10
#define MAX_INVEN_HEIGHT	6

//////////////////////////////////////////////////////////////////////////////
// Class Inventory
//////////////////////////////////////////////////////////////////////////////

class Inventory 
{
// constructor & destructor
public:
	Inventory(CoordInven_t X,CoordInven_t Y, bool bDeleteAll=true) throw();
	Inventory(const Inventory* pInventory) throw();
	~Inventory() throw();

// identity methods
public:
	string getOwner(void) const throw() { return m_Owner; }
	void setOwner(const string& owner) throw() { m_Owner = owner; }

	CoordInven_t getWidth() const throw() { return m_Width; }
	CoordInven_t getHeight() const throw() { return m_Height; }

	ItemNum_t getItemNum() const throw() { return m_TotalNum; }
	void increaseNum() throw() { m_TotalNum++; }
	void increaseNum(ItemNum_t ItemNum) throw() { m_TotalNum += ItemNum; }
	void decreaseItemNum() throw() { m_TotalNum--; }
	void decreaseItemNum(ItemNum_t ItemNum) throw() { m_TotalNum -= ItemNum; }
	void setItemNum(ItemNum_t ItemNum) throw() { m_TotalNum = ItemNum; }

	Weight_t getWeight() const throw() { return m_TotalWeight; }
	void increaseWeight(Weight_t Weight) throw() { m_TotalWeight += Weight; }
	void decreaseWeight(Weight_t Weight) throw() { m_TotalWeight -= Weight; }

	bool getDeleteAllFlag(void) const throw() { return m_bDeleteAll; }
	void setDeleteAllFlag(bool value) throw() { m_bDeleteAll = value; }

// check methods
public: 
	bool hasItem(CoordInven_t X, CoordInven_t Y) throw();
	bool hasItem(ObjectID_t ObjectID) throw();
	bool hasItemWithItemID(ItemID_t ItemID) throw();
	bool hasKey(ItemID_t TargetItemID) throw();

	bool canAdding(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();
	bool canAddingEx(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();

// addition & deletion related methods
public:
	bool  addItem(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();
	bool  CheckaddItem(CoordInven_t X, CoordInven_t Y, Item* pItem, Item* pItem2) throw();
	Item* addItemEx(CoordInven_t X, CoordInven_t Y, Item* pItem) throw(Error);
	bool  addItem(Item* pItem) throw(InventoryFullException,Error);
	bool  addItem(Item* pItem, TPOINT& pt) throw(InventoryFullException,Error);
	bool  getEmptySlot(Item* pItem, _TPOINT& p) throw()
	{
		Assert (pItem != NULL);
		return getEmptySlot( pItem->getVolumeWidth(), pItem->getVolumeHeight(), p );
	}
	bool  getEmptySlot(VolumeWidth_t ItemWidth, VolumeHeight_t ItemHeight, _TPOINT& p) throw();
	void  deleteItem(ObjectID_t ObjectID) throw(Error);
	void  deleteItem(CoordInven_t X, CoordInven_t Y) throw(Error);
	void DeleteKeyItem() throw();

	void  reloadItem(ObjectID_t ObjectID) throw(Error);
// find methods
public:
	Item* searchItem(CoordInven_t X, CoordInven_t Y, Item* pItem, TPOINT & pt) throw();

	Item* getItemWithItemID(ItemID_t itemID) throw(Error);
	Item* getBeltWithItemID(ItemID_t itemID) throw(Error);
	Item* getItemWithObjectID(ObjectID_t objectID) throw(Error);

	Item* findItemOID(ObjectID_t objectID, CoordInven_t& X, CoordInven_t& Y) throw();
	Item* findItemIID(ItemID_t ItemID, CoordInven_t& X, CoordInven_t& Y) throw();

	Item* findItemOID(ObjectID_t objectID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) throw();
	Item* findItemIID(ItemID_t ItemID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) throw();

	// ������ ��� �� ��ǥ ������ ���� ��
	Item* SerchItemCall(Item::ItemClass IClass, ItemType_t ItemType, ItemNum_t num) throw();
	bool  SerchItemCalls(Item::ItemClass IClass, ItemType_t ItemType, ItemNum_t num) throw();
	Item* findSubInventoryID(ItemID_t ItemID, Item::ItemClass IClass) throw();
	Item* findSubInventoryItem(ItemID_t ItemID, CoordInven_t X, CoordInven_t Y) throw();

	Item* findItem(Item::ItemClass IClass, ItemType_t itemType=0xFFFF) throw();
	Item* findItem(Item::ItemClass IClass, ItemType_t itemType, CoordInven_t& X, CoordInven_t& Y) throw();

	Item* SerchStoneItem(CoordInven_t X, CoordInven_t Y) throw();
	Item* searchItem2(Item* pItem, TPOINT & pt) throw();

// item manipulation related methods
public:
	Item* getItem(CoordInven_t X, CoordInven_t Y) const throw();

	InventorySlot& getInventorySlot(CoordInven_t X, CoordInven_t Y) const throw() { return m_pInventorySlot[X][Y]; }

protected:
	void  setItem(CoordInven_t X, CoordInven_t Y, Item* pItem) throw();

// packing related methods
public:
	void clear() throw(); 
	list<Item*> getList() const throw();
	int  calc2x2Item(void) const throw();

// misc methods
public:
	void   save(const string& owner) throw();
	string toString() const throw();


//#ifdef __XMAS_EVENT_CODE__
/////////////////////////////////////////////////////////////////////////
// 2001�� ũ�������� �̺�Ʈ ���� �Լ���.
// 2002�� ��̳� ��Ÿ �̺�Ʈ�� ���ؼ� ����(GiftBox�� ������� ����)
// �̺�Ʈ ������ ���ؼ� XMAS_STAR�� STAR_EVENT�� �ٲٴ� ���� ����ؾ� ��
public:
	bool hasEnoughStar(const XMAS_STAR& star) throw (Error);
	void decreaseStar(const XMAS_STAR& star) throw (Error);
	bool hasRedGiftBox(void) throw (Error);
	bool hasGreenGiftBox(void) throw (Error);
//#endif

public:
	void clearQuestItem(list<Item*>& iList) throw(Error);

////////////////////////////////////////
// member data
////////////////////////////////////////
private:
	string          m_Owner;          // �κ��丮 ������
	CoordInven_t    m_Width;          // Inventory Width
	CoordInven_t    m_Height;         // Inventory Height 
	ItemNum_t       m_TotalNum;       // Total Count
	Weight_t        m_TotalWeight;    // Total Weight
	InventorySlot** m_pInventorySlot; // InventorySlot�� ������ �迭.
	bool            m_bDeleteAll;     // ��ü�� ������ �� �����۱��� �����Ѵ�.
};

#endif	// __INVENTORY_H__
