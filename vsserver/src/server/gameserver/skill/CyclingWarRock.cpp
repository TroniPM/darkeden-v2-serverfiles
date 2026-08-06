//////////////////////////////////////////////////////////////////////////////
// Filename    : RingOfFlare.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CyclingWarRock.h"
#include "EffectCyclingWarRock.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCOtherModifyInfo.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void CyclingWarRock::execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		//SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/2;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bEffected   = pOusters->isFlag(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);
		bool bEffected2   = pOusters->isFlag(Effect::EFFECT_CLASS_RING_OF_FLARE);
		bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && !bEffected2 && bSatisfyRequire)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			//cout << pOusters->getName() << "이 CyclingWarRock를 썼고 데미지는 " << output.Damage << "입니다." << endl;

			// 이팩트 클래스를 만들어 붙인다.
			EffectCyclingWarRock* pEffect = new EffectCyclingWarRock(pOusters);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);
			pEffect->setNextTime(0);
			pEffect->setSendEffectClass( Effect::EFFECT_CLASS_CYCLING_WAR_ROCK );

			pOusters->addEffect(pEffect);
			pOusters->setFlag(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
			_GCSkillToSelfOK1.setGrade(Grade);
		
			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
			_GCSkillToSelfOK2.setGrade(Grade);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToSelfOK2, pOusters);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pOusters->getObjectID());
			gcAddEffect.setEffectID(pEffect->getSendEffectClass());
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void CyclingWarRock::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(Oustersobject)" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// 슬레이어가 아니라면 사용할 수가 없다.
		if (pTargetCreature==NULL		// NoSuch 제거. by sigi. 2002.5.2
			|| !pTargetCreature->isOusters())
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(Oustersobject)" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bEffected   = pTargetOusters->isFlag(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);
		bool bEffected2   = pTargetOusters->isFlag(Effect::EFFECT_CLASS_RING_OF_FLARE);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && !bEffected2)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

			// 기술의 효과치 및 지속시간을 계산한다.
			SkillInput input(pOusters, pOustersSkillSlot);
			input.TargetType = SkillInput::TARGET_OTHER;
			SkillOutput output;
			computeOutput(input, output);

			// 이팩트 클래스를 만들어 붙인다.
			EffectCyclingWarRock* pEffect = new EffectCyclingWarRock(pTargetOusters);
			output.Damage = getPercentValue(output.Damage, 60);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);
			pEffect->setNextTime(0);
			pEffect->setSendEffectClass( Effect::EFFECT_CLASS_CYCLING_WAR_ROCK );

			pOusters->addEffect(pEffect);
			pOusters->setFlag(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);
			
			Coord_t targetX = pTargetCreature->getX();
			Coord_t targetY = pTargetCreature->getY();
			Coord_t myX     = pOusters->getX();
			Coord_t myY     = pOusters->getY();

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
		
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(0);
		
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setDuration(0);
			
			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(0);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);
			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);

				_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());

				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else
			{
				Assert(false);
			}
		
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(TargetObjectID);
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_CYCLING_WAR_ROCK);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
			
			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}

	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(Oustersobject)" << endl;

	__END_CATCH
}

CyclingWarRock g_CyclingWarRock;
