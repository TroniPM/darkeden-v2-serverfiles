//////////////////////////////////////////////////////////////////////////////
// Filename    : InfoClassManager.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INFO_CLASS_MANAGER_H__
#define __INFO_CLASS_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class InfoClassManager;
//////////////////////////////////////////////////////////////////////////////

class ItemInfo;

struct OPTION_RATIO
{
	OptionType_t	optionType;
	int				ratioSum;
};

class InfoClassManager 
{
public:
	InfoClassManager() throw();
	virtual ~InfoClassManager() throw();

public:
	virtual Item::ItemClass getItemClass()  = 0;
	
	void init() throw(Error);
	void reload() throw(Error);

	virtual void load() throw(Error) = 0;

	void addItemInfo(ItemInfo* pItemInfo) throw(DuplicatedException, Error);
	ItemInfo* getItemInfo(ItemType_t ItemType) ;
	uint getInfoCount()  { return m_InfoCount + 1; }

	void removeAllItemInfo() throw(Error);

	// for Mysterious Item
	ItemType_t  getRandomItemType() ;

	Price_t		getAveragePrice() const 	{ return m_AveragePrice; }


	string toString() ;

protected:
	uint       m_InfoCount;  // #����������
	ItemInfo** m_pItemInfos; // array of item info

	int        m_TotalRatio;	// item type���� total Ratio
	Price_t	   m_AveragePrice;	// �� item class�� ��� item ������ ���
};

#endif
