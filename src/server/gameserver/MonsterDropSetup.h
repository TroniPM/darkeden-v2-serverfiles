//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_DROP_SETUP_H__
#define __MONSTER_DROP_SETUP_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class MonsterDropSetup
{
public:
	MonsterDropSetup();
	~MonsterDropSetup();

public:
	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	bool IsDrop() const { return m_IsDrop; }
	void setDrop( bool IsDrop ) { m_IsDrop = IsDrop; }

	int getSlayerRandomDrop1() const { return m_SlayerRandomDrop1; }
	void setSlayerRandomDrop1( int RandomDrop1) { m_SlayerRandomDrop1 = RandomDrop1; }

	int getItemDropBounsRatio() const { return m_DropBounsRatio; }
	void setItemDropBounsRatio( int DropBounsRatio) { m_DropBounsRatio = DropBounsRatio; }

	int getRandomDropNum() const { return m_RandomDropNum; }
	void setRandomDropNum( int RandomDropNum) { m_RandomDropNum = RandomDropNum; }

	bool getItemSetOptionSetup() const { return m_ItemSetOptionSetup; }
	void setItemSetOptionSetup( bool ItemSetOptionSetup) { m_ItemSetOptionSetup = ItemSetOptionSetup; }

	int getItemSetOptionRatio() const { return m_ItemSetOptionRatio; }
	void setItemSetOptionRatio( int ItemSetOptionRatio) { m_ItemSetOptionRatio = ItemSetOptionRatio; }

	bool getItemSetHeroOptionSetup() const { return m_ItemSetHeroOptionSetup; }
	void setItemSetHeroOptionSetup( bool ItemSetHeroOptionSetup) { m_ItemSetHeroOptionSetup = ItemSetHeroOptionSetup; }

	int getItemSetHeroOptionRatio() const { return m_ItemSetHeroOptionRatio; }
	void setItemSetHeroOptionRatio( int ItemSetHeroOptionRatio) { m_ItemSetHeroOptionRatio = ItemSetHeroOptionRatio; }

	int getItemRareOptionBounsRatio() const { return m_RareOptionBounsRatio; }
	void setItemRareOptionBounsRatio( int RareOptionBounsRatio) { m_RareOptionBounsRatio = RareOptionBounsRatio; }

	bool IsInventory() const { return m_IsInventory; }
	void setInventory( bool IsInventory) { m_IsInventory = IsInventory; }

	int getInventorySetup1() const { return m_InventorySetup1; }
	void setInventorySetup1( int InventorySetup1) { m_InventorySetup1 = InventorySetup1; }

	int getInventoryNum() const { return m_InventoryNum; }
	void setInventoryNum( int InventoryNum) { m_InventoryNum = InventoryNum; }

	int getInventoryXY() const { return m_XY; }
	void setInventoryXY( int XY) { m_XY = XY; }

	bool IsGold() const { return m_Gold; }
	void setGold( bool Gold) { m_Gold = Gold; }

	Gold_t getGetGold() const { return m_SetGold; }
	void setGetGold( Gold_t Gold) { m_SetGold = Gold; }

	string toString() const;

private:
	int					m_ID;			// MonsterDropSetup ID
	bool					m_IsDrop;			// MonsterDropSetup ID
	int					m_SlayerRandomDrop1;			// MonsterDropSetup ID
	int					m_RandomDropNum;			// MonsterDropSetup ID
	bool					m_ItemSetOptionSetup;
	int					m_ItemSetOptionRatio;
	bool					m_ItemSetHeroOptionSetup;
	int					m_ItemSetHeroOptionRatio;
	bool					m_IsInventory;			// MonsterDropSetup ID
	int					m_InventorySetup1;			// MonsterDropSetup ID
	int					m_InventoryNum;			// MonsterDropSetup ID
	int					m_XY;			// MonsterDropSetup ID
	bool					m_Gold;
	Gold_t					m_SetGold;			// MonsterDropSetup ID
	int	m_RareOptionBounsRatio;
	int	m_DropBounsRatio;
};

//////////////////////////////////////////////////////////////////////////////
// Class MonsterDropSetupManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, MonsterDropSetup*>			HashMapMonsterDropSetup;
typedef HashMapMonsterDropSetup::iterator			HashMapMonsterDropSetupItor;
typedef HashMapMonsterDropSetup::const_iterator		HashMapMonsterDropSetupConstItor;

class MonsterDropSetupManager 
{
public:
	MonsterDropSetupManager();
	~MonsterDropSetupManager();

public:

	// clear list
	void clear() throw();

	// void load() throw();
	void load();
	
	// get MonsterDropSetup
	MonsterDropSetup* getMonsterDropSetup(int id) const;

	// add MonsterDropSetup
	void addMonsterDropSetup(MonsterDropSetup* pMonsterDropSetup) throw(DuplicatedException, Error);

	// toString for Debug
	string toString() const;

private:
	HashMapMonsterDropSetup m_MonsterDropSetups;
};

// Global Variable Definition
extern MonsterDropSetupManager* g_pMonsterDropSetupManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
