//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketUtil.cpp
// Written by  : excel96
// Description : 
// ���� ������, ����Ⱑ ������ ��Ŷ�� ����� ���� ���� �ϳ��� ���������ν�
// ���������� ��������.
//////////////////////////////////////////////////////////////////////////////

#include "PacketUtil.h"
#include "Properties.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "NPC.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZonePlayerManager.h"
#include "TimeManager.h"
#include "WeatherManager.h"
#include "ItemInfo.h"
#include "Inventory.h"
#include "ItemInfoManager.h"
#include "Effect.h"
#include "EventSystemMessage.h"
#include "ZoneUtil.h"
#include "WarScheduler.h"
#include "PlayerCreature.h"
#include "ItemNameInfo.h"
#include "GameServerInfo.h"
#include "GameServerInfoManager.h"

#include "Item.h"
#include "AR.h"
#include "SR.h"
#include "SG.h"
#include "SMG.h"
#include "Belt.h"
#include "OustersArmsband.h"
#include "Mine.h"
#include "PetItem.h"

#include "Corpse.h"
#include "SlayerCorpse.h"
#include "VampireCorpse.h"
#include "OustersCorpse.h"
#include "MonsterCorpse.h"

#include "PCSlayerInfo3.h"
#include "PCVampireInfo2.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"
#include "SubItemInfo.h"
#include "CastleInfoManager.h"
#include "PKZoneInfoManager.h"

#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCAddSlayer.h"
#include "Gpackets/GCAddVampire.h"
#include "Gpackets/GCAddOusters.h"
#include "Gpackets/GCAddMonster.h"
#include "Gpackets/GCAddNPC.h"
#include "Gpackets/GCAddNewItemToZone.h"
#include "Gpackets/GCDropItemToZone.h"
#include "Gpackets/GCAddSlayerCorpse.h"
#include "Gpackets/GCAddVampireCorpse.h"
#include "Gpackets/GCAddMonsterCorpse.h"
#include "Gpackets/GCAddOustersCorpse.h"
#include "Gpackets/GCOtherModifyInfo.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCWarScheduleList.h"
#include "Gpackets/GCMiniGameScores.h"
#include "Gpackets/GCPetStashList.h"
#include "Gpackets/GCLoadInventory.h"
#include "Gpackets/GCLoadGear.h"
#include "Gpackets/GCUpdateInfo.h"
#include "Gpackets/GCModifyInformation.h"
#include "ModifyInfo.h"
//#include "Gpackets/GCItemNameInfoList.h"

#include "GuildManager.h"

#include "Assert.h"
#include "LogClient.h"
#include "DB.h"
#include <list>
#include <stdio.h>

#include "PCFinder.h"
#include "GuildUnion.h"
#include "GuildManager.h"
#include "Store.h"
#include "DynamicZone.h"

void sendGCOtherModifyInfoGuildUnionByGuildID(uint gID)
	throw()
{

	__BEGIN_TRY

 	// �����ѳ𿡰Կ� ������.
	list<Creature*> cList = g_pPCFinder->getGuildCreatures( gID , 300);
	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{

		Creature* pOtherCreature = *itr;
		Zone *pZone = pOtherCreature->getZone();

		if(pZone != NULL)
		{
			GCOtherModifyInfo   gcOtherModifyInfo;

			ZoneCoord_t X = pOtherCreature->getX();
			ZoneCoord_t Y = pOtherCreature->getY();

			makeGCOtherModifyInfoGuildUnion(&gcOtherModifyInfo, pOtherCreature);

			__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

			pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);

			__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

		}
	}
	


	__END_CATCH
	

}
// �ش�ũ���İ� �Ҽӵ� ����� ��� �𿡰� GCOtherModifyInfo �� ������.
void sendGCOtherModifyInfoGuildUnion(Creature* pTargetCreature)
	throw()
{

	__BEGIN_TRY

	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetCreature->getPlayer());
	Assert(pTargetGamePlayer!=NULL);

	PlayerCreature* pTargetPlayerCreature = dynamic_cast<PlayerCreature*>(pTargetGamePlayer->getCreature());
	Assert( pTargetPlayerCreature != NULL );

 	// �����ѳ𿡰Կ� ������.
	list<Creature*> cList = g_pPCFinder->getGuildCreatures( pTargetPlayerCreature->getGuildID() , 300);
	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{

		Creature* pOtherCreature = *itr;
		if(pOtherCreature != NULL)
		{
			Zone *pZone = pOtherCreature->getZone();

			if(pZone != NULL)
			{
				GCOtherModifyInfo   gcOtherModifyInfo;

				ZoneCoord_t X = pOtherCreature->getX();
				ZoneCoord_t Y = pOtherCreature->getY();

				makeGCOtherModifyInfoGuildUnion(&gcOtherModifyInfo, pOtherCreature);

				if(pTargetCreature->getZone()->getZoneGroup()->getZoneGroupID()== pOtherCreature->getZone()->getZoneGroup()->getZoneGroupID() )
				{
					pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);
				}
				else
				{
					__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

					pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);

					__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

				}
			}
		}
	}
	


	__END_CATCH
	

}


void makeGCOtherModifyInfoGuildUnion(GCOtherModifyInfo* pModifyInformation, Creature* pCreature)
	throw()
{
	__BEGIN_TRY
	
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPlayerCreature != NULL );
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );

	// �Ҽӵ� ������ ������
	if(pUnion == NULL)
	{

		pModifyInformation->addShortData(MODIFY_UNIONID,  	  0);	
		pModifyInformation->addShortData(MODIFY_UNIONGRADE,   GCUpdateInfo::UNION_NOTHING);	
	
		////cout << "GCModifyInfo->GuildInformation - NOT FOUND UNION / UNION_NOTHING" << endl;
	}
	else
	{
		// �Ҽӵ� ������ �ִ�.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pModifyInformation->addShortData(MODIFY_UNIONID, pUnion->getUnionID() );
		
		if(g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature))
		{
			isGuildMaster = true;
		}

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID() )
		{
			isGuildUnionMaster = true;
		}

		if( isGuildMaster && isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_MASTER);
			////cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_MASTER" << endl;
		}
		else if( isGuildMaster && !isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_GUILD_MASTER);
			////cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_GUILD_MASTER" << endl;
		}
		else
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_NOTHING);
//			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_NOTHING" << endl;
		}
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// void makeGCModifyInformation for GuildUnion Info()
//
// ��� Union ������ GCModifyInformation �� �ɴ´�.
//////////////////////////////////////////////////////////////////////////////

	
void makeGCModifyInfoGuildUnion(GCModifyInformation* pModifyInformation, Creature* pCreature)
	throw()
{
	__BEGIN_TRY
	
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPlayerCreature != NULL );
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );

	// �Ҽӵ� ������ ������
	if(pUnion == NULL)
	{

		pModifyInformation->addShortData(MODIFY_UNIONID,  	  0);	
		pModifyInformation->addShortData(MODIFY_UNIONGRADE,   GCUpdateInfo::UNION_NOTHING);	
	
//		//cout << "GCModifyInfo->GuildInformation - NOT FOUND UNION / UNION_NOTHING" << endl;
	}
	else
	{
		// �Ҽӵ� ������ �ִ�.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pModifyInformation->addShortData(MODIFY_UNIONID, pUnion->getUnionID() );
		
		if(g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature))
		{
			isGuildMaster = true;
		}

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID() )
		{
			isGuildUnionMaster = true;
		}

		if( isGuildMaster && isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_MASTER);
//			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_MASTER" << endl;
		}
		else if( isGuildMaster && !isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_GUILD_MASTER);
//			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_GUILD_MASTER" << endl;
		}
		else
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_NOTHING);
//			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_NOTHING" << endl;
		}
	}


	__END_CATCH
}

void makeGCLoadInventory(GCLoadInventory* pUpdateInfo, Creature* pCreature, int Type)
	throw()
{
	__BEGIN_TRY
	cout << " �׽�Ʈ 1 " <<endl;
		if(Type == 0){
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert(pSlayer != NULL);

				pUpdateInfo->setInventoryInfo(pSlayer->getInventoryInfo());
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				Assert(pVampire != NULL);

				pUpdateInfo->setInventoryInfo(pVampire->getInventoryInfo());
			}else if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				Assert(pOusters != NULL);

				pUpdateInfo->setInventoryInfo(pOusters->getInventoryInfo());
			}
		}else{
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert(pSlayer != NULL);

				pUpdateInfo->setInventoryInfo(pSlayer->getInventoryInfo2());
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				Assert(pVampire != NULL);

				pUpdateInfo->setInventoryInfo(pVampire->getInventoryInfo2());
			}else if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				Assert(pOusters != NULL);

				pUpdateInfo->setInventoryInfo(pOusters->getInventoryInfo2());
			}
		}
	cout << " �׽�Ʈ 2 " <<endl;
	__END_CATCH
}
void makeGCLoadGear(GCLoadGear* pUpdateInfo, Creature* pCreature, int Type)
	throw()
{
	__BEGIN_TRY

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPlayerCreature != NULL );

			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert(pSlayer != NULL);

				pUpdateInfo->setGearInfo(pSlayer->getGearInfo());
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				Assert(pVampire != NULL);

				pUpdateInfo->setGearInfo(pVampire->getGearInfo());
			}else if (pCreature->isOusters())
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				Assert(pOusters != NULL);

				pUpdateInfo->setGearInfo(pOusters->getGearInfo());
			}
				pUpdateInfo->setBloodBibleSignInfo( pPlayerCreature->getBloodBibleSign() );
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// void makeGCUpdateInfo()
//
// ��Ż�̳�, �׾ �� ���̸� �̵��� �� ����, GCUpdateInfo ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCUpdateInfo(GCUpdateInfo* pUpdateInfo, Creature* pCreature)
	throw()
{
	__BEGIN_TRY

	////////////////////////////////////////////////////////////
	// �� ��ġ ���� ����
	////////////////////////////////////////////////////////////
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();

	ZoneGroup* pZoneGroup = pZone->getZoneGroup();
	Assert(pZoneGroup != NULL);

	pUpdateInfo->setZoneID(pZone->getZoneID());
	pUpdateInfo->setGameTime(g_pTimeManager->getGameTime());

	pUpdateInfo->setZoneX(x);
	pUpdateInfo->setZoneY(y);

	// DynamicZone ó��
	if ( pZone->isDynamicZone() )
	{
		DynamicZone* pDynamicZone = pZone->getDynamicZone();
		Assert( pDynamicZone != NULL );

		pUpdateInfo->setZoneID( pDynamicZone->getTemplateZoneID() );
	}
	//cout << " ����� ��?" << endl;
	////////////////////////////////////////////////////////////
	// �κ��丮 �� ��� ���� ����
	////////////////////////////////////////////////////////////
	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert(pSlayer != NULL);

		pUpdateInfo->setPCInfo(pSlayer->getSlayerInfo2());

		pUpdateInfo->setGearInfo(pSlayer->getGearInfo());
		pUpdateInfo->setExtraInfo(pSlayer->getExtraInfo());

		if (pSlayer->hasRideMotorcycle())
			pUpdateInfo->setRideMotorcycleInfo(pSlayer->getRideMotorcycleInfo());

		pUpdateInfo->setSMSCharge( pSlayer->getSMSCharge() );
		pUpdateInfo->setNicknameInfo( pSlayer->getNickname() );
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Assert(pVampire != NULL);

		pUpdateInfo->setPCInfo(pVampire->getVampireInfo2());

		// Inventory, Gear ���� ����
		pUpdateInfo->setGearInfo(pVampire->getGearInfo());
		pUpdateInfo->setExtraInfo(pVampire->getExtraInfo());

		pUpdateInfo->setSMSCharge( pVampire->getSMSCharge() );
		pUpdateInfo->setNicknameInfo( pVampire->getNickname() );
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		Assert(pOusters != NULL);

		pUpdateInfo->setPCInfo( pOusters->getOustersInfo2() );
		//cout << " ���� : " << pOusters->getOustersInfo2()->getMaxSize() << endl;
		// Inventory, Gear ���� ����
		pUpdateInfo->setGearInfo(pOusters->getGearInfo());
		pUpdateInfo->setExtraInfo(pOusters->getExtraInfo() );

		pUpdateInfo->setSMSCharge( pOusters->getSMSCharge() );
		pUpdateInfo->setNicknameInfo( pOusters->getNickname() );
	}

	//cout << " ����� ��?2" << endl;
	////////////////////////////////////////////////////////////
	// ����Ʈ ���� ����
	////////////////////////////////////////////////////////////
	pUpdateInfo->setEffectInfo(pCreature->getEffectInfo());
	//cout << " ����� ��?3" << endl;
	////////////////////////////////////////////////////////////
	// �þ� ���� ����
	////////////////////////////////////////////////////////////
	if (pZone->getZoneType()==ZONE_CASTLE )
	{
		pUpdateInfo->setDarkLevel(pZone->getDarkLevel());
		pUpdateInfo->setLightLevel(pZone->getLightLevel());
	}
	else if ( g_pPKZoneInfoManager->isPKZone( pZone->getZoneID() ) )
	{
		pUpdateInfo->setLightLevel(14);
		pUpdateInfo->setDarkLevel(0);
	}
	else if (pCreature->isSlayer())
	{
		if (pCreature->isFlag(Effect::EFFECT_CLASS_LIGHTNESS))
		{
			pUpdateInfo->setLightLevel(15);
			pUpdateInfo->setDarkLevel(1);
		}
		else if (pCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE))
		{
			pUpdateInfo->setDarkLevel(15);
			pUpdateInfo->setLightLevel(1);
		}
		else
		{
			pUpdateInfo->setDarkLevel(pZone->getDarkLevel());
			pUpdateInfo->setLightLevel(pZone->getLightLevel());
		}
	}
	else if ( pCreature->isVampire() )
	{
		pUpdateInfo->setDarkLevel(max(0, DARK_MAX - pZone->getDarkLevel()));
		pUpdateInfo->setLightLevel(min(13, LIGHT_MAX - pZone->getLightLevel()));
	}
	else if ( pCreature->isOusters() )
	{
		if (pCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE))
		{
			pUpdateInfo->setDarkLevel(15);
			pUpdateInfo->setLightLevel(1);
		}
	//	else if (pCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
	//	{
	//		pUpdateInfo->setDarkLevel(15);
	//		pUpdateInfo->setLightLevel(3);
	//	}
		else
		{
			pUpdateInfo->setDarkLevel( 13 );
			pUpdateInfo->setLightLevel( 6 );
		}
	}
	//cout << " ����� ��?4" << endl;
	////////////////////////////////////////////////////////////
	// ���� ���� ����
	////////////////////////////////////////////////////////////
	pUpdateInfo->setWeather(pZone->getWeatherManager()->getCurrentWeather());
	pUpdateInfo->setWeatherLevel(pZone->getWeatherManager()->getWeatherLevel());

	////////////////////////////////////////////////////////////
	// NPC ��������Ʈ ���� ����
	////////////////////////////////////////////////////////////
	pUpdateInfo->setNPCCount(pZone->getNPCCount());
	for (uint i = 0 ; i < pZone->getNPCCount() ; i ++)
		pUpdateInfo->setNPCType(i , pZone->getNPCType(i));

	////////////////////////////////////////////////////////////
	// ���� ��������Ʈ ���� ����
	////////////////////////////////////////////////////////////
	// ������ ����� ��ȯ�Ǵ� ���͸� �̸� �ε��Ѵ�.
	if (pZone->isMasterLair())
	{
		// ����� SpriteType�̴�. -_-; by sigi. 2002.10.8
		const int num = 25;
		const MonsterType_t mtypes[num] =
		{
			27,		// �������
			40,		// �񷹸�
			41,		// ��Ƽ��Ʈ���̴�
			47,		// ī���������
			48,		// ȣ��
			57,		// ������??
			61,		// ��������
			62,		// ����Ʈ���̴�
			64,		// �𵥶�
			68,		// ����
			70,		// ��ũ��ũ����
			71,		// ī��������Ʈ
			72,		// ũ����������
			73,		// �ε��ũ�Ͻ�
			74,		// ����
			75,		// �ﰡ���
			76,		// �����ڵ�
			88,		// ��ũ�����
			89,		// �ε�ī����
			90,		// ī�����׸���
			91,		// ���ɵ�
			92,		// ��ũ������
			101,	// ��������ũ
			102,	// ��?��?
			103		// ���տ���

			//27, 48, 40, 41, 57, 
			//61, 62, 64, 68, 71, 
			//73, 76, 89, 90, 91, 
			//92,103,102, 101
		};

		pUpdateInfo->setMonsterCount( num );
		for (int i = 0 ; i < num; i ++)
			pUpdateInfo->setMonsterType(i , mtypes[i]);
	}
	else
	{
		pUpdateInfo->setMonsterCount(pZone->getMonsterCount());
		for (uint i = 0 ; i < pZone->getMonsterCount() ; i ++)
			pUpdateInfo->setMonsterType(i , pZone->getMonsterType(i));
	}
	//cout << " ����� ��?5" << endl;
	////////////////////////////////////////////////////////////
	// NPC ��ǥ ���� ����
	////////////////////////////////////////////////////////////
	list<NPCInfo*>* pNPCInfos = pZone->getNPCInfos();
	list<NPCInfo*>::const_iterator itr = pNPCInfos->begin();
	for (; itr != pNPCInfos->end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		pUpdateInfo->addNPCInfo(pInfo);
	}
	////////////////////////////////////////////////////////////
	// ������ ���� ����
	////////////////////////////////////////////////////////////
	ServerGroupID_t ZoneGroupCount = g_pZoneGroupManager->size();
	UserNum_t ZoneUserNum = 0;

	for( int i = 1; i < ZoneGroupCount+1; i++ ) {
		ZoneGroup* pZoneGroup;

		try
		{
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
		}
		catch (NoSuchElementException&)
		{
			throw Error("Critical Error : ZoneInfoManager�� �ش� ���׷��� �������� �ʽ��ϴ�.");
		}

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		ZoneUserNum += pZonePlayerManager->size();

	}
	//cout << " ����� ��?6" << endl;
	int UserModify = 0;

	//ServerGroupID_t CurrentServerGroupID = g_pConfig->getPropertyInt( "ServerID" );

	/*
	if( CurrentServerGroupID == 0 
		|| CurrentServerGroupID == 1 
		|| CurrentServerGroupID == 2 
		|| CurrentServerGroupID == 7 ) {
		UserModify = 400;
	}
	*/
	UserModify = 1000;

	if (ZoneUserNum < 100 + UserModify ) 
	{
		pUpdateInfo->setServerStat( SERVER_FREE );
	} 
	else if (ZoneUserNum < 250 + UserModify ) 
	{
		pUpdateInfo->setServerStat( SERVER_NORMAL );
	} 
	else if (ZoneUserNum < 400 + UserModify ) 
	{
		pUpdateInfo->setServerStat( SERVER_BUSY );
	} 
	else if (ZoneUserNum < 500 + UserModify ) 
	{
		pUpdateInfo->setServerStat( SERVER_VERY_BUSY );
	} 
	else if (ZoneUserNum >= 800 + UserModify ) 
	{
		pUpdateInfo->setServerStat( SERVER_FULL );
	} 
	else 
	{
		pUpdateInfo->setServerStat( SERVER_DOWN );
	}

	// �����̾� ���� ����
	if (pZone->isPremiumZone()) pUpdateInfo->setPremiumZone();

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	if (pGamePlayer->isPremiumPlay()) pUpdateInfo->setPremiumPlay();

	static bool bNonPK = g_pGameServerInfoManager->getGameServerInfo( 1, g_pConfig->getPropertyInt( "ServerID" ), g_pConfig->getPropertyInt( "WorldID" ) )->isNonPKServer();

	if ( bNonPK )
	{
		pUpdateInfo->setNonPK(1);
//		//cout << "PK�Ұ���" << endl;
	}
	else
	{
		pUpdateInfo->setNonPK(0);
//		//cout << "PK����" << endl;
	}

	// GuildUnion Information
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPlayerCreature != NULL );
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );
	//cout << " ����� ��?8" << endl;
	// �Ҽӵ� ������ ������
	if(pUnion == NULL)
	{
		pUpdateInfo->setGuildUnionID(0);
		pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_NOTHING);
//		//cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_NOTHING (NOT UNION)" << endl;
	}
	else
	{
		// �Ҽӵ� ������ �ִ�.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pUpdateInfo->setGuildUnionID( pUnion->getUnionID() );
		
		if(g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature))
		{
			isGuildMaster = true;
		}

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID() )
		{
			isGuildUnionMaster = true;
		}

		if( isGuildMaster && isGuildUnionMaster )
		{
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_MASTER);
//			//cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_MASTER" << endl;
		}
		else if( isGuildMaster && !isGuildUnionMaster )
		{
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_GUILD_MASTER);
//			//cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_GUILD_MASTER" << endl;
		}
		else
		{
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_NOTHING);
//			//cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_NOTHING" << endl;
		}
	}
	//cout << " ����� ��?9" << endl;
	pUpdateInfo->setBloodBibleSignInfo( pPlayerCreature->getBloodBibleSign() );

	// �Ŀ� ����Ʈ
	pUpdateInfo->setPowerPoint( pPlayerCreature->getPowerPoint() );
	//cout << " ����� ��?10" << endl;
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// �����̾� �߰� ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddSlayer(GCAddSlayer* pAddSlayer, Slayer* pSlayer) 
	throw()
{
	__BEGIN_TRY

	pAddSlayer->setSlayerInfo(pSlayer->getSlayerInfo3());
	pAddSlayer->setEffectInfo(pSlayer->getEffectInfo());
	pAddSlayer->setPetInfo(pSlayer->getPetInfo());
	pAddSlayer->setNicknameInfo(pSlayer->getNickname());
	pAddSlayer->setStoreInfo(&(pSlayer->getStore()->getStoreInfo()));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� �߰� ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddVampire(GCAddVampire* pAddVampire, Vampire* pVampire) 
	throw()
{
	__BEGIN_TRY
	pAddVampire->setVampireInfo(pVampire->getVampireInfo3());
	pAddVampire->setEffectInfo(pVampire->getEffectInfo());
	pAddVampire->setPetInfo(pVampire->getPetInfo());
	pAddVampire->setNicknameInfo(pVampire->getNickname());
	pAddVampire->setStoreInfo(&(pVampire->getStore()->getStoreInfo()));

	////cout << "makeGCAddVampire: CoatType=" << (int)(pAddVampire->getVampireInfo().getCoatType()) << endl;

	// ����??��Ż�� �̿��ؼ� �̵��� ���̶��...
	if (pVampire->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
		pAddVampire->setFromFlag(1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺�ͽ� �߰� ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddOusters(GCAddOusters* pAddOusters, Ousters* pOusters) 
	throw()
{
	__BEGIN_TRY

	pAddOusters->setOustersInfo(pOusters->getOustersInfo3());
	pAddOusters->setEffectInfo(pOusters->getEffectInfo());
	pAddOusters->setPetInfo(pOusters->getPetInfo());
	pAddOusters->setNicknameInfo(pOusters->getNickname());
	pAddOusters->setStoreInfo(&(pOusters->getStore()->getStoreInfo()));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� �߰� ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddMonster(GCAddMonster* pAddMonster, Monster* pMonster) 
	throw()
{
	__BEGIN_TRY

	pAddMonster->setObjectID(pMonster->getObjectID());
	pAddMonster->setMonsterType(pMonster->getMonsterType());
	pAddMonster->setMonsterName(pMonster->getName());
	pAddMonster->setX(pMonster->getX());
	pAddMonster->setY(pMonster->getY());
	pAddMonster->setDir(pMonster->getDir());
	pAddMonster->setEffectInfo(pMonster->getEffectInfo());
	pAddMonster->setCurrentHP(pMonster->getHP());
	pAddMonster->setMaxHP(pMonster->getHP(ATTR_MAX)); 
	pAddMonster->setLevel(pMonster->getLevel()); 
	// ���ο� ��Ż�� �̿��ؼ� �̵��� ���̶��...
	if (pMonster->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
		pAddMonster->setFromFlag(1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// NPC �߰� ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddNPC(GCAddNPC* pAddNPC, NPC* pNPC) 
	throw()
{
	__BEGIN_TRY

	pAddNPC->setObjectID(pNPC->getObjectID());
	pAddNPC->setName(pNPC->getName());
	pAddNPC->setNPCID(pNPC->getNPCID());
	pAddNPC->setSpriteType(pNPC->getSpriteType());
	pAddNPC->setMainColor(pNPC->getMainColor());
	pAddNPC->setSubColor(pNPC->getSubColor());
	pAddNPC->setX(pNPC->getX());
	pAddNPC->setY(pNPC->getY());
	pAddNPC->setDir(pNPC->getDir());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���ο� �������� ������ �߰��� �� ������ GCAddNewItemToZone�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddNewItemToZone(GCAddNewItemToZone* pAddNewItemToZone, Item* pItem, int X, int Y)
	throw()
{
	__BEGIN_TRY

	Item::ItemClass IClass = pItem->getItemClass();

	pAddNewItemToZone->setObjectID(pItem->getObjectID());
	pAddNewItemToZone->setX(X);
	pAddNewItemToZone->setY(Y);
	pAddNewItemToZone->setItemClass(IClass);
	pAddNewItemToZone->setItemType(pItem->getItemType());
	pAddNewItemToZone->setOptionType(pItem->getOptionTypeList());
	pAddNewItemToZone->setOptionType2(pItem->getOptionTypeList2());
	pAddNewItemToZone->setDurability(pItem->getDurability());
	pAddNewItemToZone->setSilver(pItem->getSilver());
	pAddNewItemToZone->setGrade(pItem->getGrade());
	pAddNewItemToZone->setEnchantLevel(pItem->getEnchantLevel());
	pAddNewItemToZone->setItemNum(pItem->getNum());
	pAddNewItemToZone->setHeroOption(pItem->getHeroOption());
	pAddNewItemToZone->setHeroOptionAttr(pItem->getHeroOptionAttr());

	// �� �迭�� ����� �Ѿ� ���ڸ� ������ ���ڿ� �Ǿ ������.
	if (IClass == Item::ITEM_CLASS_AR) 
	{
		AR * pAR = dynamic_cast<AR*>(pItem);
		pAddNewItemToZone->setItemNum(pAR->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SG) 
	{
		SG * pSG = dynamic_cast<SG*>(pItem);
		pAddNewItemToZone->setItemNum(pSG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SMG) 
	{
		SMG * pSMG = dynamic_cast<SMG*>(pItem);
		pAddNewItemToZone->setItemNum(pSMG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SR) 
	{
		SR * pSR = dynamic_cast<SR*>(pItem);
		pAddNewItemToZone->setItemNum(pSR->getBulletCount());
	} 
	// ��Ʈ��� �ȿ� ����ִ� �����̳� źâ�� ���� ������ ������� �Ѵ�.
	else if (IClass == Item::ITEM_CLASS_BELT) 
	{
		Belt*      pBelt          = dynamic_cast<Belt*>(pItem);
		Inventory* pBeltInventory = pBelt->getInventory();
		BYTE       SubItemCount   = 0;

		// ������ ���ڸ�ŭ �������� ������ �о� ���δ�.
		for(int i = 0; i < pBelt->getPocketCount(); i++) 
		{
			Item * pBeltItem = pBeltInventory->getItem(i, 0);
			if (pBeltItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pBeltItem->getObjectID());
				pSubItemInfo->setItemClass(pBeltItem->getItemClass());
				pSubItemInfo->setItemType(pBeltItem->getItemType());
				pSubItemInfo->setItemNum(pBeltItem->getNum());
				pSubItemInfo->setSlotID(i);

				pAddNewItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pAddNewItemToZone->setListNum(SubItemCount);
	}
	// �Ͻ������ �ȿ� ����ִ� ��?��̳?źâ�� ���� ������ ������� �Ѵ�.
	else if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
	{
		OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
		Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
		BYTE SubItemCount = 0;

		// ������ ���ڸ�ŭ �������� ������ �о� ���δ�.
		for(int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
		{
			Item * pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
			if (pOustersArmsbandItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
				pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
				pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
				pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
				pSubItemInfo->setSlotID(i);

				pAddNewItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pAddNewItemToZone->setListNum(SubItemCount);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���ο� �������� ������ �߰��� �� ������ GCDropItemToZone�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCDropItemToZone(GCDropItemToZone* pDropItemToZone, Item* pItem, int X, int Y)
	throw()
{
	__BEGIN_TRY

	Item::ItemClass IClass = pItem->getItemClass();

	pDropItemToZone->setObjectID(pItem->getObjectID());
	pDropItemToZone->setX(X);
	pDropItemToZone->setY(Y);
	pDropItemToZone->setItemClass(IClass);
	pDropItemToZone->setItemType(pItem->getItemType());
	pDropItemToZone->setOptionType(pItem->getOptionTypeList());
	pDropItemToZone->setOptionType2(pItem->getOptionTypeList2());
	pDropItemToZone->setDurability(pItem->getDurability());
	pDropItemToZone->setSilver(pItem->getSilver());
	pDropItemToZone->setGrade(pItem->getGrade());
	pDropItemToZone->setEnchantLevel(pItem->getEnchantLevel());
	pDropItemToZone->setItemNum(pItem->getNum());
	pDropItemToZone->setHeroOption(pItem->getHeroOption());
	pDropItemToZone->setHeroOptionAttr(pItem->getHeroOptionAttr());

	// �� �迭�� ����� �Ѿ� ���ڸ� ������ ���ڿ� �Ǿ ������.
	if (IClass == Item::ITEM_CLASS_AR) 
	{
		AR * pAR = dynamic_cast<AR*>(pItem);
		pDropItemToZone->setItemNum(pAR->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SG) 
	{
		SG * pSG = dynamic_cast<SG*>(pItem);
		pDropItemToZone->setItemNum(pSG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SMG) 
	{
		SMG * pSMG = dynamic_cast<SMG*>(pItem);
		pDropItemToZone->setItemNum(pSMG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SR) 
	{
		SR * pSR = dynamic_cast<SR*>(pItem);
		pDropItemToZone->setItemNum(pSR->getBulletCount());
	} 
	// ��Ʈ��� �ȿ� ����ִ� �����̳� źâ�� ���� ������ ������� �Ѵ�.
	else if (IClass == Item::ITEM_CLASS_BELT) 
	{
		Belt*      pBelt          = dynamic_cast<Belt*>(pItem);
		Inventory* pBeltInventory = pBelt->getInventory();
		BYTE       SubItemCount   = 0;

		// ������ ���ڸ�ŭ �������� ������ �о� ���δ�.
		for(int i = 0; i < pBelt->getPocketCount(); i++) 
		{
			Item * pBeltItem = pBeltInventory->getItem(i, 0);
			if (pBeltItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pBeltItem->getObjectID());
				pSubItemInfo->setItemClass(pBeltItem->getItemClass());
				pSubItemInfo->setItemType(pBeltItem->getItemType());
				pSubItemInfo->setItemNum(pBeltItem->getNum());
				pSubItemInfo->setSlotID(i);

				pDropItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pDropItemToZone->setListNum(SubItemCount);
	}
	// �Ͻ������ �ȿ� ����ִ� �����̳� źâ�� ���� ������ ������� �Ѵ�.
	else if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
	{
		OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
		Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
		BYTE SubItemCount = 0;

		// ������ ���ڸ�ŭ �������� ������ �о� ���δ�.
		for(int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
		{
			Item * pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
			if (pOustersArmsbandItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
				pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
				pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
				pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
				pSubItemInfo->setSlotID(i);

				pDropItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pDropItemToZone->setListNum(SubItemCount);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ������ �����̾� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddSlayerCorpse(GCAddSlayerCorpse* pAddSlayerCorpse, SlayerCorpse* pSlayerCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddSlayerCorpse->setSlayerInfo(pSlayerCorpse->getSlayerInfo());
	pAddSlayerCorpse->setTreasureCount(pSlayerCorpse->getTreasureCount());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ������ �����̾� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddVampireCorpse(GCAddVampireCorpse* pAddVampireCorpse, VampireCorpse* pVampireCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddVampireCorpse->setVampireInfo(pVampireCorpse->getVampireInfo());
	pAddVampireCorpse->setTreasureCount(pVampireCorpse->getTreasureCount());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ������ ���� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddMonsterCorpse(GCAddMonsterCorpse* pAddMonsterCorpse, MonsterCorpse* pMonsterCorpse, int X, int Y) 
	throw()
{
	__BEGIN_TRY

	pAddMonsterCorpse->setObjectID(pMonsterCorpse->getObjectID());
	pAddMonsterCorpse->setMonsterType(pMonsterCorpse->getMonsterType());
	pAddMonsterCorpse->setMonsterName(pMonsterCorpse->getMonsterName());
	pAddMonsterCorpse->setX(X);
	pAddMonsterCorpse->setY(Y);
	pAddMonsterCorpse->setDir(pMonsterCorpse->getDir());
	pAddMonsterCorpse->setTreasureCount(pMonsterCorpse->getTreasureCount());
	pAddMonsterCorpse->sethasHead(pMonsterCorpse->gethasHead());
	pAddMonsterCorpse->setLastKiller(pMonsterCorpse->getLastKiller());
	pAddMonsterCorpse->setLevel(pMonsterCorpse->getLevel()); 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ������ �ƿ콺���� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddOustersCorpse(GCAddOustersCorpse* pAddOustersCorpse, OustersCorpse* pOustersCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddOustersCorpse->setOustersInfo(pOustersCorpse->getOustersInfo());
	pAddOustersCorpse->setTreasureCount(pOustersCorpse->getTreasureCount());

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// �ٸ� ����� �ִ� ü�� ���� ���� ����Ǿ��� ��쿡 ���ư��� 
// GCOtherModifyInfo�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Slayer* pSlayer, const SLAYER_RECORD* prev)
{
	SLAYER_RECORD cur;
	pSlayer->getSlayerRecord(cur);

	pInfo->setObjectID(pSlayer->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Vampire* pVampire, const VAMPIRE_RECORD* prev)
{
	VAMPIRE_RECORD cur;
	pVampire->getVampireRecord(cur);

	pInfo->setObjectID(pVampire->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Ousters* pOusters, const OUSTERS_RECORD* prev)
{
	OUSTERS_RECORD cur;
	pOusters->getOustersRecord(cur);

	pInfo->setObjectID(pOusters->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCCreateItem(GCCreateItem* pGCCreateItem, Item* pItem, CoordInven_t x, CoordInven_t y) 
	throw(Error)
{
	pGCCreateItem->setObjectID(pItem->getObjectID());
	pGCCreateItem->setItemClass((BYTE)pItem->getItemClass());
	pGCCreateItem->setItemType(pItem->getItemType());
	pGCCreateItem->setOptionType(pItem->getOptionTypeList());
	pGCCreateItem->setOptionType2(pItem->getOptionTypeList2());
	pGCCreateItem->setDurability(pItem->getDurability());
	pGCCreateItem->setEnchantLevel(pItem->getEnchantLevel());
	pGCCreateItem->setHeroOption(pItem->getHeroOption());
	pGCCreateItem->setHeroOptionAttr(pItem->getHeroOptionAttr());
	pGCCreateItem->setSilver(pItem->getSilver());
	pGCCreateItem->setGrade(pItem->getGrade());
	pGCCreateItem->setItemNum(pItem->getNum());
	pGCCreateItem->setInvenX(x);
	pGCCreateItem->setInvenY(y);

	if ( pItem->getItemClass() == Item::ITEM_CLASS_PET_ITEM )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		list<OptionType_t> olist;
		list<OptionType_t> olist2;

		if ( pPetItem->getPetInfo()->getPetOption() != 0 ) 
			olist.push_back(pPetItem->getPetInfo()->getPetOption());

		if ( pPetItem->getPetInfo()->getPetVersionOption() != 0 ) 
			olist.push_back(pPetItem->getPetInfo()->getPetVersionOption());

		list<OptionType_t> optionList = pPetItem->getPetInfo()->getOptionType();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		list<OptionType_t> optionList2 = pPetItem->getPetInfo()->getMixOptionType();
		list<OptionType_t>::const_iterator itr2 = optionList2.begin();

		while(itr != optionList.end())
		{
		olist.push_back(*itr);
		itr++;
		}
		while(itr2 != optionList2.end())
		{
		olist2.push_back(*itr2);
		itr2++;
		}

		pGCCreateItem->setOptionType( olist );
		pGCCreateItem->setOptionType2(olist2);
		pGCCreateItem->setDurability( pPetItem->getPetInfo()->getPetHP() );
		pGCCreateItem->setEnchantLevel( pPetItem->getPetInfo()->getPetAttr() );
		pGCCreateItem->setSilver( pPetItem->getPetInfo()->getPetAttrLevel() );
		pGCCreateItem->setGrade( (pPetItem->getPetInfo()->getPetHP()==0)?(pPetItem->getPetInfo()->getLastFeedTime().daysTo( VSDateTime::currentDateTime() )):(-1) );
		pGCCreateItem->setItemNum( pPetItem->getPetInfo()->getPetLevel() );
	}
}

void sendPayInfo(GamePlayer* pGamePlayer)
	throw (Error)
{
	__BEGIN_TRY

	/*
	char str[80];
	if (pGamePlayer->isPayPlaying())
	{
		Timeval currentTime;
		getCurrentTime(currentTime);
		Timeval payTime = pGamePlayer->getPayPlayTime(currentTime);

		if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PERSON)
		{
			strcpy(str, "[����] ");
		}
		else
		{
			strcpy(str, "[PC��] ");
		}

		if (pGamePlayer->getPayType()==PAY_TYPE_FREE)
		{	
			strcat(str, "���Ἥ������ ���� �����Դ�??");
		}
		else if (pGamePlayer->getPayType()==PAY_TYPE_PERIOD)
		{	
			sprintf(str, "%s%s ���� ��밡���մϴ�.", str, pGamePlayer->getPayPlayAvailableDateTime().toString().c_str());
		}
		else
		{
			sprintf(str, "%s���ð� : %d / %d ��", str, (payTime.tv_sec/60), pGamePlayer->getPayPlayAvailableHours());
		}
	}
	else
	{	
		strcpy(str, "���� ���� ���Դϴ�.");
	}

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(str);
	pGamePlayer->sendPacket (&gcSystemMessage);
	*/

	__END_CATCH
}

// ������ LevelUp effect�� �ѷ��ش�.
void sendEffectLevelUp(Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	//Assert(pCreature->isPC());

	// ������ �ѷ��ش�.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());
	gcAddEffect.setDuration(10);	// ���� �ǹ̾����� 1�ʷ� ����

	if (pCreature->isSlayer())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_SLAYER);
	}
	else if (pCreature->isVampire())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_VAMPIRE);
	}
	else if (pCreature->isOusters())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_OUSTERS);
	}

	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	////cout << "send LEVEL UP : " << gcAddEffect.toString().c_str() << endl;

	__END_CATCH
}

void sendSystemMessage(GamePlayer* pGamePlayer, const string& msg)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pGamePlayer!=NULL);

	// ���� �ִٸ� �ٷ� �����ش�.
	if (pGamePlayer->getPlayerStatus()==GPS_NORMAL)
	{
		GCSystemMessage gcSystemMessage;

		gcSystemMessage.setMessage( msg );

		pGamePlayer->sendPacket( &gcSystemMessage );
	}
	// ���� ���ٸ�.. GamePlayer�� �߰��صΰ� ���߿� �����ش�.
	else
	{
		Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_SYSTEM_MESSAGE);
		EventSystemMessage* pEventSystemMessage = NULL;

		if (pEvent==NULL)
		{
			pEvent = pEventSystemMessage = new EventSystemMessage(pGamePlayer);
			// ���� ���� ���� ó���ȴ�.
			pEvent->setDeadline( 0 );
			pGamePlayer->addEvent( pEvent );
		}
		else
		{
			pEventSystemMessage = dynamic_cast<EventSystemMessage*>(pEvent);
		}

		Assert(pEventSystemMessage!=NULL);
		pEventSystemMessage->addMessage( msg );

		////cout << "NOT GPS_NORMAL: EventSystemMessage" << endl;
	}

	__END_CATCH
}

bool makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList, ZoneID_t zoneID) 
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = getZoneByZoneID(zoneID);
	Assert(pZone!=NULL);
	Assert(pZone->isCastle());

	WarScheduler* pWarScheduler = pZone->getWarScheduler();
	Assert(pWarScheduler!=NULL);

	pWarScheduler->makeGCWarScheduleList( pGCWarScheduleList );

	__END_CATCH

	return true;
}

/*void makeGCItemNameInfoList(GCItemNameInfoList* pInfo, PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	list<ItemNameInfo*>& itemNameInfos = pPC->getItemNameInfoList();
	list<ItemNAmeInfo*>::const_iterator itr = itemNameInfos.begin();

	for( ; itr != itemNameInfos.end() ; itr++ )
	{
		pInfo->addItemNameInfo( *itr );
	}

	__END_CATCH
}*/

void sendGCMiniGameScores( PlayerCreature* pPC, BYTE gameType, BYTE Level )
{
	GCMiniGameScores gcMGS;
	gcMGS.setGameType( (GameType)gameType );
	gcMGS.setLevel(Level);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT Name, Score FROM MiniGameScores WHERE Type=%u AND Level=%u LIMIT 1", gameType, Level);

		// UPDATE�� ���� Result* ��ſ�.. pStmt->getAffectedRowCount()
		if (pResult->next())
		{
			gcMGS.addScore( pResult->getString(1), pResult->getInt(2) );
		}

/*		pResult = pStmt->executeQuery(
				"SELECT Score FROM MiniGameScores WHERE Type=%u AND Level=%u AND Name='%s' LIMIT 1",
					gameType, Level, pPC->getName().c_str() );

		if (pResult->next())
		{
			gcMGS.addScore( pPC->getName(), pResult->getInt(1) );
		}*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	pPC->getPlayer()->sendPacket(&gcMGS);
}

void makeGCPetStashList( GCPetStashList* pPacket, PlayerCreature* pPC )
{
	for ( int i=0; i<MAX_PET_STASH; ++i )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pPC->getPetStashItem(i));

		if ( pPetItem != NULL )
		{
			PetStashItemInfo* pInfo = new PetStashItemInfo;
			pInfo->pPetInfo = pPetItem->getPetInfo();
			pInfo->KeepDays = 0;

			pPacket->getPetStashItemInfos()[i] = pInfo;
		}
	}

	////cout << pPacket->toString() << endl;
}
