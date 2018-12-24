//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasCastleSymbol.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasCastleSymbol.h"
#include "ZoneUtil.h"
#include "Creature.h"
#include "Slayer.h"
#include "CastleSymbol.h"
#include "CastleInfoManager.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "WarSystem.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "GuildManager.h"
#include "StringPool.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>

const Effect::EffectClass EffectHasCastleSymbol::EffectClasses[6] =
{
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_2,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_3,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_4,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_5,
	Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL_6,
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasCastleSymbol::EffectHasCastleSymbol(Creature* pCreature)
	throw(Error)
: EffectHasRelic( pCreature )
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasCastleSymbol::EffectHasCastleSymbol(Item* pItem)
	throw(Error)
: EffectHasRelic( pItem )
{
	__BEGIN_TRY

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasCastleSymbol::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// �� ������ ��´�.
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
	Assert( pZoneInfo != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC!=NULL);
	
	// ��ġ�� �˸���.
/*	StringStream msg;
	msg << pCreature->getName() << " ��(" 
		//<< ( pCreature->isSlayer() ? "�����̾�" : "�����̾�" ) << ")�� " 
		<< g_pGuildManager->getGuildName( pPC->getGuildID() ) << ")�� "
	    << pZoneInfo->getFullName() << "(" << (int)pCreature->getX() << ", " << (int)pCreature->getY()
		<< ")���� ���� ��¡(" << m_PartName << ")�� ������ �ֽ��ϴ�.";
	*/

	char msg[300]; 
	sprintf( msg, g_pStringPool->c_str( STRID_BROADCAST_CASTLE_SYMBOL_POSITION ),
					pCreature->getName().c_str(), g_pGuildManager->getGuildName( pPC->getGuildID() ).c_str(),
					pZoneInfo->getFullName().c_str(), (int)pCreature->getX(), (int)pCreature->getY(),
					m_PartName.c_str() );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg);

	
	g_pCastleInfoManager->broadcastShrinePacket( m_Part , &gcSystemMessage );
/*
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_Part );
	
	const list<ZoneID_t>& ZoneIDList = pCastleInfo->getZoneIDList();
	list<ZoneID_t>::const_iterator itr = ZoneIDList.begin();

	for ( ; itr != ZoneIDList.end() ; itr++) 
	{
		Zone* pCastleZone = getZoneByZoneID( *itr );
		pCastleZone->broadcastPacket( &gcSystemMessage );
	}
*/
//	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	setNextTime(m_Tick);
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasCastleSymbol::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	if (m_pZone==NULL) return;

	// ���� ������ �������� ��츸 �޼����� �����ش�.
	ZoneID_t 	castleZoneID;
	bool		isCastle;

	isCastle = g_pCastleInfoManager->getCastleZoneID( m_pZone->getZoneID() , castleZoneID);

	if ( isCastle && g_pWarSystem->hasCastleActiveWar( castleZoneID ))
	{
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		// ��ġ�� �˸���.
/*		StringStream msg;
		msg << pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y
			<< ")�� ���ܿ� " << m_PartName << " ���� ��¡ �� �ֽ��ϴ�.";
*/

		char msg[200];
		sprintf( msg, g_pStringPool->c_str( STRID_BROADCAST_CASTLE_SYMBOL_POSITION_2 ),
						pZoneInfo->getFullName().c_str(), (int)m_X, (int)m_Y, m_PartName.c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);

		g_pCastleInfoManager->broadcastShrinePacket( m_Part , &gcSystemMessage );
/*
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_Part );
		
		const list<ZoneID_t>& ZoneIDList = pCastleInfo->getZoneIDList();
		list<ZoneID_t>::const_iterator itr = ZoneIDList.begin();

		for ( ; itr != ZoneIDList.end() ; itr++) 
		{
			Zone* pCastleZone = getZoneByZoneID( *itr );
			pCastleZone->broadcastPacket( &gcSystemMessage );
		}
*/
//		g_pZoneGroupManager->broadcast( &gcSystemMessage );

	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectHasCastleSymbol::setPart( int part )
	throw()
{
	__BEGIN_TRY

	const CastleSymbolInfo* pCastleSymbolInfo = dynamic_cast<const CastleSymbolInfo*>(g_pCastleSymbolInfoManager->getItemInfo( part ) );

	if ( pCastleSymbolInfo != NULL )
	{
		m_Part = part;
		m_PartName = pCastleSymbolInfo->getName();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasCastleSymbol::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasCastleSymbol("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
