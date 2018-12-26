////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.cpp
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterInstantExit.h"
#include "Properties.h"
#include "StringPool.h"
#include "Zone.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZoneUtil.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "PacketUtil.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "DynamicZonePartyOfDungeon.h"
#include "DynamicZoneGroup.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneInfo.h"
#include "GQuestManager.h"

#include "Party.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterInstantExit::read (PropertyBuffer & pb)
    
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
		m_X      = pb.getPropertyInt("X");
		m_Y      = pb.getPropertyInt("Y");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionEnterInstantExit::execute (Creature * pNPC , Creature * pCreature) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Assert( pPC != NULL );

	bool bTransport = true;
#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	try {

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_ZoneID );

		// 유료존인데 유료사용자가 아니면...
		if (pZoneInfo==NULL
			|| pZoneInfo->isPayPlay() && !(pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass()))
		{
			string connectIP = pGamePlayer->getSocket()->getHost();

			// 유료 서비스 사용이 가능한가?
			if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
			{
				sendPayInfo(pGamePlayer);
			}
			else
			{
				// 유료 서비스 사용 불가인 경우
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
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if (bTransport)
	{
		// Dynamic 존인지 확인.
		int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( pCreature->getZoneID() );

		if ( targetDynamicZoneType != DYNAMIC_ZONE_MAX )
		{
			// Dynamic 존일 경우
			DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
			Assert( pDynamicZoneGroup != NULL );

			DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
			Assert( pDynamicZone != NULL );

			if ( targetDynamicZoneType == DYNAMIC_ZONE_PARTY_OF_DUNGEON )
			{
				DynamicZonePartyOfDungeon* pAlterOfBlood = dynamic_cast<DynamicZonePartyOfDungeon*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				transportCreature(pCreature, pAlterOfBlood->getZoneID(), m_X, m_Y, true);
			}
		}
		else
		{
			// Dynamic 존이 아닐 경우
			transportCreature( pCreature, m_ZoneID, m_X, m_Y, true );
		}
	}
	else
	{
	    GCNPCResponse response;
	    response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	    pGamePlayer->sendPacket(&response);
	}

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionEnterInstantExit::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterInstantExit("
	    << "ZoneID:" << (int)m_ZoneID
	    << ",X:"  << (int)m_X
	    << ",Y:"  << (int)m_Y
	    << ")";
	return msg.toString();

	__END_CATCH
}

