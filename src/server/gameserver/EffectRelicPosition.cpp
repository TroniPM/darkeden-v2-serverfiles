//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicPosition.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRelicPosition.h"
#include "ZoneUtil.h"
#include "ZoneGroupManager.h"
#include "HolyLandManager.h"
#include "ShrineInfoManager.h"
#include "StringStream.h"
#include "Relic.h"
#include "ZoneInfoManager.h"
#include "CastleInfoManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCBloodBibleStatus.h"
#include "StringPool.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRelicPosition::EffectRelicPosition(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicPosition::affect()
	throw(Error)
{
	__BEGIN_TRY

	Item* pItem = dynamic_cast<Item*>(m_pTarget);
	affect( pItem );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicPosition::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	// �� ������ ��´�.
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_ZoneID );
	Assert( pZoneInfo != NULL );

	if (pItem->getItemClass() == Item::ITEM_CLASS_RELIC)
	{
		// ������ ������ ��´�.
		ItemType_t relicIndex = pItem->getItemType();
		const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));
		Assert( pRelicInfo != NULL );

//		StringStream msg;

/*		// ��ġ�� �˸���.
		msg << "����(" << pRelicInfo->getName() << ")�� "
			<< pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y << ")�� ������ �ֽ��ϴ�."; */

		char msg[100];

		sprintf( msg, g_pStringPool->c_str( STRID_RELIC_IN_ZONE ),
						pRelicInfo->getName().c_str(),
						pZoneInfo->getFullName().c_str(),
						(int)m_X,
						(int)m_Y
		);

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType( SYSTEM_MESSAGE_COMBAT );
		gcSystemMessage.setMessage( msg );

		g_pHolyLandManager->broadcast( &gcSystemMessage );

		setNextTime(m_Tick);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		ShrineSet* pShrineSet = g_pShrineInfoManager->getShrineSet( m_Part );
		Assert(pShrineSet!=NULL);

		GCBloodBibleStatus* pGCBBS = new GCBloodBibleStatus;
		pGCBBS->setItemType( m_Part );
		pGCBBS->setZoneID( m_ZoneID );
		pGCBBS->setStorage( STORAGE_ZONE );
		//pGCBBS->setRace( pShrineSet->getOwnerRace() );
		pGCBBS->setShrineRace( pShrineSet->getOwnerRace() );
		pGCBBS->setX( m_X );
		pGCBBS->setY( m_Y );

//		g_pHolyLandManager->broadcast( pGCBBS );
		g_pZoneGroupManager->broadcast( pGCBBS );
		g_pShrineInfoManager->registerBloodBibleStatus( m_Part, pGCBBS );
		/*
		msg << "���� ���� ������ "
			<< pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y << ")�� ������ �ֽ��ϴ�.";

		g_pZoneGroupManager->broadcast( &gcSystemMessage );
		*/

		setNextTime(999999);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
//		StringStream msg;

//		msg << "���� ��¡�� "
//			<< pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y << ")�� ������ �ֽ��ϴ�.";

		char msg[200];
		sprintf( msg, g_pStringPool->c_str( STRID_BROADCAST_CASTLE_SYMBOL_POSITION_3 ),
						pZoneInfo->getFullName().c_str(), (int)m_X, (int)m_Y );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType( SYSTEM_MESSAGE_HOLY_LAND );
		gcSystemMessage.setMessage( msg );

		g_pCastleInfoManager->broadcastShrinePacket( m_Part, &gcSystemMessage );

		setNextTime(m_Tick);
//		g_pZoneGroupManager->broadcast( &gcSystemMessage );
	}
	else
	{
		return;
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicPosition::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	
	
	Item* pItem = dynamic_cast<Item *>(m_pTarget);
	unaffect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicPosition::unaffect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	pItem->removeFlag( Effect::EFFECT_CLASS_RELIC_POSITION );

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRelicPosition::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRelicPosition("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
