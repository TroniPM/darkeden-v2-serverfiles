//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradePrepareHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradePrepare.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"
	#include "StringStream.h"

	#include "Gpackets/GCTradePrepare.h"
	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradePrepareHandler::execute (CGTradePrepare* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t     TargetOID   = pPacket->getTargetObjectID();
	BYTE           CODE        = pPacket->getCode();
	GamePlayer*    pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	GCTradePrepare gcTradePrepare;

	Creature* pSender = pGamePlayer->getCreature();
	Assert(pSender != NULL);

	Zone* pZone = pSender->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ����ڸ� ������ ã�ƺ���.
	Creature* pReceiver = NULL;
	/*
	try { pReceiver = pZone->getCreature(TargetOID); }
	catch (NoSuchElementException) { pReceiver = NULL; }
	*/

	// NoSuch����. by sigi. 2002.5.2
	pReceiver = pZone->getCreature(TargetOID);

	// ��ȯ�� �� ���� �������� �ʴ´ٸ� �翬�� ��ȯ�� �� ����.
	if (pReceiver == NULL)
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// ��ȯ�� �� ��� ���� ���� �̸��� ���ٸ�, �� ���� ĳ���̶�� ������ �߶������.
	// ������ �̷� ��찡 �߻��ߴ�. ��� ������ �� ������... 2002-03-04 �輺��
	if (pSender->getName() == pReceiver->getName())
	{
		StringStream msg;
		msg << "CGTradePrepare : Error, Same Creature!!! Name[" << pSender->getName() << "]";
		filelog("TradeError.log", "%s", msg.toString().c_str());
		throw ProtocolException(msg.toString());
	}

	// ��ȯ�� �� ���� PC�� �ƴϰų�, ������ �ٸ��ٸ� ��ȯ�� �� ���� ����.
	if (!pReceiver->isPC() || !isSameRace(pSender, pReceiver))
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

	// �� �� ���� ���뿡 �ִ��� üũ�� �Ѵ�.
	if (!isInSafeZone(pSender) || !isInSafeZone(pReceiver))
	{
		pTradeManager->cancelTrade(pSender);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// ������̸� Ÿ�� �ִٸ� ������.
	if (pSender->isSlayer() && pReceiver->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pSender);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pReceiver);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pSender);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pSender->isOusters() && pReceiver->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pSender);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pReceiver);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
		)
		{
			pTradeManager->cancelTrade(pSender);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	TradeInfo* pInfo1          = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2          = pTradeManager->getTradeInfo(pReceiver->getName());
	Player*    pReceiverPlayer = pReceiver->getPlayer();

	// A�� B���� ��ȯ�� ���� ó�� �䱸�ߴ�...
	switch (CODE)
	{
		////////////////////////////////////////////////////////////
		// A�� B���� ��ȯ�� �䱸�����Ƿ�,
		// B���� A�� ��ȯ�� �䱸�ϰ� �ִٴ� ����� �˷��ش�.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_REQUEST:
			// ��ȯ�� �䱸�� ���� ��ȯ ���̶��... -_-
			if (pInfo1 != NULL)
			{
				pTradeManager->cancelTrade(pSender);
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_ALREADY_TRADING);
				return;
			}

			// ��ȯ�� �䱸���� ���� ��ȯ ���̶��,
			// �ٻڴϱ� ��ȯ�� ���� �� ����.
			if (pInfo2 != NULL)
			{
				gcTradePrepare.setTargetObjectID(pPacket->getTargetObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_BUSY);
				pPlayer->sendPacket(&gcTradePrepare);
				return;
			}
			   
			// ��Ŷ�� �����ش�.
			gcTradePrepare.setTargetObjectID(pSender->getObjectID());
			gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_REQUEST);
			pReceiverPlayer->sendPacket(&gcTradePrepare);

			// �� �� ��ȯ ���� �����Ƿ�, TradeInfo�� ������ �ش�.
			pTradeManager->initTrade(pSender, pReceiver);
			break;

		////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_CANCEL:
			// ��ȯ �������� üũ�Ѵ�.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_CANCEL);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// ��ȯ�� �ź������Ƿ�, TradeInfo�� ������ �ش�.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B�� ��ȯ�� ���Ѵٴ� ����� A���� �˷��ش�.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_ACCEPT:
			// ��ȯ �������� üũ�Ѵ�.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_ACCEPT);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B�� ��ȯ�� �ź��Ѵٴ� ����� A���� �˷��ش�.
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_REJECT:
			// ��ȯ �������� üũ�Ѵ�.
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_REJECT);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// ��ȯ�� �ź������Ƿ�, TradeInfo�� ������ �ش�.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		////////////////////////////////////////////////////////////
		// B�� ���� ��ȯ�� ���� �� ���� ����(������ �ִ� ���)��� 
		// ���� A���� �˷��ش�. 
		////////////////////////////////////////////////////////////
		case CG_TRADE_PREPARE_CODE_BUSY:
			if (pTradeManager->isTrading(pSender, pReceiver))
			{
				// ��Ŷ�� �����ش�.
				gcTradePrepare.setTargetObjectID(pSender->getObjectID());
				gcTradePrepare.setCode(GC_TRADE_PREPARE_CODE_BUSY);
				pReceiverPlayer->sendPacket(&gcTradePrepare);
				// ��ȯ�� �ź������Ƿ�, TradeInfo�� �������ش�.
				pTradeManager->cancelTrade(pSender, pReceiver);
			}
			else
			{
				executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
				return;
			}
			break;

		// �˼� ���� �ڵ��...
		default:
			throw ProtocolException("CGTradePrepare::execute() : �� �� ���� �ڵ�");
	}


#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradePrepareHandler::executeError (CGTradePrepare* pPacket , Player* pPlayer, BYTE ErrorCode)
	 
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


