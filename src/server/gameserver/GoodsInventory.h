//////////////////////////////////////////////////////////////////////////
// Filename			: GoodsInventory.h
// Written By		: bezz
// Description		: Ȩ���������� ������ �������� ��� �ִ� Inventory
//////////////////////////////////////////////////////////////////////////

#ifndef __GOODS_INVENTORY_H__
#define __GOODS_INVENTORY_H__

#include "Types.h"
#include "Item.h"

#include <list>

typedef struct
{
	string		m_ID;
	Item* 		m_pItem;
} BuyItem;

//////////////////////////////////////////////////////////////
// Class GoodsInventory
//////////////////////////////////////////////////////////////

class GoodsInventory
{
public:
	typedef list<BuyItem>				ListItem;
	typedef ListItem::iterator			ListItemItr;
	typedef ListItem::const_iterator	ListItemConstItr;

public:
	GoodsInventory() {};
	~GoodsInventory() throw();

public:
	ListItem& getGoods() throw() { return m_Goods; }

	// ������ �߰�
	void addItem( string ID, Item* pItem ) throw();

	// ������ ��������
	Item* popItem( ObjectID_t oid ) throw();

	// ������ ����������
	Item* getItem( ObjectID_t oid ) throw();

	// �κ��丮�� �����?
	bool empty() throw() { return m_Goods.empty(); }

	void clear() throw();

	// �κ��丮�� �ִ� ������ ����
	int getNum() const { return m_Goods.size(); }

private:
	ListItem m_Goods;
};

#endif
