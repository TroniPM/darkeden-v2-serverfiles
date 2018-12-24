#include "PetAttrInfo.h"
#include "DB.h"
#include "PetInfo.h"

void PetAttrInfoManager::clear()
{
	hash_map<PetAttr_t, PetAttrInfo*>::iterator itr = m_PetAttrInfoMap.begin();
	hash_map<PetAttr_t, PetAttrInfo*>::iterator endItr = m_PetAttrInfoMap.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( itr->second );
	}

	m_PetAttrInfoMap.clear();
}

void PetAttrInfoManager::load()
{
	Statement *pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT PetAttr, Level, AddAttr, AccumAttr FROM PetAttrBalanceInfo" );

		while ( pResult->next() )
		{
			PetAttr_t PetAttr = pResult->getInt(1);

			if ( m_PetAttrInfoMap[PetAttr] == NULL ) m_PetAttrInfoMap[PetAttr] = new PetAttrInfo(PetAttr);
			PetLevel_t PetLevel = pResult->getInt(2);

			m_PetAttrInfoMap[PetAttr]->setPetAttrLevel( PetLevel, (PetAttrLevel_t)pResult->getInt(4) );
		}

		pResult = pStmt->executeQuery( "SELECT PetAttr, EnchantRatio FROM PetAttrInfo" );
		
		while ( pResult->next() )
		{
			PetAttr_t PetAttr = pResult->getInt(1);
			if ( m_PetAttrInfoMap[PetAttr] != NULL ) m_PetAttrInfoMap[PetAttr]->setEnchantRatio( pResult->getInt(2) );
			else cout << "PetAttrInfo�� �ִ� PetAttr�� �������� �ʴ� �Ӽ��Դϴ�." << endl;
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )
}

bool PetAttrInfoManager::enchantRandomAttr( PetInfo* pPetInfo, int ratio )
{
	int value = rand()%100;

	cout << "ratio : " << ratio << endl;
	cout << "value : " << value << endl;

	hash_map<PetAttr_t, PetAttrInfo*>::iterator itr = m_PetAttrInfoMap.begin();
	hash_map<PetAttr_t, PetAttrInfo*>::iterator endItr = m_PetAttrInfoMap.end();

	if ( pPetInfo->getPetLevel() < 10 ) return false;
	if ( value < ratio ) return false;

	value = rand()%100;

	cout << "�ɼǼ��� : " << value << endl;

	for ( ; itr != endItr ; ++itr )
	{
		PetAttrInfo* pPetAttrInfo = itr->second;

		if ( pPetAttrInfo == NULL ) continue;

		cout << (int)pPetAttrInfo->getPetAttr() << " : " << pPetAttrInfo->getEnchantRatio() << endl;

		if ( pPetAttrInfo->getEnchantRatio() > value )
		{
			cout << "selected" << endl;

			pPetInfo->setPetAttr( pPetAttrInfo->getPetAttr() );
			pPetInfo->setPetAttrLevel( pPetAttrInfo->getPetAttrLevel( pPetInfo->getPetLevel() ) );
			return true;
		}

		value -= pPetAttrInfo->getEnchantRatio();
	}

	return false;
}

bool PetAttrInfoManager::enchantSpecAttr( PetInfo* pPetInfo, PetAttr_t PetAttr )
{
	int value = rand()%100;
	if ( value > 70 ) return false;

	PetAttrInfo* pPetAttrInfo = m_PetAttrInfoMap[PetAttr];
	if ( pPetAttrInfo == NULL )
	{
		filelog("PetBug.log", "�Ӽ� ���� �� ��æƮ���� �̻��� ���� ����ִ�. : %u", PetAttr );
		return false;
	}

	pPetInfo->setPetAttr( pPetAttrInfo->getPetAttr() );
	pPetInfo->setPetAttrLevel( pPetAttrInfo->getPetAttrLevel( pPetInfo->getPetLevel() ) );

	return true;
}

bool PetAttrInfoManager::enchantClearAttr( PetInfo* pPetInfo )
{
	/*int value = rand()%100;
	if ( value > 70 ) return false;

	PetAttrInfo* pPetAttrInfo = m_PetAttrInfoMap[PetAttr];
	if ( pPetAttrInfo == NULL )
	{
		filelog("PetBug.log", "�Ӽ� ���� �� ��æƮ���� �̻��� ���� ����ִ�. : %u", PetAttr );
		return false;
	}*/

	pPetInfo->setPetAttr( 255 );
	pPetInfo->setPetAttrLevel( 0 );

	return true;
}

PetAttrInfo* PetAttrInfoManager::getPetAttrInfo( PetAttr_t PetAttr ) const
{
	hash_map<PetAttr_t,PetAttrInfo*>::const_iterator itr = m_PetAttrInfoMap.find(PetAttr);

	if ( itr == m_PetAttrInfoMap.end() ) return NULL;

	return itr->second;
}

