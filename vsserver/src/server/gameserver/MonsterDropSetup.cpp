//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ItemUtil.h"
#include "MonsterDropSetup.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Treasure.h"
#include "Utility.h"

MonsterDropSetup::MonsterDropSetup() :m_ID(0)
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterDropSetup::~MonsterDropSetup()
{
	__BEGIN_TRY
	__END_CATCH
}

string MonsterDropSetup::toString() const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterDropSetup("
		<< "m_ID : " << m_ID
		<< "m_SlayerRandomDrop1 : " << m_SlayerRandomDrop1
		<< "m_RandomDropNum: " << m_RandomDropNum
		<< ")";
	return msg.toString();

	__END_CATCH

}

MonsterDropSetupManager::MonsterDropSetupManager()
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterDropSetupManager::~MonsterDropSetupManager()
{
	__BEGIN_TRY

	HashMapMonsterDropSetupItor itr = m_MonsterDropSetups.begin();
	HashMapMonsterDropSetupItor endItr = m_MonsterDropSetups.end();

	for (; itr != endItr ;itr++ )
	{
		MonsterDropSetup* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	m_MonsterDropSetups.clear();

	__END_CATCH
}

void MonsterDropSetupManager::clear()
	throw()
{
	__BEGIN_TRY

	HashMapMonsterDropSetupItor itr = m_MonsterDropSetups.begin();

	for ( ; itr != m_MonsterDropSetups.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_MonsterDropSetups.clear();
	
	__END_CATCH
}

void MonsterDropSetupManager::load()
	throw(Error)
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
							"SELECT MonsterType, isSetup, ItemDrop, DropBounsRatio, ItemDropNum, ItemSetOptionSetup, ItemSetOptionRatio, ItemSetHeroOptionSetup, ItemSetHeroOptionRatio, RareBounsRatio, isInventory, InventorySetup, InventorySetupNum, InventoryXY, IsGold,SetGold FROM MonsterDropSetup");
		
		while( pResult->next() )
		{
			uint i = 0;

			MonsterDropSetup* pMonsterDropSetup = new MonsterDropSetup();

			pMonsterDropSetup->setID(pResult->getInt(++i));
			pMonsterDropSetup->setDrop(pResult->getInt(++i));
			pMonsterDropSetup->setSlayerRandomDrop1(pResult->getInt(++i));
			pMonsterDropSetup->setItemDropBounsRatio(pResult->getInt(++i));
			pMonsterDropSetup->setRandomDropNum(pResult->getInt(++i));
			pMonsterDropSetup->setItemSetOptionSetup(pResult->getInt(++i));
			pMonsterDropSetup->setItemSetOptionRatio(pResult->getInt(++i));
			pMonsterDropSetup->setItemSetHeroOptionSetup(pResult->getInt(++i));
			pMonsterDropSetup->setItemSetHeroOptionRatio(pResult->getInt(++i));
			pMonsterDropSetup->setItemRareOptionBounsRatio(pResult->getInt(++i));
			pMonsterDropSetup->setInventory(pResult->getInt(++i));
			pMonsterDropSetup->setInventorySetup1(pResult->getInt(++i));
			pMonsterDropSetup->setInventoryNum(pResult->getInt(++i));
			pMonsterDropSetup->setInventoryXY(pResult->getInt(++i));
			pMonsterDropSetup->setGold(pResult->getInt(++i));
			pMonsterDropSetup->setGetGold(pResult->getInt(++i));
			addMonsterDropSetup(pMonsterDropSetup);	
		}

	}
	END_DB(pStmt)

	__END_CATCH
}

MonsterDropSetup* MonsterDropSetupManager::getMonsterDropSetup(int id) const
{
	__BEGIN_TRY

	HashMapMonsterDropSetupConstItor itr = m_MonsterDropSetups.find(id);

	if ( itr == m_MonsterDropSetups.end() )
		return NULL;

	return itr->second;
	
	__END_CATCH
}

void MonsterDropSetupManager::addMonsterDropSetup(MonsterDropSetup* pMonsterDropSetup) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	HashMapMonsterDropSetupItor itr = m_MonsterDropSetups.find(pMonsterDropSetup->getID());

	if ( itr != m_MonsterDropSetups.end() )
		throw DuplicatedException();

	m_MonsterDropSetups[ pMonsterDropSetup->getID() ] = pMonsterDropSetup;

	__END_CATCH
}

string MonsterDropSetupManager::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	if ( m_MonsterDropSetups.empty() ) msg << "EMPTY";
	else
	{
		HashMapMonsterDropSetupConstItor endItr = m_MonsterDropSetups.end();
		for (HashMapMonsterDropSetupConstItor itr = m_MonsterDropSetups.begin() ; itr != endItr ; itr++ )
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

MonsterDropSetupManager* g_pMonsterDropSetupManager = NULL;
