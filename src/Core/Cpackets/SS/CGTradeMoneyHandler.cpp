//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeMoneyHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeMoney.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeMoney.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::execute (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t      TargetOID   = pPacket->getTargetObjectID();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);
	
	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);
	
	Creature* pTargetPC = NULL;
	/*
	try { pTargetPC = pZone->getCreature(TargetOID); } 
	catch (NoSuchElementException) { pTargetPC = NULL; }
	*/

	// NoSuch����. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID);

	// ��ȯ ��밡 ���ٸ� ������.
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// ��ȯ ��밡 ����� �ƴϰų�, ���� ������ ������.
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
	else throw ProtocolException("CGTradeMoney::execute() : �� �� ���� �÷��̾� ũ����");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeSlayer (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� �˻縦 �߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*       pSender         = dynamic_cast<Slayer*>(pPC);
	Slayer*       pReceiver       = dynamic_cast<Slayer*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ���°� �´��� üũ�� �غ����Ѵ�.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// ��ȯâ���� ���� �׼����� ���� ���� ������ �־�� �Ѵ�.
		if (pSender->getGold() >= Amount)
		{
			// ���� �޴� ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �־���� �Ѵ�.
			// ���� ��ȯ ������ ���� ���ؼ� ���. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin      = receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮����
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// ��ȯâ���� ���� ����, �κ��丮���ٰ� ���Ѵ�.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// �κ��丮���� ���� �׼����� ��ȯâ�� �ִ� ���� ���ƾ� �Ѵ�.
		if (pInfo1->getGold() >= Amount)
		{
			// ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �� �� �ִ�.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}
			
			// �κ��丮���ٰ� ���� ���ϰ�, ��ȯâ���� ���� ����.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮���� 
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeVampire (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� �˻縦 �߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*      pSender         = dynamic_cast<Vampire*>(pPC);
	Vampire*      pReceiver       = dynamic_cast<Vampire*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ���°� �´��� üũ�� �غ����Ѵ�.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// ��ȯâ���� ���� �׼����� ���� ���� ������ �־�� �Ѵ�.
		if (pSender->getGold() >= Amount)
		{
			// ���� �޴� ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �־���� �Ѵ�.
			// ���� ��ȯ ������ ���� ���ؼ� ���. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin		= receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮����
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// ��ȯâ���� ���� ����, �κ��丮���ٰ� ���Ѵ�.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// �κ��丮���� ���� �׼����� ��ȯâ�� �ִ� ���� ���ƾ� �Ѵ�.
		if (pInfo1->getGold() >= Amount)
		{
			// ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �� �� �ִ�.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// �κ��丮���ٰ� ���� ���ϰ�, ��ȯâ���� ���� ����.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮���� 
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeOusters (CGTradeMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� �˻縦 �߱� ������,
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t    TargetOID       = pPacket->getTargetObjectID();
	Gold_t        Amount          = pPacket->getAmount();
	BYTE          Code            = pPacket->getCode();
	GamePlayer*   pGamePlayer     = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*     pPC             = pGamePlayer->getCreature();
	Zone*         pZone           = pPC->getZone();
	Creature*     pTargetPC       = pZone->getCreature(TargetOID); 

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*      pSender         = dynamic_cast<Ousters*>(pPC);
	Ousters*      pReceiver       = dynamic_cast<Ousters*>(pTargetPC);
	Player*       pTargetPlayer   = pTargetPC->getPlayer();
	Gold_t        finalAmount     = Amount;
	Gold_t        margin          = 0;
	GCTradeMoney  gcTradeMoney;
	GCTradeVerify gcTradeVerify;

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ���°� �´��� üũ�� �غ����Ѵ�.
	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pReceiver->getName());

	// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
	if (Code == CG_TRADE_MONEY_INCREASE)
	{
		// ��ȯâ���� ���� �׼����� ���� ���� ������ �־�� �Ѵ�.
		if (pSender->getGold() >= Amount)
		{
			// ���� �޴� ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �־���� �Ѵ�.
			// ���� ��ȯ ������ ���� ���ؼ� ���. by sigi. 2003.1.8
			Gold_t receiverGold = pReceiver->getGold() + pInfo1->getGold();
			if (receiverGold + Amount > MAX_MONEY)
			{
				margin		= receiverGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// �κ��丮���� ���� ����, ��ȯâ���� ���Ѵ�.
			pSender->setGold(pSender->getGold() - finalAmount);
			pInfo1->setGold(pInfo1->getGold() + finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_INCREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮����
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_INCREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else 
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_INCREASE_MONEY);
			return;
		}
	}
	// ��ȯâ���� ���� ����, �κ��丮���ٰ� ���Ѵ�.
	else if (Code == CG_TRADE_MONEY_DECREASE)
	{
		// �κ��丮���� ���� �׼����� ��ȯâ�� �ִ� ���� ���ƾ� �Ѵ�.
		if (pInfo1->getGold() >= Amount)
		{
			// ���� �ƽ��� �ʰ��ϰ� �ȴٸ�, �Ϻθ� �� �� �ִ�.
			Gold_t senderGold = pSender->getGold() + pInfo2->getGold();
			if (senderGold + Amount > MAX_MONEY)
			{
				margin      = senderGold + Amount - MAX_MONEY;
				finalAmount = finalAmount - margin;
			}

			// �κ��丮���ٰ� ���� ���ϰ�, ��ȯâ���� ���� ����.
			pSender->setGold(pSender->getGold() + finalAmount);
			pInfo1->setGold(pInfo1->getGold() - finalAmount);

			// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
			if (pInfo1->getStatus() == TRADE_FINISH)
			{
				// ���� ��Ŷ�� �����ش�.
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MONEY_DECREASE);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// �������� ���ϰų� �� ���, ���¸� ��ȯ����� �Ѵ�.
			pInfo1->setStatus(TRADE_TRADING);
			pInfo2->setStatus(TRADE_TRADING);

			// ���� �ø� ����ڿ��� ������ �κ��丮���� 
			// ���� �ݾ��� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(TargetOID);
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE_RESULT);
			gcTradeMoney.setAmount(finalAmount);
			pPlayer->sendPacket(&gcTradeMoney);

			// ���濡�� �ٲ� ������ �����ش�.
			gcTradeMoney.setTargetObjectID(pSender->getObjectID());
			gcTradeMoney.setCode(GC_TRADE_MONEY_DECREASE);
			gcTradeMoney.setAmount(finalAmount);
			pTargetPlayer->sendPacket(&gcTradeMoney);
		}
		else
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_DECREASE_MONEY);
			return;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeMoneyHandler::executeError (CGTradeMoney* pPacket , Player* pPlayer, BYTE ErrorCode)
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


