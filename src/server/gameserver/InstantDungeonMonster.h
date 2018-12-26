//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __INSTANT_DUNGEON_MONSTER_H__
#define __INSTANT_DUNGEON_MONSTER_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class InstantDungeonMonster
{
public:
	InstantDungeonMonster();
	~InstantDungeonMonster();

public:
	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	MonsterType_t getMonsterType() const { return m_MonsterType; }
	void setMonsterType( MonsterType_t MonsterType ) { m_MonsterType = MonsterType; }

	int getMonsterNumber() const { return m_Number; }
	void setMonsterNumber( int Number ) { m_Number = Number; }

	int getGroupID() const { return m_GroupID; }
	void setGroupID( int GroupID ) { m_GroupID = GroupID; }

	int getX() const { return m_X; }
	void setX( int X ) { m_X = X; }

	int getY() const { return m_Y; }
	void setY( int Y ) { m_Y = Y; }

	int IsBoss() const { return m_Boss; }
	void setBoss( int Boss ) { m_Boss = Boss; }

	string toString() const;

private:
	int					m_ID;
	MonsterType_t			m_MonsterType;	// Item Class
	int	m_Number;
	int	m_GroupID;
	int	m_X;
	int	m_Y;
	int	m_Boss;
};

//////////////////////////////////////////////////////////////////////////////
// Class InstantDungeonMonsterManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, InstantDungeonMonster*>			HashMapInstantDungeonMonster;
typedef HashMapInstantDungeonMonster::iterator			HashMapInstantDungeonMonsterItor;
typedef HashMapInstantDungeonMonster::const_iterator		HashMapInstantDungeonMonsterConstItor;

class InstantDungeonMonsterManager 
{
public:
	InstantDungeonMonsterManager();
	~InstantDungeonMonsterManager();

public:

	// void load() ;
	void load();
	
	// get InstantDungeonMonster
	InstantDungeonMonster* getInstantDungeonMonster(int id) const;

	// add InstantDungeonMonster
	void addInstantDungeonMonster(InstantDungeonMonster* pInstantDungeonMonster);

	int getGroupBoss(int ID, int Boss) const;
	int getCountSum(int Count) const;
	int getMinInt(int Count) const;
	int getMaxInt(int Count) const;
	int getTowerMinInt(int Count, int Statge) const;
	int getTowerEndStatge(int Count) const;
	list<WORD> getTowerMonsterList(int Count, int Statge);
	//const list<MonsterType_t>& getTowerMaxInt(int Count, int Statge) const;
	int getBossCount(int Counts) const;
	// toString for Debug
	string toString() const;

private:
	HashMapInstantDungeonMonster m_InstantDungeonMonsters;
};

// Global Variable Definition
extern InstantDungeonMonsterManager* g_pInstantDungeonMonsterManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
