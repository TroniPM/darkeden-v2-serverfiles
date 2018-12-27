//////////////////////////////////////////////////////////////////////////////
// Filename    : Corpse.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CORPSE_H__
#define __CORPSE_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include "ItemFactory.h"

//////////////////////////////////////////////////////////////////////////////
// ��ü Ÿ��
//////////////////////////////////////////////////////////////////////////////
enum CorpseType 
{
	SLAYER_CORPSE = 0,
	VAMPIRE_CORPSE,
	NPC_CORPSE,
	MONSTER_CORPSE,
	OUSTERS_CORPSE
};

//////////////////////////////////////////////////////////////////////////////
// class Corpse
//////////////////////////////////////////////////////////////////////////////

class Corpse : public Item 
{
public:
	Corpse() ;
	virtual ~Corpse() ;

public:
	virtual ItemClass getItemClass()  { return ITEM_CLASS_CORPSE; }
	virtual string getObjectTableName()  { return ""; }

	virtual ItemType_t getItemType()  = 0;
	virtual void setItemType(ItemType_t monsterType)  = 0;

    virtual VolumeWidth_t getVolumeWidth()  { return 0; }
    virtual VolumeHeight_t getVolumeHeight()  { return 0; }
    virtual Weight_t getWeight()  { return 0; }

	virtual string toString()  = 0;

public:
	void addTreasure(Item* pItem) ;
	Item* getTreasure() ;
	Item* getTreasure( ObjectID_t objectID ) ;
	Item* popTreasure( ObjectID_t objectID ) ;

	BYTE getTreasureCount()  { return m_TreasureCount; }
	void setTreasureCount(BYTE Count)  { m_TreasureCount = Count; }

	ZoneCoord_t getX()  { return m_X; }
	void setX(ZoneCoord_t x)  { m_X = x; }

	ZoneCoord_t getY()  { return m_Y; }
	void setY(ZoneCoord_t y)  { m_Y = y; }

	// get/set zone
    Zone* getZone()  { return m_pZone; }
    void setZone(Zone* pZone)  { m_pZone = pZone; }

	int getLevel()  { return m_Level; }
	void setLevel(int level)  { m_Level = level; }

	Exp_t getExp()  { return m_Exp; }
	void setExp(Exp_t exp)  { m_Exp = exp; }

protected:
	list<Item*> m_Treasures;     // ������ ����Ʈ
	BYTE        m_TreasureCount; // ������ ����

	// ���� �����븦 ���� �ʻ� ��ǥ �ֱ�
	// �� �ܿ��� ��ǥ�� ����� ���� �ȵ� �� �����Ƿ� ������
	ZoneCoord_t  m_X, m_Y;

	Zone*		m_pZone;

	// ��ü�� �� ������ �� ���±� ;;;
	int 		m_Level;		// ���� -_-;
	Exp_t		m_Exp;			// �̳� ���̰� ���� ����ġ;
	
	// ���Ͱ� Relic���� �ƴ����� �����ϴ� ����
	// ���� Relic�̶��, ������ ��ü�� ������� �ʵ��� �ؾ� �Ѵ�.
};

//////////////////////////////////////////////////////////////////////////////
// class CorpseFactory
//////////////////////////////////////////////////////////////////////////////

class CorpseFactory : public ItemFactory 
{
public:
	Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return NULL; }
	string getItemName()  { return "Corpse"; }
	Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CORPSE; }
};

#endif
