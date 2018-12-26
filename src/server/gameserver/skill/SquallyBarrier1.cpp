//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SquallyBarrier1.h"
#include "EffectSquallyBarrier1.h"
#include "EffectSquallyBarrier1back.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void SquallyBarrier1::execute(Ousters* pSlayer, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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
		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		//SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER1);
		bool bEffected2   = pSlayer->isFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER2);
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && !bEffected2)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 이팩트 클래스를 만들어 붙인다.
			EffectSquallyBarrier1* pEffect = new EffectSquallyBarrier1(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setLevel(50);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_SQUALLY_BARRIER1);

			OUSTERS_RECORD prev;
			pSlayer->getOustersRecord(prev);
			pSlayer->initAllStat();
			pSlayer->addModifyInfo(prev, _GCSkillToSelfOK1);

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

			//기존 질풍 배리어가 있다면 기존꺼에도 쿨딜레이를 불어넣어준다.. ''
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

SquallyBarrier1 g_SquallyBarrier1;
