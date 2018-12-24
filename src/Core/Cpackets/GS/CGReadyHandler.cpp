//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReadyHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReady.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "ZonePlayerManager.h"
	#include "Zone.h"
	#include "ZoneGroup.h"
	#include "Gpackets/GCLoadInventory.h"
	#include "PacketUtil.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ�� ������ �ε��� ������, ���� �������� CGReady ��Ŷ�� �����Ѵ�.
// �� ��Ŷ�� ���� Ŭ���̾�Ʈ�� Zone�� ť�� PC�� �־��ְ�, ����������
// �÷��̾ IPM���� ZPM���� �ű��.
//////////////////////////////////////////////////////////////////////////////
void CGReadyHandler::execute (CGReady* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : BEGIN");

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	// �ּ�ó�� by sigi. 2002.5.11
	//Assert(pZone != NULL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : After pointer");
	
	//--------------------------------------------------------------------------------
	// �÷��̾ IPM���� �����ϰ� ZPM���� �ű��.
	//--------------------------------------------------------------------------------
	try 
	{
		// IncomingPlayer�� Process Commands �ȿ��� ����Ǵ� ���̹Ƿ� �ݵ�� �� ������� ������ �� ���̴�.
		//g_pIncomingPlayerManager->deletePlayer_NOBLOCKED(pGamePlayer->getSocket()->getSOCKET());
		g_pIncomingPlayerManager->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		// Core�� ���� ���濡 ���� ������ ���� ������ �ִ��� �����ϱ� ���Ͽ� heartbeat���� �ϰ������� ������.
		g_pIncomingPlayerManager->pushOutPlayer(pGamePlayer);

		/*GCLoadInventory gcLoadInventory;
		makeGCLoadInventory(&gcLoadInventory, pCreature, 0);
		pGamePlayer->sendPacket(&gcLoadInventory);*/

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After deletePlayer[Name:%s]", pCreature->getName().c_str());

		/*
		ZoneGroup* pZoneGroup = pZone->getZoneGroup();
		Assert(pZoneGroup != NULL);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After getZoneGroup[Name:%s]", pCreature->getName().c_str());

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		Assert(pZonePlayerManager != NULL);	

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After getZonePlayerManager[Name:%s]", pCreature->getName().c_str());

//		pZonePlayerManager->addPlayer(pGamePlayer);
//		pZonePlayerManager->pushPlayer(pGamePlayer);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After pushPlayer[Name:%s]", pCreature->getName().c_str());


		// PC�� ���� ť�� ����ִ´�.
		//pGamePlayer->getCreature()->getZone()->pushPC(pGamePlayer->getCreature());

//		pZone->pushPC(pCreature);

		//filelog("CGReadyTrace.txt", "CGReadyHandler : After pushPC[Name:%s]", pCreature->getName().c_str());

		//pZone->addPC(pCreature, pCreature->getX(), pCreature->getY(), DOWN);
		*/
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;
		msg << "Critical Error : IPM�� �÷��̾ ���׿�. ���� ������..  - -;\n" << nsee.toString();
		throw Error(msg.toString());
	}

	// ��õ��� �����κ��� ������ ���� �ʴ� �����̴�.
	pGamePlayer->setPlayerStatus(GPS_NORMAL);

	//filelog("CGReadyTrace.txt", "CGReadyHandler : END");

#endif

	__END_DEBUG_EX 
	__END_CATCH
}
