//////////////////////////////////////////////////////////////////////////////
// Filename    : Eternity.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Eternity.h"
#include "EffectEternity.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ����
//////////////////////////////////////////////////////////////////////////////
void Eternity::execute(Slayer * pSlayer, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		Tile& rTile = pZone->getTile( pSlayer->getX(), pSlayer->getY() );

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = pSlayer->isFlag( Effect::EFFECT_CLASS_COMA ) && HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_ETERNITY) || rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION)!=NULL;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			Effect* pComa = pSlayer->findEffect( Effect::EFFECT_CLASS_COMA );
			if ( pComa == NULL )
			{
				executeSkillFailException(pSlayer, getSkillType());
				return;
			}

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// ����Ʈ Ŭ������ ����� ���δ�.
			EffectEternity* pEffect = new EffectEternity(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setHPPenalty(output.Damage);
			pEffect->setBroadcastingEffect(false);
//			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_ETERNITY);

			pZone->registerObject( pEffect );
			pZone->addEffect( pEffect );

			pComa->setDeadline( output.Duration + 10 ); //11��. ��ų �ߵ� ���� ��Ȱ��ġ�� ƨ��°� ����

			// ����ġ�� �ø���.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// ��Ŷ�� ����� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
		
		pSkillSlot->setRunTime(20);	//2��
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Eternity g_Eternity;
