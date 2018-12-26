//////////////////////////////////////////////////////////////////////////////
// Filename    : RapidGliding.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RapidGliding.h"
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
void RapidGliding::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		// NPC�� ������ ���� ����.
		//		bool bIncreaseDomainExp = pVampire->isRealWearingEx(Vampire::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if ( !rect.ptInRect(X, Y) && (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 1801 || pZone->getDynamicZone()->getTemplateZoneID() == 1803 || pZone->getDynamicZone()->getTemplateZoneID() == 1804))
		{
			executeSkillFailException(pVampire, getSkillType());
		}

		SkillInput input(pVampire);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, output.Range);
		bool bEffected	 = pVampire->hasRelicItem() 
							|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) 
							|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);
		bool bPassLine	 = isPassLine( pZone, pVampire->getX(), pVampire->getY(), X, Y );

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected && bPassLine )
		{

			// ������ PC�� �������ش�.
			if (pZone->moveFastPC(pVampire, pVampire->getX(), pVampire->getY(), X, Y, getSkillType())) 
			{
				decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

				_GCSkillToTileOK1.setSkillType(SkillType);
				_GCSkillToTileOK1.setCEffectID(0);
				_GCSkillToTileOK1.setX(X);
				_GCSkillToTileOK1.setY(Y);
				_GCSkillToTileOK1.setRange(0);
				_GCSkillToTileOK1.setDuration(0);

				_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
				_GCSkillToTileOK5.setSkillType(SkillType);
				_GCSkillToTileOK5.setX(X);
				_GCSkillToTileOK5.setY(Y);
				_GCSkillToTileOK5.setRange(0);
				_GCSkillToTileOK5.setDuration(0);

				// �ڽſ��� �ٲ� HP�� �˷��ش�.
				pPlayer->sendPacket( &_GCSkillToTileOK1);

				// ������ HP�� �ٲ��ٰ� �˸���.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pVampire->getHP());
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &_GCSkillToTileOK5, pVampire);

				pVampireSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailException(pVampire, getSkillType());
			}
		} 
		else 
		{
			executeSkillFailException(pVampire, getSkillType());
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;


	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void RapidGliding::execute(Vampire * pVampire, ObjectID_t TargetObjectID, VampireSkillSlot * pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		// NPC�� ������ ���� ����.
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

//		bool bIncreaseDomainExp = pVampire->isRealWearingEx(Vampire::WEAR_RIGHTHAND);

		execute( pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID );
/*
		SkillInput input(pVampire);
		SkillOutput output;
		computeOutput(input, output);

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, output.Range);
		bool bEffected	 = pVampire->hasRelicItem();

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{

			// ������ PC�� �������ش�.
			if (pZone->moveFastPC(pVampire, pVampire->getX(), pVampire->getY(), pTargetCreature->getX(), pTargetCreature->getY())) 
			{
				GCModifyInformation	gcMI;

				decreaseMana(pVampire, RequiredMP, gcMI);

				// �ڽſ��� �ٲ� HP�� �˷��ش�.
				pPlayer->sendPacket( &gcMI );

				// ������ HP�� �ٲ��ٰ� �˸���.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pVampire->getHP());
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);

				pVampireSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
			}
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
		*/
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

RapidGliding g_RapidGliding;

