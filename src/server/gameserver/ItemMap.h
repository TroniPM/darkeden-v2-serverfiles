//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMap.h
// Written by  : �輺��
// Description : 
// Ŭ���̾�Ʈ���� ������ ��Ʈ�� �������� ���̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_MAP__
#define __ITEM_MAP__

#include "Item.h"
#include <map>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class ItemMap
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

class ItemMap : public std::map<ulonglong, Item*> 
{
// Inner type definition
public:
	typedef std::map<ulonglong, Item*> ITEM_MAP;
	typedef ITEM_MAP::iterator         iterator;
	typedef ITEM_MAP::const_iterator   const_iterator;

// Member methods
public:
	ItemMap() throw();
	~ItemMap() throw();

public:
	// ��� �ڷ���� ������.
	void clearAll(void) throw() { clear(); m_Num2x2 = 0; m_Num2x2Temp = 0;}

	// �������� ���Ѵ�.
	bool addItem(Item* pItem) throw();

	// 2x2 �������� ������ ������ �ش�.
	void set2x2(int n) throw();
	int  get2x2() const throw() { return m_Num2x2; }

protected:
	// �������� �ʿ� �ֱ� ���� Ű�� ���Ѵ�.
	ulonglong getKey(Item* pItem) throw();

// Member data
protected:
	int m_Num2x2;
	int m_Num2x2Temp; // �ӽ� - GetKey���� �ʼ�

};




#endif
