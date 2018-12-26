//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TrueColorofVampLoad.h"
#include "EffectTrueColorofVampLoad.h"
#include "EffectHPRecovery.h"
#include "EffectManager.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCHPRecoveryStartToSelf.h"
#include "Gpackets/GCHPRecoveryStartToOthers.h"
//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void TrueColorofVampLoad::execute(Vampire* pSlayer, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

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
//		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
//		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_TRUE_COLOR_OF_VAMP_LOAD);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// ���� �ð��� ����Ѵ�.
			SkillInput input(pSlayer);
			SkillOutput output;
			computeOutput(input, output);

			// ����Ʈ Ŭ������ ?���?���δ�.
			EffectTrueColorofVampLoad* pEffect = new EffectTrueColorofVampLoad(pSlayer);
			pEffect->setDeadline(output.Duration);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_TRUE_COLOR_OF_VAMP_LOAD);

			VAMPIRE_RECORD prev;
			pSlayer->getVampireRecord(prev);
			pSlayer->initAllStat();
			pSlayer->addModifyInfo(prev, _GCSkillToSelfOK1);

			// ����ġ�� �ø���.
			//SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			//Exp_t ExpUp = 10* (Grade + 1);
			//shareAttrExp(pSlayer, ExpUp, 1, 8, 1, _GCSkillToSelfOK1);
			//increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
//			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToSelfOK2, pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(pEffect->getEffectClass());
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect, pSlayer);

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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

TrueColorofVampLoad g_TrueColorofVampLoad;
