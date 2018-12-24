//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_ITEM_DROP_OPTION_H__
#define __MONSTER_ITEM_DROP_OPTION_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class MonsterItemDropOption 
{
public:
	MonsterItemDropOption();
	~MonsterItemDropOption();

public:
	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	int getOptionClassType() const { return m_OptionClassType; }
	void setOptionsClassType( int ClassType) { m_OptionClassType = ClassType; }

	int getOptionPlusPoint() const { return m_OptionPlusPoint; }
	void setOptionPlusPoint( int PlusPoint) { m_OptionPlusPoint = PlusPoint; }

	int getOptionRatio() const { return m_OptionRatio; }
	void setOptionRatio( int OptionRatio) { m_OptionRatio = OptionRatio; }

	int getOptionGroup() const { return m_OptionGroup; }
	void setOptionGroup( int OptionGroup) { m_OptionGroup = OptionGroup; }


	string toString() const;

private:
	int	m_ID;
	int	m_OptionClassType;
	int	m_OptionPlusPoint;
	int	m_OptionRatio;
	int	m_OptionGroup;
};

//////////////////////////////////////////////////////////////////////////////
// Class MonsterItemDropOptionManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, MonsterItemDropOption*>			HashMapMonsterItemDropOption;
typedef HashMapMonsterItemDropOption::iterator			HashMapMonsterItemDropOptionItor;
typedef HashMapMonsterItemDropOption::const_iterator		HashMapMonsterItemDropOptionConstItor;

class MonsterItemDropOptionManager 
{
public:
	MonsterItemDropOptionManager();
	~MonsterItemDropOptionManager();

public:

	// clear list
	void clear() throw();

	// void load() throw();
	void load() throw(Error);
	
	// get MonsterItemDropOption
	MonsterItemDropOption* getMonsterItemDropOption(int id) const;

	// add MonsterItemDropOption
	void addMonsterItemDropOption(MonsterItemDropOption* pMonsterItemDropOption) throw(DuplicatedException, Error);

	int getRandomItem(int OptionType);
	int getRandomOption(int OptionType);
	// toString for Debug
	string toString() const;

private:
	HashMapMonsterItemDropOption m_MonsterItemDropOptions;
};

// Global Variable Definition
extern MonsterItemDropOptionManager* g_pMonsterItemDropOptionManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
