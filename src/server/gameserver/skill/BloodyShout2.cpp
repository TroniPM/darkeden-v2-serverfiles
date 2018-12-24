//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyShout2.h"
#include "EffectBloodyShout2.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void BloodyShout2::execute(Vampire* pSlayer, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_BLOODY_SHOUT1);
		bool bEffected2   = pSlayer->isFlag(Effect::EFFECT_CLASS_BLOODY_SHOUT2);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && !bEffected2)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// ���� �ð��� ����Ѵ�.
			SkillInput input(pSlayer);
			SkillOutput output;
			computeOutput(input, output);

			// ����Ʈ Ŭ������ ����� ���δ�.
			EffectBloodyShout2* pEffect = new EffectBloodyShout2(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setLevel(output.Damage);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_BLOODY_SHOUT2);

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

BloodyShout2 g_BloodyShout2;
