//////////////////////////////////////////////////////////////////////////////
// Filename    : CureCriticalWounds.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CureCriticalWounds.h"
#include "EffectCureCriticalWounds.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

const uint CriticalBloodDrainLevel = 74;

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void CureCriticalWounds::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

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
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_CURE_CRITICAL_WOUNDS);

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
			input.TargetType = SkillInput::TARGET_OTHER;
			computeOutput(input, output);

			// ����Ʈ�� �����ؼ� ���δ�
			EffectCureCriticalWounds * pECCW = new EffectCureCriticalWounds(pSlayer);
			pECCW->setDeadline(output.Duration);
			pECCW->setPoint(output.Damage);
			pECCW->setRange(1);
			pECCW->setDelay(20);
			pECCW->setNextTime(0);
			pSlayer->addEffect(pECCW);
			pSlayer->setFlag( Effect::EFFECT_CLASS_CURE_CRITICAL_WOUNDS );

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
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_CURE_CRITICAL_WOUNDS);
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

	__END_CATCH
}

CureCriticalWounds g_CureCriticalWounds;
