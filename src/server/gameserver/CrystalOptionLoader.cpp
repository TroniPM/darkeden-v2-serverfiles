//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ItemUtil.h"
#include "CrystalOptionLoader.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Treasure.h"
#include "Utility.h"

CrystalOptionLoader::CrystalOptionLoader() :m_ID(0)
{
	__BEGIN_TRY
	__END_CATCH
}

CrystalOptionLoader::~CrystalOptionLoader()
{
	__BEGIN_TRY
	__END_CATCH
}

string CrystalOptionLoader::toString() const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CrystalOptionLoader("
		<< "m_ID : " << m_ID
		<< ")";
	return msg.toString();

	__END_CATCH

}

CrystalOptionLoaderManager::CrystalOptionLoaderManager()
{
	__BEGIN_TRY
	__END_CATCH
}

CrystalOptionLoaderManager::~CrystalOptionLoaderManager()
{
	__BEGIN_TRY

	HashMapCrystalOptionLoaderItor itr = m_CrystalOptionLoaders.begin();
	HashMapCrystalOptionLoaderItor endItr = m_CrystalOptionLoaders.end();

	for (; itr != endItr ;itr++ )
	{
		CrystalOptionLoader* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	m_CrystalOptionLoaders.clear();

	__END_CATCH
}

void CrystalOptionLoaderManager::load()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
							"SELECT OptionID, OptionType, OptionRatio FROM CrystalOptionLoader");
		
		while( pResult->next() )
		{
			uint i = 0;

			CrystalOptionLoader* pCrystalOptionLoader = new CrystalOptionLoader();

			int 	id 			= pResult->getInt(++i);
			int 	itemOptions = pResult->getInt(++i);
			int 	itemOptionsRatio = pResult->getInt(++i);
			pCrystalOptionLoader->setID( id );
			pCrystalOptionLoader->setItemOptions( itemOptions );
			pCrystalOptionLoader->setItemOptionRatio(itemOptionsRatio);

			addCrystalOptionLoader(pCrystalOptionLoader);	
		}

	}
	END_DB(pStmt)

	__END_CATCH
}

CrystalOptionLoader* CrystalOptionLoaderManager::getCrystalOptionLoader(int id) const
{
	__BEGIN_TRY

	HashMapCrystalOptionLoaderConstItor itr = m_CrystalOptionLoaders.find(id);

	if ( itr == m_CrystalOptionLoaders.end() )
		return NULL;

	return itr->second;
	
	__END_CATCH
}

void CrystalOptionLoaderManager::addCrystalOptionLoader(CrystalOptionLoader* pCrystalOptionLoader) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	HashMapCrystalOptionLoaderItor itr = m_CrystalOptionLoaders.find(pCrystalOptionLoader->getID());

	if ( itr != m_CrystalOptionLoaders.end() )
		throw DuplicatedException();

	m_CrystalOptionLoaders[ pCrystalOptionLoader->getID() ] = pCrystalOptionLoader;

	__END_CATCH
}

string CrystalOptionLoaderManager::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	if ( m_CrystalOptionLoaders.empty() ) msg << "EMPTY";
	else
	{
		HashMapCrystalOptionLoaderConstItor endItr = m_CrystalOptionLoaders.end();
		for (HashMapCrystalOptionLoaderConstItor itr = m_CrystalOptionLoaders.begin() ; itr != endItr ; itr++ )
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

int CrystalOptionLoaderManager::getRandomItem(int minID, int maxID)
{
	__BEGIN_TRY

	// 최소값을 저장한다.
	int minnum = minID;
	int randomX = Random(minID,maxID);
	do{
	CrystalOptionLoader* pCrystalOptionLoader = getCrystalOptionLoader( randomX );

	int Randoms = rand()%100000;

	if(pCrystalOptionLoader->getItemOptionRatio() >= Randoms ){

	cout << "아이템의 옵션 넣기 성공 : 확률(" << pCrystalOptionLoader->getItemOptionRatio() << " / " << Randoms << endl;

	return (int)pCrystalOptionLoader->getItemOptions();

	}

	cout << "아이템의 옵션 넣기 실패 : 확률(" << pCrystalOptionLoader->getItemOptionRatio() << " / " << Randoms << endl;

	minID++;

	// 옵션이 뜨지않았다. 그럴경우 최소값을 다시 초기화 시킨후 다시 계속 루프를 돌려 옵션이 들때까지 돌린다.
	if(minID == maxID){minID = minnum;}

	}while(minID <= maxID); // 맥스치만큼 루프를 돌린다.

	__END_CATCH
}

CrystalOptionLoaderManager* g_pCrystalOptionLoaderManager = NULL;
