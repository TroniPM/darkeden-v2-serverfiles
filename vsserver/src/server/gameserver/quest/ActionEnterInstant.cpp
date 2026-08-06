////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.cpp
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionEnterInstant.h"
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
#include "DynamicZonePartyOfDungeon2.h"
#include "DynamicZonePartyOfDungeon3.h"
#include "DynamicZonePartyOfDungeon4.h"
#include "DynamicZoneMiniGame.h"
#include "DynamicZoneAsylion.h"
#include "DynamicZoneTimeOfDungeon.h"
#include "DynamicZoneMenegroth1.h"
#include "DynamicZoneCastleOfDefense.h"
#include "DynamicZoneBossRoom.h"
#include "DynamicZoneBossRoom2.h"
#include "DynamicZoneGroup.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneInfo.h"
#include "GQuestManager.h"
#include "EffectSimyunEnterLoop.h"
#include "Party.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

#include "DynamicZoneTiffagues_1.h"
#include "DynamicZoneTiffagues_2_1.h"
#include "DynamicZoneTiffagues_2_2.h"
#include "DynamicZoneHilanom.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionEnterInstant::read (PropertyBuffer & pb)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_ZoneID = pb.getPropertyInt("ZoneID");
		m_X      = pb.getPropertyInt("X");
		m_Y      = pb.getPropertyInt("Y");
		m_InstantID      = pb.getPropertyInt("InstantID");
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
void ActionEnterInstant::execute (Creature * pNPC , Creature * pCreature) 
	throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );
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
		bool teleportok = true;
		// Dynamic 존인지 확인.
		int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( m_ZoneID );

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
				pAlterOfBlood->setGroupID(m_InstantID);
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_PARTY_OF_DUNGEON2 )
			{
				DynamicZonePartyOfDungeon2* pAlterOfBlood = dynamic_cast<DynamicZonePartyOfDungeon2*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setGroupID(m_InstantID);
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_PARTY_OF_DUNGEON3 )
			{

				if ( !pPC->isFlag( Effect::EFFECT_CLASS_SIMYUN_ENTER_LOOP ) )
				{
					EffectSimyunEnterLoop* pEffect = new EffectSimyunEnterLoop(pPC);
					pEffect->setDeadline(432000*2 );

					pPC->setFlag( pEffect->getEffectClass() );
					pPC->addEffect( pEffect );

					pEffect->create( pPC->getName() );

					GCAddEffect gcAddEffect;
					gcAddEffect.setObjectID( pPC->getObjectID() );
					gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
					gcAddEffect.setDuration( 43200 );

					pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );

				DynamicZonePartyOfDungeon3* pAlterOfBlood = dynamic_cast<DynamicZonePartyOfDungeon3*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setGroupID(m_InstantID);
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				//pAlterOfBlood->setRace( pPC->getRace() );

				}else{
				teleportok = false;
				}
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_PARTY_OF_DUNGEON4 )
			{
				DynamicZonePartyOfDungeon4* pAlterOfBlood = dynamic_cast<DynamicZonePartyOfDungeon4*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setGroupID(m_InstantID);
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_ASYLION)
			{
				DynamicZoneAsylion* pAlterOfBlood = dynamic_cast<DynamicZoneAsylion*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setRace(pCreature->getRace());
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_TIME_OF_DUNGEON)
			{
				DynamicZoneTimeOfDungeon* pAlterOfBlood = dynamic_cast<DynamicZoneTimeOfDungeon*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_BOSS_ROOM)
			{
				DynamicZoneBossRoom* pAlterOfBlood = dynamic_cast<DynamicZoneBossRoom*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_BOSS_ROOM2)
			{
				DynamicZoneBossRoom2* pAlterOfBlood = dynamic_cast<DynamicZoneBossRoom2*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_MENEGROTH1)
			{
				DynamicZoneMenegroth1* pAlterOfBlood = dynamic_cast<DynamicZoneMenegroth1*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_CASTLE_OF_DEFENSE)
			{
				DynamicZoneCastleOfDefense* pAlterOfBlood = dynamic_cast<DynamicZoneCastleOfDefense*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_MINI_GAME)
			{
				DynamicZoneMiniGame* pAlterOfBlood = dynamic_cast<DynamicZoneMiniGame*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_TIFFAGUES_1)
			{
				DynamicZoneTiffagues_1* pAlterOfBlood = dynamic_cast<DynamicZoneTiffagues_1*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_TIFFAGUES_2_1)
			{
				DynamicZoneTiffagues_2_1* pAlterOfBlood = dynamic_cast<DynamicZoneTiffagues_2_1*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_TIFFAGUES_2_2)
			{
				DynamicZoneTiffagues_2_2* pAlterOfBlood = dynamic_cast<DynamicZoneTiffagues_2_2*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}

			if ( targetDynamicZoneType == DYNAMIC_ZONE_HILANOM)
			{
				DynamicZoneHilanom* pAlterOfBlood = dynamic_cast<DynamicZoneHilanom*>(pDynamicZone);
				Assert( pAlterOfBlood != NULL );
				pAlterOfBlood->setZoneID(pCreature->getZoneID());
				pAlterOfBlood->setZoneX(pCreature->getX());
				pAlterOfBlood->setZoneY(pCreature->getY());
				pAlterOfBlood->setInstantID(m_InstantID);
				//pAlterOfBlood->setRace( pPC->getRace() );
			}
			/*
			파티나 개인으로 다 이동 하게끔 한다.
			*/
			if(teleportok){
			if(pPC->getPartyID() ==0){
			transportCreature(pCreature, pDynamicZone->getZoneID(), m_X, m_Y, true);
			}else{
			const PCManager* pPCManager = pCreature->getZone()->getPCManager();
			pPCManager->transportPartyCreatures(pDynamicZone->getZoneID(), m_X, m_Y, pPC->getPartyID(), 0 );
			}
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
string ActionEnterInstant::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionEnterInstant("
	    << "ZoneID:" << (int)m_ZoneID
	    << ",X:"  << (int)m_X
	    << ",Y:"  << (int)m_Y
	    << ")";
	return msg.toString();

	__END_CATCH
}

