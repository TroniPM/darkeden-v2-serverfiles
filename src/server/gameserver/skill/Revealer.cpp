//////////////////////////////////////////////////////////////////////////////
// Filename    : Revealer.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Revealer.h"
#include "EffectRevealer.h"
#include "Party.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Revealer::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_REVEALER);
		
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// ����� �����Ǵ� �ð��� ���õ��� ���� �޶�����.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// ����Ʈ ������Ʈ�� �����ؼ� ���δ�.
			EffectRevealer* pEffectRevealer = new EffectRevealer (pSlayer);
			pEffectRevealer->setSkillLevel( pSkillSlot->getExpLevel() );
			pEffectRevealer->setDeadline(output.Duration);
			pSlayer->addEffect(pEffectRevealer);
			pSlayer->setFlag(Effect::EFFECT_CLASS_REVEALER);

			// �� ����Ʈ�� �������ν�, �� ���̴� ���� ���δ�.
			pZone->updateMineScan(pSlayer);
			//pZone->updateInvisibleScan( pSlayer );
			pZone->updateHiddenScan( pSlayer );

			// ����ġ�� �ø���.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1)* 2;
			shareAttrExp(pSlayer, ExpUp, 1, 8, 1, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
//			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToSelfOK2, pSlayer);

			// ����Ʈ�� �پ��ٰ� �˷��ش�.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_REVEALER);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			pSkillSlot->setRunTime(output.Delay);

			uint PartyID = pSlayer->getPartyID();
			if (PartyID != 0)
			{
				LocalPartyManager* pLPM = pZone->getLocalPartyManager();
				pLPM->shareRevealer(PartyID, pSlayer, output.Duration);
			}
		}
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Revealer g_Revealer;
