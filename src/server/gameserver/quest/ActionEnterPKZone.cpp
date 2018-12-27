////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterPKZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterPKZone.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZonePlayerManager.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "PCOustersInfo2.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "WeatherManager.h"
#include "PaySystem.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "LogClient.h"
#include "PacketUtil.h"
#include "ZoneUtil.h"
#include "Properties.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "StringPool.h"
#include "PKZoneInfoManager.h"
#include "GQuestManager.h"

#include <stdio.h>

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterPKZone::read (PropertyBuffer & pb)
    
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionEnterPKZone::execute (Creature * pNPC , Creature * pCreature) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	SYSTEM_RETURN_IF_NOT( SYSTEM_PK_ZONE );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert( pPC != NULL );

	bool bTransport = true;
#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_ZoneID );

		// �������ε� �������ڰ� �ƴϸ�...
		if (pZoneInfo==NULL
			|| pZoneInfo->isPayPlay() && !pGamePlayer->isPayPlaying())
		{
			string connectIP = pGamePlayer->getSocket()->getHost();

			// ���� ���� ����� �����Ѱ�?
			if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
			{
				sendPayInfo(pGamePlayer);
			}
			else
			{
				// ���� ���� ��� �Ұ��� ���
				GCSystemMessage gcSystemMessage;

				if (g_pConfig->getPropertyInt("IsNetMarble")==0)
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER_PAY_ZONE ) );
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
				}

				pGamePlayer->sendPacket (&gcSystemMessage);

				bTransport = false;

				return;
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if ( bTransport )
	{
		if ( pPC->isPLAYER() && !g_pPKZoneInfoManager->canEnterPKZone( m_ZoneID ) ) bTransport = false;
	}

	if (bTransport)
	{
		PKZoneInfo* pPKZoneInfo = g_pPKZoneInfoManager->getPKZoneInfo( m_ZoneID );

		if ( pPKZoneInfo == NULL )
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
			pGamePlayer->sendPacket (&gcSystemMessage);
		}

		// ��ڴ� �ο� ���� �� �ް� ����. -_-;
		if ( !pPC->isPLAYER() || pPKZoneInfo->enterZone() )
		{
			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert( pSlayer != NULL );

				// ������̸� Ÿ�� ������ ������̿��� ������.
				if ( pSlayer->hasRideMotorcycle() )
				{
					pSlayer->getOffMotorcycle();
				}
			}

			if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				Assert( pOusters != NULL );

				// ���� Ÿ�� ������ �����ش�
				if ( pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
				{
					Effect* pEffect = pOusters->findEffect(Effect::EFFECT_CLASS_SUMMON_SYLPH);
					if ( pEffect != NULL ) pEffect->setDeadline(0);
				}
			}

			if ( pNPC != NULL ) pPC->getGQuestManager()->illegalWarp();
			transportCreature(pCreature, m_ZoneID, pPKZoneInfo->getEnterX(), pPKZoneInfo->getEnterY(), true);
		}
		else
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_PKZONE_PC_LIMITED ) );
			pGamePlayer->sendPacket (&gcSystemMessage);
		}
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_PKZONE_PC_LIMITED ) );
		pGamePlayer->sendPacket (&gcSystemMessage);
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterPKZone::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterPKZone("
	    << "ZoneID:" << (int)m_ZoneID
	    << ")";
	return msg.toString();

	__END_CATCH
}

