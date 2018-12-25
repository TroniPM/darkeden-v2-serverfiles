//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ItemUtil.h"
#include "InstantDungeonMonster.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Monster.h"
#include "Treasure.h"
#include "Utility.h"

InstantDungeonMonster::InstantDungeonMonster() :m_ID(0)
{
	__BEGIN_TRY
	__END_CATCH
}

InstantDungeonMonster::~InstantDungeonMonster()
{
	__BEGIN_TRY
	__END_CATCH
}

/*Monster* InstantDungeonMonster::getMonster()
{
	__BEGIN_TRY

	Monster* pMonster = g_pItemFactoryManager->createItem( (Item::ItemClass)getItemClass(), getItemType() , getItemOptions() );

	return pItem;

	__END_CATCH
}
*/

string InstantDungeonMonster::toString() const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "InstantDungeonMonster("
		<< "m_ID : " << m_ID
		<< "m_MonsterType : " << m_MonsterType
		<< "m_Number : " << (int)m_Number
		<< "m_GroupID : " << m_GroupID
		<< ")";
	return msg.toString();

	__END_CATCH

}

InstantDungeonMonsterManager::InstantDungeonMonsterManager()
{
	__BEGIN_TRY
	__END_CATCH
}

InstantDungeonMonsterManager::~InstantDungeonMonsterManager()
{
	__BEGIN_TRY

	HashMapInstantDungeonMonsterItor itr = m_InstantDungeonMonsters.begin();
	HashMapInstantDungeonMonsterItor endItr = m_InstantDungeonMonsters.end();

	for (; itr != endItr ;itr++ )
	{
		InstantDungeonMonster* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	m_InstantDungeonMonsters.clear();

	__END_CATCH
}

void InstantDungeonMonsterManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT IndunID, MonsterType, MonsterNum, MonsterX, MonsterY, GroupID, Boss FROM InstantDungeonMonster");

	// 인던 아이디 및 몬스터 타입 및 몬?뵀?넘버
	// 그룹을 묶음

	while( pResult->next() )
	{
			uint i = 0;

			InstantDungeonMonster* pInstantDungeonMonster = new InstantDungeonMonster();
	// 인던 아이디
	pInstantDungeonMonster->setID( pResult->getInt(++i) );
	pInstantDungeonMonster->setMonsterType( pResult->getInt(++i) );
	pInstantDungeonMonster->setMonsterNumber( pResult->getInt(++i) );
	pInstantDungeonMonster->setX( pResult->getInt(++i) );
	pInstantDungeonMonster->setY( pResult->getInt(++i) );
	pInstantDungeonMonster->setGroupID( pResult->getInt(++i) );
	pInstantDungeonMonster->setBoss( pResult->getInt(++i) );
	addInstantDungeonMonster(pInstantDungeonMonster);	
	}

	}
	END_DB(pStmt)

	__END_CATCH
}

InstantDungeonMonster* InstantDungeonMonsterManager::getInstantDungeonMonster(int id) const
{
	__BEGIN_TRY

	HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.find(id);

	if ( itr == m_InstantDungeonMonsters.end() )
		return NULL;

	return itr->second;
	
	__END_CATCH
}

void InstantDungeonMonsterManager::addInstantDungeonMonster(InstantDungeonMonster* pInstantDungeonMonster) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	HashMapInstantDungeonMonsterItor itr = m_InstantDungeonMonsters.find(pInstantDungeonMonster->getID());

	if ( itr != m_InstantDungeonMonsters.end() )
		throw DuplicatedException();

	m_InstantDungeonMonsters[ pInstantDungeonMonster->getID() ] = pInstantDungeonMonster;

	__END_CATCH
}

int  InstantDungeonMonsterManager::getGroupBoss(int ID, int Boss) const 
{
	__BEGIN_TRY
	HashMapInstantDungeonMonsterConstItor endItr = m_InstantDungeonMonsters.end();
	//HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.find(ID);
	for (HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.begin() ; itr != endItr ; itr++ )
	{

		InstantDungeonMonster* pInstantDungeonMonster =  itr->second;

		if(pInstantDungeonMonster->getGroupID() == ID && pInstantDungeonMonster->IsBoss() == Boss){
			return pInstantDungeonMonster->getMonsterType();
		}

		if(pInstantDungeonMonster == NULL) break;
	}

	return 0;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getCountSum(int Count) const 
{
	__BEGIN_TRY
	Statement* pStmt = NULL;
	int Resut;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT Count(*) FROM InstantDungeonMonster where GroupID = %d", Count);
		pResult->next();
		Resut = pResult->getInt(1);
	}
	END_DB(pStmt)

	return Resut;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getMinInt(int Count) const 
{
	__BEGIN_TRY
	Statement* pStmt = NULL;
	int Resut;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT IndunID FROM InstantDungeonMonster where GroupID = %d order by IndunID ASC", Count);
		pResult->next();
		Resut = pResult->getInt(1);
	}
	END_DB(pStmt)

	return Resut;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getMaxInt(int Count) const 
{
	__BEGIN_TRY
	Statement* pStmt = NULL;
	int Resut;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT IndunID FROM InstantDungeonMonster where GroupID = %d order by IndunID DESC", Count);
		pResult->next();
		Resut = pResult->getInt(1);
	}
	END_DB(pStmt)

	return Resut;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getTowerMinInt(int Count, int Statge) const 
{
	__BEGIN_TRY

	HashMapInstantDungeonMonsterConstItor endItr = m_InstantDungeonMonsters.end();
	int CountStatge = 0;
	for (HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.begin() ; itr != endItr ; itr++ )
	{

		InstantDungeonMonster* pInstantDungeonMonster =  itr->second;

		if(pInstantDungeonMonster->getGroupID() == Count && pInstantDungeonMonster->IsBoss() == Statge){
		CountStatge++;
		}
	}

	return CountStatge;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getTowerEndStatge(int Count) const 
{
	__BEGIN_TRY

	HashMapInstantDungeonMonsterConstItor endItr = m_InstantDungeonMonsters.end();
	int CountStatge = 0;
	for (HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.begin() ; itr != endItr ; itr++ )
	{

		InstantDungeonMonster* pInstantDungeonMonster =  itr->second;

		if(pInstantDungeonMonster->getGroupID() == Count){
		CountStatge++;
		}
	}

	return CountStatge;
	__END_CATCH
}

list<WORD> InstantDungeonMonsterManager::getTowerMonsterList(int Count, int Statge) 
{
	__BEGIN_TRY
	list<WORD> m_MonsterType;
	m_MonsterType.clear();

	HashMapInstantDungeonMonsterConstItor endItr = m_InstantDungeonMonsters.end();
	for (HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.begin() ; itr != endItr ; itr++ )
	{

		InstantDungeonMonster* pInstantDungeonMonster =  itr->second;

		if(pInstantDungeonMonster->getGroupID() == Count && pInstantDungeonMonster->IsBoss() == Statge){
		m_MonsterType.push_back(pInstantDungeonMonster->getID());
		}
	}

	return m_MonsterType;
	__END_CATCH
}

int  InstantDungeonMonsterManager::getBossCount(int Counts) const 
{
	__BEGIN_TRY
	Statement* pStmt = NULL;
	int Resut;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT Count(*)  FROM InstantDungeonMonster where GroupID = %d and Boss = 1", Counts);
		pResult->next();
		Resut = pResult->getInt(1);
	}
	END_DB(pStmt)
	return Resut;
	__END_CATCH
}


string InstantDungeonMonsterManager::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	if ( m_InstantDungeonMonsters.empty() ) msg << "EMPTY";
	else
	{
		HashMapInstantDungeonMonsterConstItor endItr = m_InstantDungeonMonsters.end();
		for (HashMapInstantDungeonMonsterConstItor itr = m_InstantDungeonMonsters.begin() ; itr != endItr ; itr++ )
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

InstantDungeonMonsterManager* g_pInstantDungeonMonsterManager = NULL;
