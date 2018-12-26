//////////////////////////////////////////////////////////////////////////////
// Filename    : Lightness.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Lightness.h"
#include "EffectLightness.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Lightness::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !pTargetCreature->isSlayer())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_LIGHTNESS);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			// ������ ���δ�.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			// ����ġ�� �÷��ش�.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t      ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToObjectOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1);
			increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
		
			// ����Ʈ�� ȿ���� ���ӽð��� ����Ѵ�.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			input.TargetType = SkillInput::TARGET_OTHER;
			computeOutput(input, output);

			// ����Ʈ�� �����ؼ� ���δ�.
			EffectLightness* pLightness = new EffectLightness (pTargetCreature);
			Assert(pLightness != NULL);
			pLightness->setDeadline(output.Duration);
			pTargetCreature->addEffect(pLightness);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_LIGHTNESS);

			Sight_t oldSight = pTargetCreature->getSight();
			Sight_t newSight = pTargetCreature->getEffectedSight();

			if ( oldSight != newSight )
			{
				pTargetCreature->setSight( newSight );
				pZone->updateScan(pTargetCreature, oldSight, newSight);
				_GCSkillToObjectOK2.addShortData(MODIFY_VISION, newSight);
			}

			// ��Ŷ�� �غ��ؼ� ������.
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);

			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration (output.Duration);

			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration (output.Duration);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pSlayer != pTargetCreature && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}

			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);
		
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToObjectOK5 , cList);

			// ����Ʈ�� �پ��ٰ� �˷��ش�.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pTargetCreature->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LIGHTNESS);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Lightness::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_LIGHTNESS);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// ����ġ�� �÷��ش�.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t      ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// ����Ʈ�� ȿ���� ���ӽð��� ����Ѵ�.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			input.TargetType = SkillInput::TARGET_SELF;
			computeOutput(input, output);

			// ����Ʈ�� �����ؼ� ���δ�
			EffectLightness* pLightness = new EffectLightness (pSlayer);
			pLightness->setDeadline(output.Duration);
			pSlayer->addEffect(pLightness);
			pSlayer->setFlag(Effect::EFFECT_CLASS_LIGHTNESS);

			Sight_t oldSight = pSlayer->getSight();
			Sight_t newSight = pSlayer->getEffectedSight();

			if ( oldSight != newSight )
			{
				pSlayer->setSight( newSight );
				pZone->updateScan(pSlayer, oldSight, newSight);
				_GCSkillToSelfOK1.addShortData(MODIFY_VISION, newSight);
			}

			// ��Ŷ�� �غ��ؼ� ������.
			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
			
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration (output.Duration);

			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(myX, myY, &_GCSkillToSelfOK2, pSlayer);

			// ����Ʈ�� �پ��ٰ� �˷��ش�.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LIGHTNESS);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

Lightness g_Lightness;
