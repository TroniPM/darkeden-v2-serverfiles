//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeWalk.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ShadyDouple.h"
#include "EffectShadyDouple.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void ShadyDouple::execute(Vampire * pVampire, ObjectID_t TargetObjectID, VampireSkillSlot * pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// 무장하고 있는 무기가 널이거나, 검이 아니라면 기술을 사용할 수 없다.
		Item* pItem = pVampire->getWearItem(Vampire::WEAR_RIGHTHAND);
		if (pItem == NULL)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bCanHit     = canHit(pVampire, pTargetCreature, SkillType);
		bool bPK         = verifyPK(pVampire, pTargetCreature);
		bool bEffected	 = pVampire->hasRelicItem();

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected )
		{
			// 빠르게 PC를 움직여준다.
				decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

				SkillInput input(pVampire);
				SkillOutput output;
				computeOutput(input, output);

				bool bCriticalHit = false;

				// 데미지를 준다.
				Damage_t BasicDamage = computeDamage(pVampire, pTargetCreature, 100/5, bCriticalHit);
				Damage_t Damage = BasicDamage + output.Damage;
				setDamage(pTargetCreature, Damage, pVampire, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pVampire, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				decreaseDurability( pVampire, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2 );

				// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
				if (bCriticalHit)
				{
					knockbackCreature(pZone, pTargetCreature, pVampire->getX(), pVampire->getY());
				}

				if (!pTargetCreature->isVampire())
				{
					increaseAlignment(pVampire, pTargetCreature, _GCSkillToObjectOK1);
				}

				int AttackNum = 0;

				AttackNum = 3;

				EffectShadyDouple* pEffect = new EffectShadyDouple( pTargetCreature );
				pEffect->setPoint( 10 + 100/5 );
				pEffect->setUserObjectID( pVampire->getObjectID() );
				pEffect->setAttackNum( AttackNum );
				pEffect->setNextTime(5);
				pTargetCreature->setFlag( Effect::EFFECT_CLASS_SHADY_DOUPLE );
				pTargetCreature->addEffect( pEffect );

				// 패킷을 준비하고 보낸다.
				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);
				_GCSkillToObjectOK1.setGrade( AttackNum );

				_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(0);
				_GCSkillToObjectOK2.setGrade( AttackNum );

				_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
				_GCSkillToObjectOK3.setSkillType(getSkillType());
				_GCSkillToObjectOK3.setTargetXY(pTargetCreature->getX(), pTargetCreature->getY());
				_GCSkillToObjectOK3.setGrade( AttackNum );
			
				_GCSkillToObjectOK4.setSkillType(getSkillType());
				_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK4.setGrade( AttackNum );

				_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
				_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK5.setSkillType(getSkillType());
				_GCSkillToObjectOK5.setDuration(0);
				_GCSkillToObjectOK5.setGrade( AttackNum );
				
				pPlayer->sendPacket(&_GCSkillToObjectOK1);

				if (pTargetCreature->isPC()) 
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				} 
				else 
				{
					Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pVampire);
				}

				list<Creature*> cList;
				cList.push_back(pVampire);
				cList.push_back(pTargetCreature);

				cList = pZone->broadcastSkillPacket(pVampire->getX(), pVampire->getY(), pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToObjectOK5, cList);
				
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCSkillToObjectOK3 , cList);
				pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(),  &_GCSkillToObjectOK4 , cList);

				pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ShadyDouple g_ShadyDouple;
