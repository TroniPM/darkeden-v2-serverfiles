//////////////////////////////////////////////////////////////////////////////
// Filename    : Item.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Item.h"
#include "DB.h"
#include "ItemInfoManager.h"
#include "Assert.h"

#include "PCItemInfo.h"
#include "PlayerCreature.h"
#include "Store.h"

#include "Cpackets/CGRequestStoreInfo.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
// class Item member methods
//////////////////////////////////////////////////////////////////////////////

Item::Item()
	throw()
{
	m_ItemID = 0;
	m_CreateType = CREATE_TYPE_NORMAL;
	m_bUnique = false;
	m_bQuest = false;
	m_bTrace = false;
	m_bTimeLimit = false;
	m_bOnStore = false;
	m_pStore = NULL;
}

Item::~Item()
	throw()
{
}

bool Item::destroy() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM %s WHERE ItemID = %lu", getObjectTableName().c_str(), m_ItemID);

		// DB���� ����°ǵ�..
		// DB�� �̹� �������� ���� ���
		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return true;

	__END_CATCH
}

// �������� ������. �⺻�� ��������, Ư���� ��쿣 Timeover �� �׿� �� ���� storage��..
void Item::waste( Storage storage ) const
	throw(Error)
{
	Assert( (uint)storage >= (uint)STORAGE_GARBAGE );

	char query[50];

	sprintf( query, "Storage = %u", (uint)storage );

	tinysave( query );
}

const list<OptionType_t>& Item::getDefaultOptions(void) const 
	throw()
{
	__BEGIN_TRY

	try {

		return g_pItemInfoManager->getItemInfo(getItemClass(), getItemType())->getDefaultOptions();

	} catch (NoSuchElementException&){
		StringStream msg;
		msg << "�׷� ������ ������ �����ϴ�.(" << (int)getItemClass() << ", " << (int)getItemType() << ")";

		filelog("itemError.txt", "%s", msg.toString().c_str());
		//throw Error(msg.toString());
	}

	static list<OptionType_t> optionTypes;
	return optionTypes;

	__END_CATCH
}

bool Item::isQuestItem() const
{
	return (getItemClass() == ITEM_CLASS_EVENT_ITEM && getItemType() < 27 ) ||//(!= 27 && getItemType() != 28) || 
		(getItemClass()==ITEM_CLASS_EVENT_TREE && getItemType()>12 && getItemType()<26) ||
		(getItemClass()==ITEM_CLASS_EVENT_TREE && getItemType()>28 && getItemType()<42) ||
		(getItemClass()==ITEM_CLASS_CODE_SHEET);
}

void Item::makePCItemInfo(PCItemInfo& result) const
{
	if ( m_ObjectID == 0 )
	{
		filelog("ItemError.log", "������ oid�� 0�Դϴ�. : %s", toString().c_str());
		result.setObjectID(0);
	}
	else
	{
		result.setObjectID(getObjectID());
	}

	result.setItemClass(getItemClass());
	result.setItemType(getItemType());
	result.setOptionType(getOptionTypeList());
	result.setOptionType2(getOptionTypeList2());
	result.setSilver(getSilver());
	result.setDurability(getDurability());
	result.setEnchantLevel(getEnchantLevel());
	result.setHeroOption(getHeroOption());
	result.setHeroOptionAttr(getHeroOptionAttr());
	result.setItemNum(getNum());
	result.setMainColor(0);
	result.setGrade(getGrade());
}

void Item::whenPCTake( PlayerCreature* pPC )
{
//	cout << pPC->getName() << " Take " << toString() << endl; 
}

void Item::whenPCLost( PlayerCreature* pPC )
{
//	cout << pPC->getName() << " Lost " << toString() << endl; 
	Store* pStore = pPC->getStore();
	BYTE index = pStore->getItemIndex(this);

	if ( index != 0xff )
	{
		pStore->removeStoreItem( index );

		CGRequestStoreInfo cgInfo;
		cgInfo.setOwnerObjectID(0);
		cgInfo.execute( pPC->getPlayer() );
	}
}
