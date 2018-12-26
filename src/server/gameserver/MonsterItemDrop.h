//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_ITEM_DROP_H__
#define __MONSTER_ITEM_DROP_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include "Treasure.h"
#include <hash_map>
#include <vector>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class MonsterItemDrop
{
public:
	MonsterItemDrop();
	~MonsterItemDrop();

public:
	void parseSlayerTreasureString(const string& text) ;
	TreasureList* getSlayerTreasureList(void) const { return m_pSlayerTreasureList; }
	TreasureList* getSlayerTreasureList(void) { return m_pSlayerTreasureList; }
	void setSlayerTreasureList(TreasureList* pTreasureList) ;

	void parseVampireTreasureString(const string& text) ;
	TreasureList* getVampireTreasureList(void) const { return m_pVampireTreasureList; }
	TreasureList* getVampireTreasureList(void) { return m_pVampireTreasureList; }
	void setVampireTreasureList(TreasureList* pTreasureList) ;

	void parseOustersTreasureString(const string& text) ;
	TreasureList* getOustersTreasureList(void) const { return m_pOustersTreasureList; }
	TreasureList* getOustersTreasureList(void) { return m_pOustersTreasureList; }
	void setOustersTreasureList(TreasureList* pTreasureList) ;

	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	string getDropString() const { return m_DropString; }
	void setDropString(const string& text) { m_DropString = text; }

	int getOptionCount() const { return m_OptionCount; }
	void setOptionCount( int OptionCount ) { m_OptionCount = OptionCount; }

	string toString() const;

private:
	int					m_ID;			// MonsterItemDrop ID
	string	m_DropString;
	int	m_OptionCount;
	TreasureList*      m_pSlayerTreasureList;       // 슬레이어를 위한 보물의 리스트
	TreasureList*      m_pVampireTreasureList;       // 슬레이어를 위한 보물의 리스트
	TreasureList*      m_pOustersTreasureList;       // 슬레이어를 위한 보물의 리스트
};

//////////////////////////////////////////////////////////////////////////////
// Class MonsterItemDropManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, MonsterItemDrop*>			HashMapMonsterItemDrop;
typedef HashMapMonsterItemDrop::iterator			HashMapMonsterItemDropItor;
typedef HashMapMonsterItemDrop::const_iterator		HashMapMonsterItemDropConstItor;

class MonsterItemDropManager 
{
public:
	MonsterItemDropManager();
	~MonsterItemDropManager();

public:

	// clear list
	void clear() ;

	// void load() ;
	void load();
	
	// get MonsterItemDrop
	MonsterItemDrop* getMonsterItemDrop(int id) const;

	// add MonsterItemDrop
	void addMonsterItemDrop(MonsterItemDrop* pMonsterItemDrop) throw(DuplicatedException, Error);

	string toString() const;

private:
	HashMapMonsterItemDrop m_MonsterItemDrops;
};

// Global Variable Definition
extern MonsterItemDropManager* g_pMonsterItemDropManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
