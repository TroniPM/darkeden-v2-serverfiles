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
	// 이부분에서 아이템 옵션 그룹이 정해지게 해야돼는데...하..

	list<OptionType_t> oList; // 옵션이 정해진다.
	int MinOpcount = getMinOptionCount();
	int MaxOpcount = Random( getMinOptionCount()+1, getMaxOptionCount());
	Item* pItem = NULL;
	if(!isOptionItem()){
	while(MinOpcount <= MaxOpcount){
	
	int RandomDrop = Random(getItemOptionGroup(),getItemOptionGroup2());
	int OptionAdd = g_pMonsterItemDropOptionManager->getRandomItem( RandomDrop, getItemOptionGroup2(), oList );
	//cout << "아이템에 옵션 넣기 : (" << OptionAdd << ")" << endl;
	
	if(OptionAdd != 0 ){oList.push_back( OptionAdd  );}
	MinOpcount++;
	}

	//cout << " 아이템 클래스 : " <<  (Item::ItemClass)getItemClass() <<  " 아이템 타입 : " << getItemType() <<endl;
	pItem = g_pItemFactoryManager->createItem( (Item::ItemClass)getItemClass(), getItemType() , oList );

	//cout << "아이템에 옵션 갯수 / 타입 / 클래스: (" << MinOpcount<< ")" << getItemType() << "/" << (Item::ItemClass)getItemClass() << endl;
	}else{
	pItem = g_pItemFactoryManager->createItem( (Item::ItemClass)getItemClass(), getItemType() , getItemOptions());

	//cout << "아이템에 옵션 갯수 / 타입 / 클래스: (" << MinOpcount<< ")" << getItemType() << "/" <<  (Item::ItemClass)getItemClass() << endl;
	}

	if((Item::ItemClass)getItemClass() != Item::ITEM_CLASS_EFFECT_ITEM && (Item::ItemClass)getItemClass() != Item::ITEM_CLASS_EVENT_STAR && getMinGrade() >= 1){ // 최소 급수 값이 0이상이어야 실행이 가능하다.
	pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());
	pItem->setDurability( computeMaxDurability(pItem) );
	}
	if((Item::ItemClass)getItemClass() == Item::ITEM_CLASS_EFFECT_ITEM || (Item::ItemClass)getItemClass() == Item::ITEM_CLASS_EVENT_STAR && getMinGrade() >= 0)
	{
	int RandomInt = Random(getMinGrade(),getMaxGrade());
	pItem->setSilver(RandomInt);
	}
			///////////////////////////////////////////////////////////////////////////////////////////
			// 세트 옵션이 드랍되지는 여부. 드랍이 되어질경우 확률에 의하여 드랍되어진다.
			// 옵션의 개수는 1개부터 최대 3개까지 드랍되어지며, 확률에 의하여 드랍되어지도록 변경한다.
			// 옵션 확률은 전반적인 랜덤이며, 확률에 의하여 드랍되어진다.
			// 옵션은 드랍되어지는 아이템 옵션과 비슷한 아이템 옵션으로 드랍되어진다.
			///////////////////////////////////////////////////////////////////////////////////////////
		list<OptionType_t> sList; // 옵션이 정해진다.
		// 세트 옵션이 나오고, 확률이 나온다. 이때 확률에 의해서 정해지게 되어진다.
		// 옵션은 기본 옵션이 나오는 갯수만큼 설정되어진다.
		if(getItemSetOptionRatio() >= Random(1,100000)){
			int MinOpcount2 = getMinOptionCount();
			int MaxOpcount2 = Random( getMinOptionCount(), getMaxOptionCount());
				while(MinOpcount2 <= MaxOpcount2){
					int RandomDrop2 = Random(getItemOptionGroup(),getItemOptionGroup2());
					int OptionAdd2 = g_pMonsterItemDropOptionManager->getRandomItem( RandomDrop2, getItemOptionGroup2(), sList );	
					//cout << "아이템에 세트 옵션 넣기 : (" << OptionAdd2 << ")" << endl;
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
		//cout << " 로드 1 " << endl;
		while( pResult->next() )
		{
			uint i = 0;
			MonsterItemDrop* pMonsterItemDrop = new MonsterItemDrop();
		//cout << " 로드 1.1 " << endl;
			int 	id 			= pResult->getInt(++i);
			string 	dropstring	= pResult->getString(++i);
			string 	dropstring2	= pResult->getString(++i);
			string 	dropstring3	= pResult->getString(++i);
			int 	optioncount 			= pResult->getInt(++i);
			pMonsterItemDrop->setID( id );
		//cout << " 로드 1.2 " << endl;
			pMonsterItemDrop->parseSlayerTreasureString( dropstring );
			pMonsterItemDrop->parseVampireTreasureString( dropstring2 );
			pMonsterItemDrop->parseOustersTreasureString( dropstring3 );
		//cout << " 로드 1.3 " << endl;
			pMonsterItemDrop->setOptionCount( optioncount );
			addMonsterItemDrop(pMonsterItemDrop);	
		}
		//cout << " 로드 2 " << endl;

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
