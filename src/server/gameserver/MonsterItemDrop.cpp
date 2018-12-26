//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ItemUtil.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemFactoryManager.h"
#include "ItemGradeManager.h"
#include "ItemHeroOptionManager.h"
#include "DB.h"
#include "Treasure.h"
#include "Properties.h"
#include "Utility.h"
#include "OptionInfo.h"
#include "SXml.h"
#include <fstream>
#include <stdio.h>
#include <functional>
#include <algorithm>

MonsterItemDrop::MonsterItemDrop() :m_ID(0)
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterItemDrop::~MonsterItemDrop()
{
	__BEGIN_TRY
	__END_CATCH
}
void MonsterItemDrop::setSlayerTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);
	//SAFE_DELETE(m_pSlayerTreasureList);
	m_pSlayerTreasureList = pTreasureList;

	__END_CATCH
}
void MonsterItemDrop::parseSlayerTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY
	string newtext = trim(text);
	TreasureList* pSlayerTreasureList = new TreasureList;
	pSlayerTreasureList->parseString(newtext);
	setSlayerTreasureList(pSlayerTreasureList);

	__END_CATCH
}
void MonsterItemDrop::setVampireTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);
	//SAFE_DELETE(m_pSlayerTreasureList);
	m_pVampireTreasureList = pTreasureList;

	__END_CATCH
}
void MonsterItemDrop::parseVampireTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY
	string newtext = trim(text);
	TreasureList* pVampireTreasureList = new TreasureList;
	pVampireTreasureList->parseString(newtext);
	setVampireTreasureList(pVampireTreasureList);

	__END_CATCH
}
void MonsterItemDrop::setOustersTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);
	//SAFE_DELETE(m_pSlayerTreasureList);
	m_pOustersTreasureList = pTreasureList;

	__END_CATCH
}
void MonsterItemDrop::parseOustersTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY
	string newtext = trim(text);
	TreasureList* pOustersTreasureList = new TreasureList;
	pOustersTreasureList->parseString(newtext);
	setOustersTreasureList(pOustersTreasureList);

	__END_CATCH
}
/*
Item* MonsterItemDrop::getItem()
{
	__BEGIN_TRY
	// �̺κп��� ������ �ɼ� �׷��� �������� �ؾߵŴµ�...��..

	list<OptionType_t> oList; // �ɼ��� ��������.
	int MinOpcount = getMinOptionCount();
	int MaxOpcount = Random( getMinOptionCount()+1, getMaxOptionCount());
	Item* pItem = NULL;
	if(!isOptionItem()){
	while(MinOpcount <= MaxOpcount){
	
	int RandomDrop = Random(getItemOptionGroup(),getItemOptionGroup2());
	int OptionAdd = g_pMonsterItemDropOptionManager->getRandomItem( RandomDrop, getItemOptionGroup2(), oList );
	//cout << "�����ۿ� �ɼ� �ֱ� : (" << OptionAdd << ")" << endl;
	
	if(OptionAdd != 0 ){oList.push_back( OptionAdd  );}
	MinOpcount++;
	}

	//cout << " ������ Ŭ���� : " <<  (Item::ItemClass)getItemClass() <<  " ������ Ÿ�� : " << getItemType() <<endl;
	pItem = g_pItemFactoryManager->createItem( (Item::ItemClass)getItemClass(), getItemType() , oList );

	//cout << "�����ۿ� �ɼ� ���� / Ÿ�� / Ŭ����: (" << MinOpcount<< ")" << getItemType() << "/" << (Item::ItemClass)getItemClass() << endl;
	}else{
	pItem = g_pItemFactoryManager->createItem( (Item::ItemClass)getItemClass(), getItemType() , getItemOptions());

	//cout << "�����ۿ� �ɼ� ���� / Ÿ�� / Ŭ����: (" << MinOpcount<< ")" << getItemType() << "/" <<  (Item::ItemClass)getItemClass() << endl;
	}

	if((Item::ItemClass)getItemClass() != Item::ITEM_CLASS_EFFECT_ITEM && (Item::ItemClass)getItemClass() != Item::ITEM_CLASS_EVENT_STAR && getMinGrade() >= 1){ // �ּ� �޼� ���� 0�̻��̾�� ������ �����ϴ�.
	pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	pItem->setDurability( computeMaxDurability(pItem) );
	}
	if((Item::ItemClass)getItemClass() == Item::ITEM_CLASS_EFFECT_ITEM || (Item::ItemClass)getItemClass() == Item::ITEM_CLASS_EVENT_STAR && getMinGrade() >= 0)
	{
	int RandomInt = Random(getMinGrade(),getMaxGrade());
	pItem->setSilver(RandomInt);
	}
			///////////////////////////////////////////////////////////////////////////////////////////
			// ��Ʈ �ɼ��� ��������� ����. ����� �Ǿ������ Ȯ���� ���Ͽ� ����Ǿ�����.
			// �ɼ��� ������ 1������ �ִ� 3������ ����Ǿ�����, Ȯ���� ���Ͽ� ����Ǿ������� �����Ѵ�.
			// �ɼ� Ȯ���� �������� �����̸�, Ȯ���� ���Ͽ� ����Ǿ�����.
			// �ɼ��� ����Ǿ����� ������ �ɼǰ� ����� ������ �ɼ����� ����Ǿ�����.
			///////////////////////////////////////////////////////////////////////////////////////////
		list<OptionType_t> sList; // �ɼ��� ��������.
		// ��Ʈ �ɼ��� ������, Ȯ���� ���´�. �̶� Ȯ���� ���ؼ� �������� �Ǿ�����.
		// �ɼ��� �⺻ �ɼ��� ������ ������ŭ �����Ǿ�����.
		if(getItemSetOptionRatio() >= Random(1,100000)){
			int MinOpcount2 = getMinOptionCount();
			int MaxOpcount2 = Random( getMinOptionCount(), getMaxOptionCount());
				while(MinOpcount2 <= MaxOpcount2){
					int RandomDrop2 = Random(getItemOptionGroup(),getItemOptionGroup2());
					int OptionAdd2 = g_pMonsterItemDropOptionManager->getRandomItem( RandomDrop2, getItemOptionGroup2(), sList );	
					//cout << "�����ۿ� ��Ʈ �ɼ� �ֱ� : (" << OptionAdd2 << ")" << endl;
					if(OptionAdd2 != 0 ){
					sList.push_back( OptionAdd2  );
					}	
					MinOpcount2++;
				}
			pItem->setOptionType2(sList);
		}

		if(getItemHeroOptionRatio() >= Random(1,100000)){
			Attr_t Option = ItemHeroOptionManager::Instance().getRandomHeroOption();
			Attr_t Option_Attr = ItemHeroOptionManager::Instance().getRandomHeroOptionAttr(pItem->getHeroOption());
			if(Option_Attr > 15){Option_Attr = Random(1,6);

			pItem->setHeroOption(ItemHeroOptionManager::Instance().getRandomHeroOption());
			pItem->setHeroOptionAttr(Option_Attr);
		}else{
			pItem->setHeroOption(0);
			pItem->setHeroOptionAttr(0);
		}

	return pItem;
	__END_CATCH
}
*/
string MonsterItemDrop::toString() const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterItemDrop("
		<< "m_ID : " << m_ID
		<< ")";
	return msg.toString();

	__END_CATCH

}

MonsterItemDropManager::MonsterItemDropManager()
{
	__BEGIN_TRY
	__END_CATCH
}

MonsterItemDropManager::~MonsterItemDropManager()
{
	__BEGIN_TRY

	HashMapMonsterItemDropItor itr = m_MonsterItemDrops.begin();
	HashMapMonsterItemDropItor endItr = m_MonsterItemDrops.end();

	for (; itr != endItr ;itr++ )
	{
		MonsterItemDrop* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	
	m_MonsterItemDrops.clear();

	__END_CATCH
}

void MonsterItemDropManager::clear()
	throw()
{
	__BEGIN_TRY

	HashMapMonsterItemDropItor itr = m_MonsterItemDrops.begin();

	for ( ; itr != m_MonsterItemDrops.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_MonsterItemDrops.clear();
	
	__END_CATCH
}

void MonsterItemDropManager::load()
	
{
	__BEGIN_TRY

	clear();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT ID, SLAYERDROPSTRING, VAMPIREDROPSTRING, OUSTERSDROPSTRING, OPTIONCOUNT FROM MonsterItemDrop");
		//cout << " �ε� 1 " << endl;
		while( pResult->next() )
		{
			uint i = 0;
			MonsterItemDrop* pMonsterItemDrop = new MonsterItemDrop();
		//cout << " �ε� 1.1 " << endl;
			int 	id 			= pResult->getInt(++i);
			string 	dropstring	= pResult->getString(++i);
			string 	dropstring2	= pResult->getString(++i);
			string 	dropstring3	= pResult->getString(++i);
			int 	optioncount 			= pResult->getInt(++i);
			pMonsterItemDrop->setID( id );
		//cout << " �ε� 1.2 " << endl;
			pMonsterItemDrop->parseSlayerTreasureString( dropstring );
			pMonsterItemDrop->parseVampireTreasureString( dropstring2 );
			pMonsterItemDrop->parseOustersTreasureString( dropstring3 );
		//cout << " �ε� 1.3 " << endl;
			pMonsterItemDrop->setOptionCount( optioncount );
			addMonsterItemDrop(pMonsterItemDrop);	
		}
		//cout << " �ε� 2 " << endl;

	}
	END_DB(pStmt)

	__END_CATCH
}

MonsterItemDrop* MonsterItemDropManager::getMonsterItemDrop(int id) const
{
	__BEGIN_TRY

	HashMapMonsterItemDropConstItor itr = m_MonsterItemDrops.find(id);

	if ( itr == m_MonsterItemDrops.end() )
		return NULL;

	return itr->second;
	
	__END_CATCH
}

void MonsterItemDropManager::addMonsterItemDrop(MonsterItemDrop* pMonsterItemDrop) 
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	HashMapMonsterItemDropItor itr = m_MonsterItemDrops.find(pMonsterItemDrop->getID());

	if ( itr != m_MonsterItemDrops.end() )
		throw DuplicatedException();

	m_MonsterItemDrops[ pMonsterItemDrop->getID() ] = pMonsterItemDrop;

	__END_CATCH
}

string MonsterItemDropManager::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	if ( m_MonsterItemDrops.empty() ) msg << "EMPTY";
	else
	{
		HashMapMonsterItemDropConstItor endItr = m_MonsterItemDrops.end();
		for (HashMapMonsterItemDropConstItor itr = m_MonsterItemDrops.begin() ; itr != endItr ; itr++ )
		{
			msg << itr->second->toString();
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

MonsterItemDropManager* g_pMonsterItemDropManager = NULL;
