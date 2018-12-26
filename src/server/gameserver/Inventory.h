//////////////////////////////////////////////////////////////////////////////
// Filename    : Inventory.h
// Written By  : elca@ewestsoft.com
// Revised By  : 김성민
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
	Inventory(CoordInven_t X,CoordInven_t Y, bool bDeleteAll=true) ;
	Inventory(const Inventory* pInventory) ;
	~Inventory() ;

// identity methods
public:
	string getOwner(void)  { return m_Owner; }
	void setOwner(const string& owner) throw() { m_Owner = owner; }

	CoordInven_t getWidth()  { return m_Width; }
	CoordInven_t getHeight()  { return m_Height; }

	ItemNum_t getItemNum()  { return m_TotalNum; }
	void increaseNum() throw() { m_TotalNum++; }
	void increaseNum(ItemNum_t ItemNum) throw() { m_TotalNum += ItemNum; }
	void decreaseItemNum() throw() { m_TotalNum--; }
	void decreaseItemNum(ItemNum_t ItemNum) throw() { m_TotalNum -= ItemNum; }
	void setItemNum(ItemNum_t ItemNum) throw() { m_TotalNum = ItemNum; }

	Weight_t getWeight()  { return m_TotalWeight; }
	void increaseWeight(Weight_t Weight) throw() { m_TotalWeight += Weight; }
	void decreaseWeight(Weight_t Weight) throw() { m_TotalWeight -= Weight; }

	bool getDeleteAllFlag(void)  { return m_bDeleteAll; }
	void setDeleteAllFlag(bool value) throw() { m_bDeleteAll = value; }

// check methods
public: 
	bool hasItem(CoordInven_t X, CoordInven_t Y) ;
	bool hasItem(ObjectID_t ObjectID) ;
	bool hasItemWithItemID(ItemID_t ItemID) ;
	bool hasKey(ItemID_t TargetItemID) ;

	bool canAdding(CoordInven_t X, CoordInven_t Y, Item* pItem) ;
	bool canAddingEx(CoordInven_t X, CoordInven_t Y, Item* pItem) ;

// addition & deletion related methods
public:
	bool  addItem(CoordInven_t X, CoordInven_t Y, Item* pItem) ;
	bool  CheckaddItem(CoordInven_t X, CoordInven_t Y, Item* pItem, Item* pItem2) ;
	Item* addItemEx(CoordInven_t X, CoordInven_t Y, Item* pItem);
	bool  addItem(Item* pItem) throw(InventoryFullException,Error);
	bool  addItem(Item* pItem, TPOINT& pt) throw(InventoryFullException,Error);
	bool  getEmptySlot(Item* pItem, _TPOINT& p) throw()
	{
		Assert (pItem != NULL);
		return getEmptySlot( pItem->getVolumeWidth(), pItem->getVolumeHeight(), p );
	}
	bool  getEmptySlot(VolumeWidth_t ItemWidth, VolumeHeight_t ItemHeight, _TPOINT& p) ;
	void  deleteItem(ObjectID_t ObjectID);
	void  deleteItem(CoordInven_t X, CoordInven_t Y);
	void DeleteKeyItem() ;

	void  reloadItem(ObjectID_t ObjectID);
// find methods
public:
	Item* searchItem(CoordInven_t X, CoordInven_t Y, Item* pItem, TPOINT & pt) ;

	Item* getItemWithItemID(ItemID_t itemID);
	Item* getBeltWithItemID(ItemID_t itemID);
	Item* getItemWithObjectID(ObjectID_t objectID);

	Item* findItemOID(ObjectID_t objectID, CoordInven_t& X, CoordInven_t& Y) ;
	Item* findItemIID(ItemID_t ItemID, CoordInven_t& X, CoordInven_t& Y) ;

	Item* findItemOID(ObjectID_t objectID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) ;
	Item* findItemIID(ItemID_t ItemID, Item::ItemClass IClass, CoordInven_t& X, CoordInven_t& Y) ;

	// 아이템 재료 및 좌표 추적을 위한 것
	Item* SerchItemCall(Item::ItemClass IClass, ItemType_t ItemType, ItemNum_t num) ;
	bool  SerchItemCalls(Item::ItemClass IClass, ItemType_t ItemType, ItemNum_t num) ;
	Item* findSubInventoryID(ItemID_t ItemID, Item::ItemClass IClass) ;
	Item* findSubInventoryItem(ItemID_t ItemID, CoordInven_t X, CoordInven_t Y) ;

	Item* findItem(Item::ItemClass IClass, ItemType_t itemType=0xFFFF) ;
	Item* findItem(Item::ItemClass IClass, ItemType_t itemType, CoordInven_t& X, CoordInven_t& Y) ;

	Item* SerchStoneItem(CoordInven_t X, CoordInven_t Y) ;
	Item* searchItem2(Item* pItem, TPOINT & pt) ;

// item manipulation related methods
public:
	Item* getItem(CoordInven_t X, CoordInven_t Y) ;

	InventorySlot& getInventorySlot(CoordInven_t X, CoordInven_t Y)  { return m_pInventorySlot[X][Y]; }

protected:
	void  setItem(CoordInven_t X, CoordInven_t Y, Item* pItem) ;

// packing related methods
public:
	void clear() ; 
	list<Item*> getList() ;
	int  calc2x2Item(void) ;

// misc methods
public:
	void   save(const string& owner) ;
	string toString() ;


//#ifdef __XMAS_EVENT_CODE__
/////////////////////////////////////////////////////////////////////////
// 2001년 크리스마스 이벤트 관련 함수들.
// 2002년 어린이날 스타 이벤트를 위해서 재사용(GiftBox는 사용하지 않음)
// 이벤트 재사용을 위해서 XMAS_STAR를 STAR_EVENT로 바꾸는 것을 고려해야 함
public:
	bool hasEnoughStar(const XMAS_STAR& star);
	void decreaseStar(const XMAS_STAR& star);
	bool hasRedGiftBox(void);
	bool hasGreenGiftBox(void);
//#endif

public:
	void clearQuestItem(list<Item*>& iList);

////////////////////////////////////////
// member data
////////////////////////////////////////
private:
	string          m_Owner;          // 인벤토리 소유주
	CoordInven_t    m_Width;          // Inventory Width
	CoordInven_t    m_Height;         // Inventory Height 
	ItemNum_t       m_TotalNum;       // Total Count
	Weight_t        m_TotalWeight;    // Total Weight
	InventorySlot** m_pInventorySlot; // InventorySlot의 이차원 배열.
	bool            m_bDeleteAll;     // 객체가 삭제될 때 아이템까지 삭제한다.
};

#endif	// __INVENTORY_H__
