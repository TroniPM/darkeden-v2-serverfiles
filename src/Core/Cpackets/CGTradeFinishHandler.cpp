//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinishHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeFinish.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeFinish.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::execute (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ�� ���ϴ� ������ ������ ã�ƺ���.
	Creature* pTargetPC = NULL;
	/*
	try 
	{ 
		pTargetPC = pZone->getCreature(TargetOID); 
	}
	catch (NoSuchElementException) 
	{ 
		pTargetPC = NULL; 
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID); 

	// ��ȯ ��밡 ���ٸ� ������
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// ��ȯ ��밡 ����� �ƴϰų�, ���� ������ �ƴ϶�� ������.
	if (!pTargetPC->isPC() || !isSameRace(pTargetPC, pPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

	// �� �� ���� ���뿡 �ִ��� üũ�� �Ѵ�.
	if (!isInSafeZone(pPC) || !isInSafeZone(pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// ������̸� Ÿ�� �ִٸ� ������.
	if (pPC->isSlayer() && pTargetPC->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pPC);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pTargetPC);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pPC->isOusters() && pTargetPC->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pPC);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pTargetPC);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
		)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

    // ���̼� ��ȯ�� �ϰ� �ִ� ���°� �ƴ϶�� ������.
	if (!pTradeManager->isTrading(pPC, pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
		return;
	}

	if (pPC->isSlayer()) executeSlayer(pPacket, pPlayer);
	else if (pPC->isVampire()) executeVampire(pPacket, pPlayer);
	else if (pPC->isOusters()) executeOusters(pPacket, pPlayer);
	else throw ProtocolException("CGTradeFinishHanderl::execuete() : �� �� ���� �÷��̾� ũ�����Դϴ�.");
		
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeSlayer (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*       pSender         = dynamic_cast<Slayer*>(pPC);
	Slayer*       pReceiver       = dynamic_cast<Slayer*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// ���� �ð��� ���´�.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// ��ȯ�� �³��ϴ� �ڵ��. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK�� ���ƿ� �ð��� �ƴ϶�� ������.
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// ��ȯ�� �³��ߴٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_FINISH);

		//cout << "CGTradeFinish [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ٲ����." << endl;

		// ���浵 ��ȯ�� ����ϰ� �ִٸ�, ������ ��ȯ�� �ϵ��� �Ѵ�.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]�� ���µ� TRADE_FINISH�̹Ƿ�, ��ȯ�� �����Ѵ�." << endl;

			// Ȯ���� ��ȯ�� �� �� �ִٸ� ��ȯ�� �Ѵ�.
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// �� ���� ��ȯ�� �����϶�� ��Ŷ�� �����ش�.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// ������ ��ȯ�� �����Ѵ�.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if ( pTradeManager->canTrade(pSender, pReceiver) == 2 )
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else 
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// ��ȯ�� �ź��ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ�� ��ҽ�Ų��.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// ��ȯ�� ��ҵǾ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// ��ȯ�� �����ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_TRADING);

		// OK�� �����ٰ� cancel�� ������, ���� 4�� ������ OK�� �ٽ� ���ƿͼ���
		// �� �ȴ�. �׷��Ƿ� ���⼭ �ð��� ������ �ش�.
		pInfo1->setNextTime(currentTime);

		// ��ȯ�� �����Ǿ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// �˼� ���� �ڵ��. ����ϰ� ©���ش�.
	else throw ProtocolException("CGTradeFinish::executeSlayer() : �� �� ���� �ڵ�");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeVampire (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*      pSender         = dynamic_cast<Vampire*>(pPC);
	Vampire*      pReceiver       = dynamic_cast<Vampire*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// ���� �ð��� ���´�.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// ��ȯ�� �³��ϴ� �ڵ��. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK�� ���ƿ� �ð��� �ƴ϶�� ������. 
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// ��ȯ�� �³��ߴٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_FINISH);

		// ���浵 ��ȯ�� ����ϰ� �ִٸ�, ������ ��ȯ�� �ϵ��� �Ѵ�.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			// Ȯ���� ��ȯ�� �� �� �ִٸ� ��ȯ�� �Ѵ�.
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]�� ���µ� TRADE_FINISH�̹Ƿ�, ��ȯ�� �����Ѵ�." << endl;
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// �� ���� ��ȯ�� �����϶�� ��Ŷ�� �����ش�.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// ������ ��ȯ�� �����Ѵ�.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if (pTradeManager->canTrade(pSender, pReceiver) == 2)
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// ��ȯ�� �ź��ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ�� ��ҽ�Ų��.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// ��ȯ�� ��ҵǾ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// ��ȯ�� �����ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_TRADING);

		// OK�� �����ٰ� cancel�� ������, ���� 4�� ������ OK�� �ٽ� ���ƿͼ���
		// �� �ȴ�. �׷��Ƿ� ���⼭ �ð��� ������ �ش�.
		pInfo1->setNextTime(currentTime);

		// ��ȯ�� �����Ǿ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// �˼� ���� �ڵ��. ����ϰ� ©���ش�.
	else throw ProtocolException("CGTradeFinish::executeVampire() : �� �� ���� �ڵ�");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeOusters (CGTradeFinish* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	BYTE          CODE            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*      pSender         = dynamic_cast<Ousters*>(pPC);
	Ousters*      pReceiver       = dynamic_cast<Ousters*>(pTargetPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	TradeInfo*    pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo*    pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	GCTradeFinish gcTradeFinish;

	// ���� �ð��� ���´�.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// ��ȯ�� �³��ϴ� �ڵ��. 
	if (CODE == CG_TRADE_FINISH_ACCEPT)
	{
		// OK�� ���ƿ� �ð��� �ƴ϶�� ������. 
		if (pInfo1->isValidOKTime(currentTime) == false)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_UNKNOWN);
			return;
		}

		// ��ȯ�� �³��ߴٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_ACCEPT);
		pTargetPlayer->sendPacket(&gcTradeFinish);

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_FINISH);

		// ���浵 ��ȯ�� ����ϰ� �ִٸ�, ������ ��ȯ�� �ϵ��� �Ѵ�.
		if (pInfo2->getStatus() == TRADE_FINISH)
		{
			// Ȯ���� ��ȯ�� �� �� �ִٸ� ��ȯ�� �Ѵ�.
			//cout << "CGTradeFinish [" << pReceiver->getName() << "]�� ���µ� TRADE_FINISH�̹Ƿ�, ��ȯ�� �����Ѵ�." << endl;
			if (pTradeManager->canTrade(pSender, pReceiver) == 1)
			{
				// �� ���� ��ȯ�� �����϶�� ��Ŷ�� �����ش�.
				gcTradeFinish.setTargetObjectID(pSender->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pTargetPlayer->sendPacket(&gcTradeFinish);

				gcTradeFinish.setTargetObjectID(pReceiver->getObjectID());
				gcTradeFinish.setCode(GC_TRADE_FINISH_EXECUTE);
				pPlayer->sendPacket(&gcTradeFinish);

				// ������ ��ȯ�� �����Ѵ�.
				pTradeManager->processTrade(pSender, pReceiver);
			}
			else if (pTradeManager->canTrade(pSender, pReceiver) == 2)
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX);
				return;
			}
			else
			{
				pTradeManager->cancelTrade(pPC);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE);
				return;
			}
		}
	}
	// ��ȯ�� �ź��ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_REJECT)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_REJECT);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ�� ��ҽ�Ų��.
		pTradeManager->cancelTrade(pSender, pReceiver);

		// ��ȯ�� ��ҵǾ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_REJECT);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// ��ȯ�� �����ϴ� �ڵ��.
	else if (CODE == CG_TRADE_FINISH_RECONSIDER)
	{
		// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
		if (pInfo1->getStatus() == TRADE_FINISH)
		{
			// ���� ��Ŷ�� �����ش�.
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_FINISH_RECONSIDER);
			pPlayer->sendPacket(&gcTradeVerify);
		}

		// ��ȯ ���¸� ��ȯ�Ѵ�.
		pInfo1->setStatus(TRADE_TRADING);

		// OK�� �����ٰ� cancel�� ������, ���� 4�� ������ OK�� �ٽ� ���ƿͼ���
		// �� �ȴ�. �׷��Ƿ� ���⼭ �ð��� ������ �ش�.
		pInfo1->setNextTime(currentTime);

		// ��ȯ�� �����Ǿ��ٴ� ���� ���濡�� �˷��ش�.
		gcTradeFinish.setTargetObjectID(pSender->getObjectID());
		gcTradeFinish.setCode(GC_TRADE_FINISH_RECONSIDER);
		pTargetPlayer->sendPacket(&gcTradeFinish);
	}
	// �˼� ���� �ڵ��. ����ϰ� ©���ش�.
	else throw ProtocolException("CGTradeFinish::executeOusters() : �� �� ���� �ڵ�");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeFinishHandler::executeError(CGTradeFinish* pPacket, Player* pPlayer, BYTE ErrorCode)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GCTradeError gcTradeError;
	gcTradeError.setTargetObjectID(pPacket->getTargetObjectID());
	gcTradeError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcTradeError);

#endif

	__END_DEBUG_EX __END_CATCH
}

