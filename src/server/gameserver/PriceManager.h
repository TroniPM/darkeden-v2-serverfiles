//////////////////////////////////////////////////////////////////////////////
// Filename    : PriceManager.h
// Written By  : �輺��
// Description : 
// �������� �������� ��� �� ��, �� �ŸŰ����� �����ϴ� Ŭ�����̴�. 
// ���������δ� ItemInfoManager�� ���� ������ �̿��� ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PRICEMANAGER_H__
#define __PRICEMANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class PriceManager
//////////////////////////////////////////////////////////////////////////////

//class Item;
class Creature;

class PriceManager
{
public:

	// ������ ������ ������ ���� ���ǰ��� ���Ѵ�.
	Price_t getPrice(Item* pItem, MarketCond_t nDiscount, ShopRackType_t shopType, Creature* pCreature) const;

	// Mysterious Item ����
	Price_t getMysteriousPrice(Item::ItemClass itemClass, Creature* pCreature) const;

	// �������� ������ ���� ���
	Price_t getRepairPrice(Item* pItem, Creature* pCreature=NULL) const;

	// �����ۿ� �� ������ ���� ���
	Price_t getSilverCoatingPrice(Item* pItem, Creature* pCreature=NULL) const;

	// �������� ����
	Price_t getStashPrice(BYTE index, Creature* pCreature=NULL) const;

	// �̺�Ʈ�� ���� �Լ�
	int getStarPrice(Item* pItem, XMAS_STAR& star) const;
	int getBallPrice(int price, XMAS_STAR& star) const;
};

// global variable declaration
extern PriceManager* g_pPriceManager;

#endif
