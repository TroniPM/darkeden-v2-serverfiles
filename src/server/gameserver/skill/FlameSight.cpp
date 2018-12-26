//////////////////////////////////////////////////////////////////////////////
// Filename    : FlameSight.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FlameSight.h"
#include "EffectFlameSight.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void FlameSight::execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
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

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t  SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*   pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t SkillLevel = pOustersSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bEffected   = pOusters->isFlag(Effect::EFFECT_CLASS_FLAME_SIGHT);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);
	   
			// ����� �����Ǵ� �ð��� ���õ��� ���� �޶�����.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Sight_t CurrentSight = pOusters->getSight();
			Sight_t oldSight     = CurrentSight;
			
			// Ȥ�ö� ���� ����Ʈ�� �����ִٸ� �����Ѵ�.
			if (pOusters->isEffect(Effect::EFFECT_CLASS_FLAME_SIGHT)) 
			{
				EffectFlameSight* pOldEffectFlameSight = (EffectFlameSight*)pOusters->findEffect(Effect::EFFECT_CLASS_FLAME_SIGHT);
				CurrentSight = pOldEffectFlameSight->getOldSight();
				pOusters->deleteEffect(Effect::EFFECT_CLASS_FLAME_SIGHT);
			}

			// ����Ʈ�� ����� ���δ�.
			EffectFlameSight* pEffectFlameSight = new EffectFlameSight (pOusters);
			pEffectFlameSight->setDeadline(output.Duration);
			pEffectFlameSight->setOldSight(CurrentSight);
			pOusters->setFlag(Effect::EFFECT_CLASS_FLAME_SIGHT);
			pOusters->addEffect(pEffectFlameSight);

			//pEffectLight->create(pOusters->getName());

			// �þ�ó��..
			Sight_t MinSight = pSkillInfo->getMinDamage();
			Sight_t MaxSight = pSkillInfo->getMaxDamage();
			Sight_t NewSight = MinSight + (MaxSight - MinSight)* SkillLevel / 100;

			// �þ� ���濡 ���� ������Ʈ ���� ��Ŷ�� ������.
			pZone->updateScan(pOusters, oldSight, NewSight);

			pOusters->setSight(NewSight);

			if (NewSight != oldSight) _GCSkillToSelfOK1.addShortData(MODIFY_VISION, NewSight);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			// EXP UP!
			//SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			//SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pOusters->getSkillDomainLevel(DomainType));
			//Exp_t ExpUp = 10* (Grade + 1)* 2;

			//shareAttrExp(pOusters, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
			//increaseDomainExp(pOusters, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			//increaseSkillExp(pOusters, DomainType, pOustersSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToSelfOK2 , pOusters);

			// ����Ʈ�� �پ��ٰ� �˷��ش�.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pOusters->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_FLAME_SIGHT);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

FlameSight g_FlameSight;
