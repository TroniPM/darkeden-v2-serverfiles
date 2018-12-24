////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.cpp
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterQuestZone.h"
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
#include "DynamicZoneAlterOfBlood.h"
#include "DynamicZonePartyOfDungeon.h"
#include "DynamicZoneGroup.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneInfo.h"
#include "GQuestManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterQuestZone::read (PropertyBuffer & pb)
    throw (Error)
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
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionEnterQuestZone::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
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

		// �������ε� �������ڰ� �ƴϸ�...
		if (pZoneInfo==NULL
			|| pZoneInfo->isPayPlay() && !(pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass()))
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
			}
		}
	} catch (NoSuchElementException&) {
	}
#endif

	if (bTransport)
	{
		// Dynamic ������ Ȯ��.
		int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( m_ZoneID );

		if ( targetDynamicZoneType != DYNAMIC_ZONE_MAX )
		{
			// Dynamic ���� ���
			DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
			Assert( pDynamicZoneGroup != NULL );

			DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
			Assert( pDynamicZone != NULL );

			transportCreature(pCreature, pDynamicZone->getZoneID(), m_X, m_Y, true);

			if ( targetDynamicZoneType == DYNAMIC_ZONE_ALTER_OF_BLOOD )
			{
				DynamicZoneAlterOfBlood* pAlterOfBlood = dynamic_cast<DynamicZoneAlterOfBlood*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setRace( pPC->getRace() );
			}
			if ( targetDynamicZoneType == DYNAMIC_ZONE_PARTY_OF_DUNGEON )
			{
				DynamicZonePartyOfDungeon* pAlterOfBlood = dynamic_cast<DynamicZonePartyOfDungeon*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setGroupID(1);
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				//pAlterOfBlood->setRace( pPC->getRace() );
			}
		}
		else
		{
			// Dynamic ���� �ƴ� ���
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
string ActionEnterQuestZone::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterQuestZone("
	    << "ZoneID:" << (int)m_ZoneID
	    << ",X:"  << (int)m_X
	    << ",Y:"  << (int)m_Y
	    << ")";
	return msg.toString();

	__END_CATCH
}

