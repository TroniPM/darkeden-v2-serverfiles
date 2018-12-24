//////////////////////////////////////////////////////////////////////////////
// Filename    : Teleport.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Teleport.h"
#include "EffectSquallyBarrier1.h"
#include "EffectSquallyBarrier2.h"
#include "DynamicZone.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneInfo.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK5.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯 
//////////////////////////////////////////////////////////////////////////////
void Teleport::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

/*		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType());
			return;
		}
*/
		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		// NPC�� ������ ���� ����.
		//		bool bIncreaseDomainExp = pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if ( !rect.ptInRect(X, Y) && (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 1801 || pZone->getDynamicZone()->getTemplateZoneID() == 1803 || pZone->getDynamicZone()->getTemplateZoneID() == 1804))
		{
			executeSkillFailException(pOusters, getSkillType());
		}

		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/10;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, output.Range);
		bool bEffected	 = pOusters->hasRelicItem() 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{
			// ������ PC�� �������ش�.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), X, Y, getSkillType())) 
			{
				decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);


		if(pOusters->isFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER1)){
		EffectSquallyBarrier1* pEffect = dynamic_cast<EffectSquallyBarrier1*>(pOusters->findEffect(Effect::EFFECT_CLASS_SQUALLY_BARRIER1));
		pEffect->setDeadline(0);
		pOusters->removeFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER1);
		}

		if(pOusters->isFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER2)){
		EffectSquallyBarrier2* pEffect = dynamic_cast<EffectSquallyBarrier2*>(pOusters->findEffect(Effect::EFFECT_CLASS_SQUALLY_BARRIER2));
		pEffect->setDeadline(0);
		pOusters->removeFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER2);
		}

				_GCSkillToTileOK1.setSkillType(SkillType);
				_GCSkillToTileOK1.setCEffectID(0);
				_GCSkillToTileOK1.setX(X);
				_GCSkillToTileOK1.setY(Y);
				_GCSkillToTileOK1.setRange(0);
				_GCSkillToTileOK1.setDuration(0);

				_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
				_GCSkillToTileOK5.setSkillType(SkillType);
				_GCSkillToTileOK5.setX(X);
				_GCSkillToTileOK5.setY(Y);
				_GCSkillToTileOK5.setRange(0);
				_GCSkillToTileOK5.setDuration(0);

				// �ڽſ��� �ٲ� MP�� �˷��ش�.
				pPlayer->sendPacket( &_GCSkillToTileOK1 );
				pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &_GCSkillToTileOK5, pOusters);

				pOustersSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailException(pOusters, getSkillType());
			}
		} 
		else 
		{
			executeSkillFailException(pOusters, getSkillType());
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;


	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Teleport::execute(Ousters * pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		// NPC�� ������ ���� ����.
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

//		bool bIncreaseDomainExp = pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND);

		execute( pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID );
/*
		SkillInput input(pOusters);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, output.Range);
		bool bEffected	 = pOusters->hasRelicItem();

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{

			// ������ PC�� �������ش�.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), pTargetCreature->getX(), pTargetCreature->getY())) 
			{
				GCModifyInformation	gcMI;

				decreaseMana(pOusters, RequiredMP, gcMI);

				// �ڽſ��� �ٲ� HP�� �˷��ش�.
				pPlayer->sendPacket( &gcMI );

				// ������ HP�� �ٲ��ٰ� �˸���.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pOusters->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pOusters->getHP());
				pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcStatusCurrentHP, pOusters);

				pOustersSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
			}
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}
		*/
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Teleport g_Teleport;

