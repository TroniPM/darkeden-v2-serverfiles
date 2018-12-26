//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAcceptUnionHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAcceptUnion.h"

#ifdef __GAME_SERVER__
	#include "SystemAvailabilitiesManager.h"
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "GuildUnion.h"
	#include "Gpackets/GCGuildResponse.h"
	#include "DB.h"
	#include "StringPool.h"
	#include "Guild.h"

	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCOtherModifyInfo.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "PacketUtil.h"
	#include "PCFinder.h"
	#include "Exception.h"
	#include "ZoneUtil.h"
	#include "Zone.h"
	#include "ZoneGroupManager.h"
	#include "PlayerCreature.h"

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAcceptUnionHandler::execute (CGAcceptUnion* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
    Assert( pGamePlayer != NULL );

    PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
    Assert( pPlayerCreature != NULL );

	SYSTEM_ASSERT(SYSTEM_GUILD);

#ifdef __OLD_GUILD_WAR__
	GCSystemMessage gcSM;
	gcSM.setMessage("��û�п��Ŵ˹���.");
	pGamePlayer->sendPacket( &gcSM );
	return;
#endif

	GCGuildResponse gcGuildResponse;

	GuildUnion *pUnion = GuildUnionManager::Instance().getGuildUnion( pPlayerCreature->getGuildID() );
	if(pUnion == NULL)
	{
		gcGuildResponse.setCode(GuildUnionOfferManager::NOT_IN_UNION);
		pPlayer->sendPacket(&gcGuildResponse);

		return;
	}
	
	// ��û�ѳ��� ���� ���� ����� �������ΰ�? || ������ �����ͱ�尡 �� ��尡 �³�?
	if( !g_pGuildManager->isGuildMaster ( pPlayerCreature->getGuildID(), pPlayerCreature )
		|| pUnion->getMasterGuildID() != pPlayerCreature->getGuildID() 		
		)
	{
		// GC_GUILD_RESPONSE �����ش�.
		// ���� : ��� �����Ͱ� �ƴ��ڳ� -.-+

		gcGuildResponse.setCode(GuildUnionOfferManager::SOURCE_IS_NOT_MASTER);
		pPlayer->sendPacket(&gcGuildResponse);

		return;
	}

	uint result = GuildUnionOfferManager::Instance().acceptJoin( pPacket->getGuildID() );

	gcGuildResponse.setCode(result);
	pPlayer->sendPacket(&gcGuildResponse);

////////////////////
	if(result == GuildUnionOfferManager::OK)
	{

		//cout << "pPacket->getGuildID() : " << endl;
		
		Guild*	pGuild	= g_pGuildManager->getGuild( pPacket->getGuildID() );

		if(pGuild == NULL)	
		{
			return;
		}
		string	TargetGuildMaster = pGuild->getMaster();
		
		//cout << "������ �����Ǿ���. �뺸���� ������ : " << TargetGuildMaster.c_str() << endl;


		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			pStmt->executeQuery( "INSERT INTO Messages (Receiver, Message) values('%s','%s')", TargetGuildMaster.c_str(),  g_pStringPool->c_str( 373 ));
			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

			
		// ���ո����Ͱ� �� ������ ���վ��̵�� UNION_MASTER�� ������� �ϰ�..
		Creature *pCreature = NULL;
		pCreature = pGamePlayer->getCreature();

		if(pCreature == NULL)	return;
			
		GCModifyInformation gcModifyInformation;
		makeGCModifyInfoGuildUnion(&gcModifyInformation, pCreature);

		pPlayer->sendPacket(&gcModifyInformation);

		
		// ���տ� ���Ե� ��� ������ ���״� ���վ��̵�� UNION_GUILD_MASTER�� ������� �ѵ�..
		//
        // �뺸���� �������� ���Union������ �ٽ� ������
	
		Creature *pTargetCreature = NULL;
        __ENTER_CRITICAL_SECTION((*g_pPCFinder))

        pTargetCreature = g_pPCFinder->getCreature_LOCKED(TargetGuildMaster);
        if (pTargetCreature==NULL)
        {
            g_pPCFinder->unlock();
            return;
        }
        GCModifyInformation gcModifyInformation2;
        makeGCModifyInfoGuildUnion(&gcModifyInformation2, pTargetCreature);
        pTargetCreature->getPlayer()->sendPacket(&gcModifyInformation2);

        __LEAVE_CRITICAL_SECTION((*g_pPCFinder))

		//////////////////////////////
		

		// �� ������ �ִ� ��鿡�� ��������� �˸���.
		sendGCOtherModifyInfoGuildUnion(pTargetCreature);
		sendGCOtherModifyInfoGuildUnion(pCreature);

		
		// �ٸ� ������ �ִ� ��鿡�� ��������� �˸���.
		GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pTargetCreature)->getGuildID() );
		GuildUnionManager::Instance().sendModifyUnionInfo( dynamic_cast<PlayerCreature*>(pCreature)->getGuildID() );
		
			

		// GCModifyInformation / GCOtherModifyInfo �� �����ؼ� ������.
		// GCModifyInformation �� pPlayerCreature ����
		// GCOtherModifyInfo �� broadcast �Ѵ�.
		// �־� ���� ������ GuildUnionID �� GuildUnionGrade��?

	}	

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

