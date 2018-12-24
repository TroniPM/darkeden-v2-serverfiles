//////////////////////////////////////////////////////////////////////////////
// Filename    : BatBreak.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BatBreak.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BatBreak::execute(Vampire * pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		if (pTargetCreature==NULL
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		SkillInput input(pVampire);
		SkillOutput output;
		computeOutput(input, output);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillInfo* pSkillInfo   = g_pSkillInfoManager->getSkillInfo(getSkillType());
		bool       bCriticalHit = false;
		Damage_t   Damage       = 0;
		Damage = output.Damage;

		int  RequiredMP         = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck         = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck        = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bCanHit            = canHit(pVampire, pTargetCreature, getSkillType());

		if (bManaCheck && bTimeCheck && bRangeCheck && bCanHit)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

			ZoneCoord_t X          = pTargetCreature->getX();
			ZoneCoord_t Y          = pTargetCreature->getY();

			VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

		list<Creature*> cList;
		int oX, oY;

		for(oY = -2; oY <= 2; oY++)
		for(oX = -2; oX <= 2; oX++)
		{

			int tileX = X+oX;
			int tileY = Y+oY;
			if (rect.ptInRect(tileX, tileY))
			{

			Tile& tile = pZone->getTile(tileX, tileY);

				list<Creature*> targetList;

				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					targetList.push_back(pCreature);
				}
				if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					targetList.push_back(pCreature);
				}
				if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
					targetList.push_back(pCreature);
				}

		
			list<Creature*>::iterator itr = targetList.begin();
			for(; itr != targetList.end(); itr++)
			{

				Creature* pTargetCreature2 = (*itr);
				Assert(pTargetCreature2 != NULL);

				if (pTargetCreature2 != pVampire)
				{

					bool bPK             = verifyPK(pVampire, pTargetCreature2);
					bool bRaceCheck      = pTargetCreature2->isOusters() || pTargetCreature2->isSlayer() || pTargetCreature2->isMonster();
					bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature2);
					bool bHitRoll           = HitRoll::isSuccess(pVampire, pTargetCreature2);
					bool        bCriticalHit = false;
					Damage_t    Damage       = 0;

					if ( !canAttack( pVampire, pTargetCreature2 )	|| pTargetCreature2->isFlag(Effect::EFFECT_CLASS_COMA) )
					{
						bHitRoll = false; 
					}

					if (bPK && bRaceCheck && bZoneLevelCheck && bHitRoll )
					{
						Damage       = 0;
						bCriticalHit = false;

						Damage += computeDamage(pVampire, pTargetCreature2, 0, bCriticalHit);

						ObjectID_t targetObjectID = pTargetCreature2->getObjectID();
						cList.push_back(pTargetCreature2);

					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature2, pVampire->getX(), pVampire->getY());
					}


					setDamage(pTargetCreature2, Damage, pVampire, getSkillType(), &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
					//computeAlignmentChange(pTargetCreature2, Damage, pVampire, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
					decreaseDurability(pVampire, pTargetCreature2, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);
	
					_GCSkillToObjectOK1.setSkillType(getSkillType());
					_GCSkillToObjectOK1.setCEffectID(CEffectID);
					_GCSkillToObjectOK1.setTargetObjectID(targetObjectID);
					_GCSkillToObjectOK1.setDuration(0);

					_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
					_GCSkillToObjectOK2.setSkillType(getSkillType());
					_GCSkillToObjectOK2.setDuration(0);

					_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
					_GCSkillToObjectOK5.setTargetObjectID(targetObjectID);
					_GCSkillToObjectOK5.setSkillType(getSkillType());

					Player* pTargetPlayer = NULL;
	
					if (pTargetCreature2->isPC()) 
					{
						pTargetPlayer = pTargetCreature2->getPlayer();
						Assert(pTargetPlayer != NULL);
						pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
					} 
					else 
					{
						Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature2);
						pMonster->addEnemy(pVampire);
					}

					list<Creature*> cList;
					cList.push_back(pVampire);
					cList.push_back(pTargetCreature2);
					}
				}
			}
		}
			pZone->broadcastPacket(X, Y, &_GCSkillToObjectOK2, pVampire);
	}
					// 패킷을 보낸다

			pPlayer->sendPacket(&_GCSkillToObjectOK1);



			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature );
		}

	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	__END_CATCH
}

BatBreak g_BatBreak;
