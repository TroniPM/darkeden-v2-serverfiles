//////////////////////////////////////////////////////////////////////////////
// Filename    : Corpse.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Corpse.h"
#include "Zone.h"
#include "ItemFactory.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "RelicUtil.h"
#include <stdio.h>
//#include "EffectHasBloodBible.h"
#include "Gpackets/GCAddEffect.h"

// ItemUtil.h�� �̰� �ű�� ������ �ȴ�.
extern void saveItemInCorpse(Item* pItem, Corpse* pCorpse);

//////////////////////////////////////////////////////////////////////////////
// class Corpse member methods
//////////////////////////////////////////////////////////////////////////////

Corpse::Corpse()
	
{
	__BEGIN_TRY

	m_TreasureCount = 0;
	m_X = m_Y = 0;
	m_pZone = NULL;
	m_Level = 0;
	m_Exp = 0;

	__END_CATCH
}

Corpse::~Corpse()
	
{
	__BEGIN_TRY

	while (!m_Treasures.empty())
	{
		Item* pItem = m_Treasures.front();
		SAFE_DELETE(pItem);
		m_Treasures.pop_front();
	}

	__END_CATCH
}

Item* Corpse::getTreasure() 
	
{
	__BEGIN_TRY

	if (!m_Treasures.empty())
	{
		Item* pItem = m_Treasures.front();
		Assert(pItem!=NULL);

		// ���ܿ��� ������ ���������� ����Ʈ�� ���ش�.
		deleteFlagEffect( this, pItem );
		deleteRelicEffect( this, pItem );

		m_Treasures.pop_front();
		m_TreasureCount--;

		return pItem;
	}

	return NULL;

	__END_CATCH
}

void Corpse::addTreasure(Item* pItem)
	
{
	__BEGIN_TRY
	
	Assert(pItem != NULL);

	if (isRelicItem(pItem))
	{
		saveItemInCorpse(pItem, this);

		addHasRelicEffect(m_pZone, this, pItem);
	}
	else if ( pItem->isFlagItem() )
	{
		saveItemInCorpse(pItem, this);
	}
	else if ( pItem->getItemClass() == Item::ITEM_CLASS_SWEEPER )
	{
		saveItemInCorpse(pItem, this);

	}

	m_Treasures.push_back(pItem);
	m_TreasureCount++;

	__END_CATCH
}

Item* Corpse::getTreasure( ObjectID_t objectID ) const
	
{
	__BEGIN_TRY

	list<Item*>::const_iterator itr = m_Treasures.begin();

	for ( ; itr != m_Treasures.end() ; itr++ )
	{
		if ( (*itr)->getObjectID() == objectID ) return *itr;
	}

	return NULL;

	__END_CATCH
}


Item* Corpse::popTreasure( ObjectID_t objectID )
	
{
	__BEGIN_TRY

	list<Item*>::iterator itr = m_Treasures.begin();

	for ( ; itr != m_Treasures.end() ; itr++ )
	{
		if ( (*itr)->getObjectID() == objectID )
		{
			Item* pItem = *itr;
			m_Treasures.erase(itr);
			m_Treasures.push_front( pItem );
			return getTreasure();
		}
	}

	return NULL;

	__END_CATCH
}
