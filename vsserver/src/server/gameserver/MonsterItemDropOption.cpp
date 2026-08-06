//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ItemUtil.h"
#include "MonsterItemDropOption.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Treasure.h"
#include "Utility.h"
#include "OptionInfo.h"
MonsterItemDropOption::MonsterItemDropOption() :m_ID(0)
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterItemDropOption::~MonsterItemDropOption()
{
	__BEGIN_TRY
	__END_CATCH
}

string MonsterItemDropOption::toString() const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterItemDropOption("
		<< "m_ID : " << m_ID
		<< ")";
	return msg.toString();

	__END_CATCH

}

MonsterItemDropOptionManager::MonsterItemDropOptionManager()
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterItemDropOptionManager::~MonsterItemDropOptionManager()
{
	__BEGIN_TRY

	HashMapMonsterItemDropOptionItor itr = m_MonsterItemDropOptions.begin();
	HashMapMonsterItemDropOptionItor endItr = m_MonsterItemDropOptions.end();

	for (; itr != endItr ;itr++ )
	{
		MonsterItemDropOption* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	m_MonsterItemDropOptions.clear();

	__END_CATCH
}

void MonsterItemDropOptionManager::clear()
	throw()
{
	__BEGIN_TRY

	HashMapMonsterItemDropOptionItor itr = m_MonsterItemDropOptions.begin();

	for ( ; itr != m_MonsterItemDropOptions.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_MonsterItemDropOptions.clear();
	
	__END_CATCH
}

void MonsterItemDropOptionManager::load()
	throw(Error)
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
							"SELECT ID, OptionClassType, OptionPlusPoint, OptionRatio, OptionGroup FROM MonsterItemDropOption");
		
		while( pResult->next() )
		{
			uint i = 0;

			MonsterItemDropOption* pMonsterItemDropOption = new MonsterItemDropOption();

			pMonsterItemDropOption->setID( pResult->getInt(++i) );
			pMonsterItemDropOption->setOptionsClassType( pResult->getInt(++i) );
			pMonsterItemDropOption->setOptionPlusPoint( pResult->getInt(++i) );
			pMonsterItemDropOption->setOptionRatio(pResult->getInt(++i));
			pMonsterItemDropOption->setOptionGroup(pResult->getInt(++i));

			addMonsterItemDropOption(pMonsterItemDropOption);	
		}

	}
	END_DB(pStmt)

	__END_CATCH
}

MonsterItemDropOption* MonsterItemDropOptionManager::getMonsterItemDropOption(int id) const
{
	__BEGIN_TRY

	HashMapMonsterItemDropOptionConstItor itr = m_MonsterItemDropOptions.find(id);

	if ( itr == m_MonsterItemDropOptions.end() )
		return NULL;

	return itr->second;
	
	__END_CATCH
}

void MonsterItemDropOptionManager::addMonsterItemDropOption(MonsterItemDropOption* pMonsterItemDropOption) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	HashMapMonsterItemDropOptionItor itr = m_MonsterItemDropOptions.find(pMonsterItemDropOption->getID());

	if ( itr != m_MonsterItemDropOptions.end() )
		throw DuplicatedException();

	m_MonsterItemDropOptions[ pMonsterItemDropOption->getID() ] = pMonsterItemDropOption;

	__END_CATCH
}

string MonsterItemDropOptionManager::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	if ( m_MonsterItemDropOptions.empty() ) msg << "EMPTY";
	else
	{
		HashMapMonsterItemDropOptionConstItor endItr = m_MonsterItemDropOptions.end();
		for (HashMapMonsterItemDropOptionConstItor itr = m_MonsterItemDropOptions.begin() ; itr != endItr ; itr++ )
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

int MonsterItemDropOptionManager::getRandomItem(int OptionType)
{
	__BEGIN_TRY
	HashMapMonsterItemDropOptionConstItor endItr = m_MonsterItemDropOptions.end();
	int OptionClassPlus = 0 ;
	for (HashMapMonsterItemDropOptionConstItor itr = m_MonsterItemDropOptions.begin() ; itr != endItr ; itr++ )
	{

		MonsterItemDropOption* pMonsterItemDropOption = itr->second;

		if(pMonsterItemDropOption == NULL) break;
		
		// 동일한 옵션 그룹일 경우에만 작동 된다.
		if(pMonsterItemDropOption->getOptionGroup() == OptionType){
			// 옵션 루팅값이 랜덤값보다 높을 경우 리턴한다.
			if(pMonsterItemDropOption->getOptionRatio() > rand()%100000){
				return pMonsterItemDropOption->getOptionPlusPoint();
			}
		}
	OptionClassPlus++;
	}

	// .. 다 뒤적였으나 옵션값을 못받았다.
	return 0;

	__END_CATCH
}

int MonsterItemDropOptionManager::getRandomOption(int OptionType)
{
	__BEGIN_TRY
	HashMapMonsterItemDropOptionConstItor endItr = m_MonsterItemDropOptions.end();
	int OptionClass = 0 ;
	for (HashMapMonsterItemDropOptionConstItor itr = m_MonsterItemDropOptions.begin() ; itr != endItr ; itr++ )
	{

		MonsterItemDropOption* pMonsterItemDropOption =  itr->second;

		if(pMonsterItemDropOption == NULL) break;
		
		// 동일한 옵션 그룹일 경우에만 작동 된다.
		if(pMonsterItemDropOption->getOptionGroup() == OptionType){
			return pMonsterItemDropOption->getOptionClassType();
		}
	OptionClass++;
	}

	// .. 다 뒤적였으나 옵션값을 못받았다.
	return 0;

	__END_CATCH
}

MonsterItemDropOptionManager* g_pMonsterItemDropOptionManager = NULL;
