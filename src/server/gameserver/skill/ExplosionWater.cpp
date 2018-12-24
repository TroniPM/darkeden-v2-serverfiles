//////////////////////////////////////////////////////////////////////////////
// Filename    : ExplosionWater.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ExplosionWater.h"
#include "EffectExplosionWater.h"

#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void ExplosionWater::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);
	int Grade = 0;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			return;
		}

		if ( pTargetCreature->isMonster() )
		{
			Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
			if ( pMonster != NULL && pMonster->isMaster() )
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature, Grade);
				return;
			}
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			return;
		}

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());

		int  RequiredMP         = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3;
		bool bManaCheck         = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck        = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bCanHit            = canHit(pOusters, pTargetCreature, getSkillType());
		bool bPK                = verifyPK(pOusters, pTargetCreature);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && bSatisfyRequire )
		{
            decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

			ZoneCoord_t X   = pOusters->getX();
			ZoneCoord_t Y   = pOusters->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Damage_t Damage = output.Damage;

			bool dummy;
			computeCriticalBonus(pOusters, getSkillType(), Damage, dummy);

			bool bCanSeeCaster = canSee(pTargetCreature, pOusters);
			if (bCanSeeCaster) 
			{
				setDamage(pTargetCreature, Damage, pOusters, getSkillType(), &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				decreaseDurability(pOusters, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);
			}
			else
			{
				setDamage(pTargetCreature, Damage, pOusters, getSkillType(), &_GCSkillToObjectOK6, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCSkillToObjectOK6, &_GCSkillToObjectOK1);
				decreaseDurability(pOusters, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK6);
			}

			EffectExplosionWater* pEffect = new EffectExplosionWater( pTargetCreature );
			pEffect->setDamageReduce( output.Tick );
			pEffect->setDeadline( output.Duration );
			pTargetCreature->setFlag( pEffect->getEffectClass() );
			pTargetCreature->addEffect( pEffect );

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
			gcAddEffect.setEffectID( pEffect->getEffectClass() );
			gcAddEffect.setDuration( output.Duration );
			
			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );

			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, _GCSkillToObjectOK1);
			}

			increaseAlignment(pOusters, pTargetCreature, _GCSkillToObjectOK1);

			_GCSkillToObjectOK1.setSkillType(getSkillType());
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			_GCSkillToObjectOK1.setGrade(Grade);
			_GCSkillToObjectOK1.setDuration(output.Duration);
		
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(getSkillType());
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.setGrade(Grade);
			_GCSkillToObjectOK2.setDuration(output.Duration);
			
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(getSkillType());
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
			_GCSkillToObjectOK3.setGrade(Grade);
		
			_GCSkillToObjectOK4.setSkillType(getSkillType());
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setGrade(Grade);
			_GCSkillToObjectOK4.setDuration(output.Duration);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(getSkillType());
			_GCSkillToObjectOK5.setGrade(Grade);
			_GCSkillToObjectOK5.setDuration(output.Duration);
			
			_GCSkillToObjectOK6.setXY(X, Y);
			_GCSkillToObjectOK6.setSkillType(getSkillType());
			_GCSkillToObjectOK6.setDuration(0);
			_GCSkillToObjectOK6.setGrade(Grade);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			Player* pTargetPlayer = NULL;
			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pOusters);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(X, Y, targetX, targetY, &_GCSkillToObjectOK5, cList);
			
			pZone->broadcastPacket(X, Y,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
		}
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature, Grade);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// ���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void ExplosionWater::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "Monster cannot use skill while hiding." << endl;
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		if (pMonster->isMaster())
		{
			int x = pMonster->getX();
			int y = pMonster->getY();
			int Splash = 3 + rand()%5; // 3~7 ����
			int range = 2;	// 5x5
			list<Creature*> creatureList;
			getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
			
				if (pMonster!=pTargetCreature)
					executeMonster(pZone, pMonster, pTargetCreature);
			}
		}
		else
		{
			executeMonster(pZone, pMonster, pEnemy);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void ExplosionWater::executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);
	int Grade = 0;

	try 
	{
		Assert(pZone != NULL);

		Creature* pTargetCreature = pEnemy;

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pMonster, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pMonster, getSkillType(), Grade);
			return;
		}

		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
		bool bRangeCheck        = verifyDistance(pMonster, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bCanHit            = canHit(pMonster, pTargetCreature, getSkillType());

		if (bRangeCheck && bHitRoll && bCanHit)
		{

			ZoneCoord_t X   = pMonster->getX();
			ZoneCoord_t Y   = pMonster->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			Damage_t Damage = output.Damage;

			//computeCriticalBonus(pOusters, getSkillType(), Damage, dummy);

			EffectExplosionWater* pEffect = new EffectExplosionWater( pTargetCreature );
			pEffect->setDamageReduce( output.Tick );
			pEffect->setDeadline( output.Duration );
			pTargetCreature->setFlag( pEffect->getEffectClass() );
			pTargetCreature->addEffect( pEffect );

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
			gcAddEffect.setEffectID( pEffect->getEffectClass() );
			gcAddEffect.setDuration( output.Duration );
			
			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
		
			_GCSkillToObjectOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK2.setSkillType(getSkillType());
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.setGrade(Grade);
			_GCSkillToObjectOK2.setDuration(output.Duration);
			
			_GCSkillToObjectOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK3.setSkillType(getSkillType());
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
			_GCSkillToObjectOK3.setGrade(Grade);
		
			_GCSkillToObjectOK4.setSkillType(getSkillType());
			_GCSkillToObjectOK4.setTargetObjectID(pTargetCreature->getObjectID());
			_GCSkillToObjectOK4.setGrade(Grade);
			_GCSkillToObjectOK4.setDuration(output.Duration);

			_GCSkillToObjectOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(pTargetCreature->getObjectID());
			_GCSkillToObjectOK5.setSkillType(getSkillType());
			_GCSkillToObjectOK5.setGrade(Grade);
			_GCSkillToObjectOK5.setDuration(output.Duration);
			
			_GCSkillToObjectOK6.setXY(X, Y);
			_GCSkillToObjectOK6.setSkillType(getSkillType());
			_GCSkillToObjectOK6.setDuration(0);
			_GCSkillToObjectOK6.setGrade(Grade);
			_GCSkillToObjectOK6.setDuration(output.Duration);
		
			Player* pTargetPlayer = NULL;
			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pMonster);
			}

			list<Creature*> cList;
			cList.push_back(pMonster);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(X, Y, targetX, targetY, &_GCSkillToObjectOK5, cList);
			
			pZone->broadcastPacket(X, Y,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);
		}
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), pTargetCreature, Grade);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType(), Grade);
	}

	__END_CATCH
}

ExplosionWater g_ExplosionWater;

