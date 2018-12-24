//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodDrain.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BloodDrain.h"
#include "EffectBloodDrain.h"
#include "EffectPrecedence.h"
#include "EffectDecreaseHP.h"
#include "GQuestManager.h"

#include "Gpackets/GCBloodDrainOK1.h"
#include "Gpackets/GCBloodDrainOK2.h"
#include "Gpackets/GCBloodDrainOK3.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCChangeDarkLight.h"

#include "LogClient.h"
//////////////////////////////////////////////////////////////////////
//
// BloodDrain::execute()
//
//////////////////////////////////////////////////////////////////////
void BloodDrain::execute(Vampire* pVampire, ObjectID_t TargetObjectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;
	Zone* pZone = pVampire->getZone();
	Assert(pZone != NULL);

	Creature* pEnemy = pZone->getCreature(TargetObjectID);

	Assert(pVampire != NULL);
	Assert(pEnemy != NULL);

	bool bSuccess = false;

	try 
	{
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		if (pVampire->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "Monster cannot use skill while hiding." << endl;
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}
		if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pVampire, true);
		}

		// ������ : ���� ���� - -;
		if (pVampire->getSkill(SKILL_BLOOD_DRAIN2))
		{
//			cout << pMonster->getName() << "�� ����������" << endl;
			int x = pVampire->getX();
			int y = pVampire->getY();
			int Splash = 3 + rand()%5; // 3~7 ����
			int range = 5;	// 11 x 11
			list<Creature*> creatureList;
			getSplashVictims(pVampire->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
			
				if (pVampire!=pTargetCreature)
				{
					//cout << "BloodDrain: " << pTargetCreature->getName().c_str() << endl;
					execute(pVampire, pTargetCreature);
				}
			}
		}
		// �Ϲ� �� : �� ����
		else
		{
			execute(pVampire, pEnemy);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void BloodDrain::execute(Vampire* pVampire, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	Assert(pVampire != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pEnemy;
		ObjectID_t TargetObjectID = pTargetCreature->getObjectID();
		//Assert(pTargetCreature != NULL);

		// NPC�� ������ ���� ����.
		// �鿪 ����. by sigi. 2002.9.13
		// �������� üũ. by sigi.2002.9.5
		// ���� �ִ� �� �� �� ����. by Sequoia.2003. 3. 20
		if (pTargetCreature==NULL		// NoSuch ����. by sigi. 2002.5.2
			|| pTargetCreature->isNPC()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN)
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)
			|| pTargetCreature->isDead()
		)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;
			return;
		}

		GCBloodDrainOK1 _GCBloodDrainOK1;
		GCBloodDrainOK2 _GCBloodDrainOK2;
		GCBloodDrainOK3 _GCBloodDrainOK3;

		Timeval CurrentTime;
		getCurrentTime(CurrentTime);

		bool bHitRoll    = HitRoll::isSuccessBloodDrain(pVampire, pTargetCreature);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SKILL_BLOOD_DRAIN);
		bool bTimeCheck  = CurrentTime.tv_sec > 1 ? true : false;
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, 2);
		bool bPK         = verifyPK(pVampire, pTargetCreature);

		if (bHitRoll && bCanHit && bTimeCheck && bRangeCheck && bPK)
		{
			// �����̾��� ��쿡�� ����Ʈ ������Ʈ�� �����Ѵ�.
			if (pTargetCreature->isSlayer())
			{
				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pTargetCreature);
				pEffectBloodDrain->setLevel(pVampire->getLevel());
				pEffectBloodDrain->setDeadline(BLOODDRAIN_DURATION);	// 3��??
				pTargetCreature->addEffect(pEffectBloodDrain);
				pEffectBloodDrain->create(pTargetCreature->getName());
				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);

				// Ÿ���� ���� �÷��״� �Ǵ�.
				pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCBloodDrainOK2);

				// �α׸� �����.
				log(LOG_BLOODDRAINED, pTargetCreature->getName(), pVampire->getName());
			}
			// �ƿ콺������ ��쿣..... -_-; ���ѽð� ���� ����Ʈ�� �����Ѵ�. ������ ���� ���ѽð��� ���� �� �ƴ�����..
//			else if ( pTargetCreature->isOusters() )
//			{
//				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pTargetCreature);
//				pEffectBloodDrain->setLevel(pVampire->getLevel());
//				pTargetCreature->addEffect(pEffectBloodDrain);
//				pEffectBloodDrain->create(pTargetCreature->getName());
//				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//				// Ÿ���� ���� �÷��״� �Ǵ�.
//				pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//				Sight_t oldSight = pTargetCreature->getSight();
//				Sight_t newSight = pTargetCreature->getEffectedSight();
//
//				if ( oldSight != newSight )
//				{
//					pTargetCreature->setSight(newSight);
//					pZone->updateScan(pTargetCreature, oldSight, pTargetCreature->getSight());
//					_GCBloodDrainOK2.addShortData(MODIFY_VISION, pTargetCreature->getSight());
//
//					GCChangeDarkLight gcChangeDarkLight;
//					gcChangeDarkLight.setDarkLevel(15);
//					gcChangeDarkLight.setLightLevel(newSight);
//					pTargetCreature->getPlayer()->sendPacket(&gcChangeDarkLight);
//				}
//			}

			// Ÿ���� ���� �÷��״� �Ǵ�.
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			
			// �ø� ����ġ���� ����Ѵ�.
			Exp_t Exp = computeCreatureExp(pTargetCreature, BLOODDRAIN_EXP);

			int targetLevel = 0;
			int targetMaxHP = 0;
			// ������ �÷��ش�.
			if (pTargetCreature->isSlayer()) 
			{
				//increaseFame(pVampire, Exp);
				Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pTargetCreature);
				targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
				targetMaxHP = pTargetSlayer->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isVampire()) 
			{
				//increaseFame(pVampire, Exp);
				Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pTargetCreature);
				targetLevel = pTargetVampire->getLevel();
				targetMaxHP = pTargetVampire->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isOusters()) 
			{
				//increaseFame(pOusters, Exp);
				Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pTargetCreature);
				targetLevel = pTargetOusters->getLevel();
				targetMaxHP = pTargetOusters->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);

				Timeval NextTurn = pMonster->getNextTurn();
				Timeval DelayTurn;
				DelayTurn.tv_sec = 4;
				DelayTurn.tv_usec = 500000;
				pMonster->addAccuDelay(DelayTurn);
				pMonster->addEnemy(pVampire);

				targetLevel = pMonster->getLevel();
				targetMaxHP = pMonster->getHP(ATTR_MAX);
			}

			shareVampExp(pVampire, Exp, _GCBloodDrainOK1);

			// ������ �ϰ� �Ǹ� ������ ����� ü���� �ö󰣴�.
			// Mephisto����Ʈ�� �ɷ������� HP�� �� �ö󰣴�.
			if (!pVampire->isFlag(Effect::EFFECT_CLASS_MEPHISTO))
			{
				HP_t HealPoint = (Exp==0? computeBloodDrainHealPoint(pTargetCreature, BLOODDRAIN_EXP) : Exp);
				HP_t CurrentHP = pVampire->getHP();
				HP_t MaxHP	   = pVampire->getHP(ATTR_MAX);
				HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + (int)HealPoint);

				// �� ������ ���� ó���� �� �ش�.
				Silver_t newSilverDamage = max(0, (int)pVampire->getSilverDamage()-(int)HealPoint);
				pVampire->saveSilverDamage(newSilverDamage);
				_GCBloodDrainOK1.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);

				// �����̾��� HP�� �����Ѵ�.
				pVampire->setHP(NewHP);

				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(NewHP);
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);

				_GCBloodDrainOK1.addShortData(MODIFY_CURRENT_HP, NewHP);
			}

			// ������ ���� �ִ� HP�� �پ���.
			// ����� �� �������� ���ٸ�.. MaxHP�� 10~15% damage
			// by sigi. 2002.9.14
			int drainDamage = 0;
			int myLevel = pVampire->getLevel();

			if (targetLevel > myLevel)
			{
				drainDamage = targetMaxHP * (rand()%6+10) / 100;
			}
			else
			{
				// ���� 5���̸��� 1%�� ��~
				int damagePercent = min(30, (rand()%6+10+(myLevel-targetLevel)));
				drainDamage = targetMaxHP * damagePercent / 100;
			}
			
			if (drainDamage > 0)
			{
				//decreaseHP(pZone, pTargetCreature, drainDamage, pVampire->getObjectID()); 
				EffectDecreaseHP* pEffect = new EffectDecreaseHP(pTargetCreature);
				pEffect->setPoint(drainDamage);
				pEffect->setDeadline( 20 );	// 2�� ��
				pEffect->setUserObjectID( pVampire->getObjectID() );
				pTargetCreature->addEffect(pEffect);
				pTargetCreature->setFlag(Effect::EFFECT_CLASS_DECREASE_HP);
			}

			pVampire->getGQuestManager()->blooddrain();

			// �����ÿ��� ���� �ٲ�
			// by sigi. 2002.12.16
			// EffectDecreaseHP���� HP�� ��Ƽ� 0�� �Ǿ���ϴ� ��찡 �־ 
			// EffectDecreaseHP::unaffect()�� �ű��.
			//computeAlignmentChange(pTargetCreature, drainDamage, pVampire, NULL, &_GCBloodDrainOK1);

			_GCBloodDrainOK1.setObjectID(TargetObjectID);

			_GCBloodDrainOK3.setObjectID(pVampire->getObjectID());
			_GCBloodDrainOK3.setTargetObjectID (TargetObjectID);

			pPlayer->sendPacket(&_GCBloodDrainOK1);

			if (pTargetCreature != NULL && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();

				if (pTargetPlayer != NULL) 
				{ 
					_GCBloodDrainOK2.setObjectID(pVampire->getObjectID());
					_GCBloodDrainOK2.addLongData(MODIFY_DURATION, BLOODDRAIN_DURATION);
					pTargetPlayer->sendPacket(&_GCBloodDrainOK2);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCBloodDrainOK3 , cList);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH

}


//////////////////////////////////////////////////////////////////////
//
// BloodDrain::execute()
//
//////////////////////////////////////////////////////////////////////
void BloodDrain::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	bool bSuccess = false;

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

		// ������ : ���� ���� - -;
		if (pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
		)
		{
//			cout << pMonster->getName() << "�� ����������" << endl;
			int x = pMonster->getX();
			int y = pMonster->getY();
			int Splash = 3 + rand()%5; // 3~7 ����
			int range = 5;	// 11 x 11
			list<Creature*> creatureList;
			getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
			
				if (pMonster!=pTargetCreature)
				{
					//cout << "BloodDrain: " << pTargetCreature->getName().c_str() << endl;
					executeMonster(pMonster, pTargetCreature);
				}
			}
		}
		// �Ϲ� �� : �� ����
		else
		{
			if (executeMonster(pMonster, pEnemy))
			{
				bSuccess = true;
			}
			else 
			{
				executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
			}
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	// �����̵� ���е� ���Ϳ��� �����̴� �ɾ��ش�.
	Timeval NextTurn = pMonster->getNextTurn();
	Timeval DelayTurn;
	DelayTurn.tv_sec = (bSuccess? 4 : 1);	// ������ ������ delay�� �ٸ��� �Ѵ�. by sigi. 2002.9.14
	DelayTurn.tv_usec = 500000;
	pMonster->addAccuDelay(DelayTurn);


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

bool BloodDrain::executeMonster(Monster* pMonster, Creature* pEnemy)
	throw (Error)
{
	__BEGIN_TRY

	bool isMaster    = pMonster->isMaster()
#ifdef __UNDERWORLD__
	|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
	;

	// �׾����� ���� ���ϰ�..
	// �����ʹ� �ƹ��� �� ���� - -;
	// ����� �׾����� �� ����.
	if (pMonster->isDead()
		|| pMonster->isFlag(Effect::EFFECT_CLASS_COMA)
		|| !pMonster->isEnemyToAttack(pEnemy) && !isMaster
		|| pEnemy->isDead() || pEnemy->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		return false;
	}

	Zone* pZone = pMonster->getZone();
	Assert(pZone != NULL);

	GCBloodDrainOK1 _GCBloodDrainOK1;
	GCBloodDrainOK2 _GCBloodDrainOK2;
	GCBloodDrainOK3 _GCBloodDrainOK3;

	// �����ʹ� ü�� 100% �� ����.
	int HPMultiplier = (isMaster? 1 : 3);	// ���� HP�� 1/1,  1/3
	bool bHitRoll    = HitRoll::isSuccessBloodDrain(pMonster, pEnemy, HPMultiplier);
	bool bCanHit     = canHit(pMonster, pEnemy, SKILL_BLOOD_DRAIN);
	// �����ʹ� �Ÿ��� ������� ����~
	bool bRangeCheck = isMaster || verifyDistance(pMonster, pEnemy, 1);

	// ���� �鿪 ����. by sigi. 2002.9.13
	bool bEffected = pEnemy->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN);

	if (bHitRoll && bCanHit && bRangeCheck && !bEffected)
	{
		if (pEnemy->isSlayer())
		{
			// Set EffectBloodDrain
			// �����͸� �ȰǴ�.
			if (!isMaster)
			{
				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pEnemy);
				pEffectBloodDrain->setLevel(pMonster->getLevel());
				pEffectBloodDrain->setDeadline(BLOODDRAIN_DURATION);	// ���ӽð����� 3�� ����
				pEnemy->addEffect(pEffectBloodDrain);
				pEffectBloodDrain->create(pEnemy->getName());
				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);

				pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pEnemy);
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCBloodDrainOK2);
			}

			// �α׸� �����.
			log(LOG_BLOODDRAINED, pEnemy->getName(), "���� ���� ����");
		}
		// �ƿ콺������ ��쿣..... -_-; ���ѽð� ���� ����Ʈ�� �����Ѵ�. ������ ���� ���ѽð��� ���� �� �ƴ�����..
//		else if ( pEnemy->isOusters() && !isMaster )
//		{
//			EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pEnemy);
//			pEffectBloodDrain->setLevel(pMonster->getLevel());
//			pEnemy->addEffect(pEffectBloodDrain);
//			pEffectBloodDrain->create(pEnemy->getName());
//			_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//			pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//			Sight_t oldSight = pEnemy->getSight();
//			Sight_t newSight = pEnemy->getEffectedSight();
//
//			if ( oldSight != newSight )
//			{
//				pEnemy->setSight(newSight);
//				pZone->updateScan(pEnemy, oldSight, pEnemy->getSight());
//				_GCBloodDrainOK2.addShortData(MODIFY_VISION, pEnemy->getSight());
//
//				GCChangeDarkLight gcChangeDarkLight;
//				gcChangeDarkLight.setDarkLevel(15);
//				gcChangeDarkLight.setLightLevel(newSight);
//				pEnemy->getPlayer()->sendPacket(&gcChangeDarkLight);
//			}
//		}


		_GCBloodDrainOK3.setObjectID(pMonster->getObjectID());
		_GCBloodDrainOK3.setTargetObjectID (pEnemy->getObjectID());

		// Ÿ���� ���� �÷��״� �Ǵ�.
		// �����͸� �ȰǴ�.
		if (!isMaster)
		{
			pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		}

		if (pEnemy != NULL && pEnemy->isPC()) 
		{
			Player* pTargetPlayer = pEnemy->getPlayer();
			if (pTargetPlayer != NULL) 
			{ 
				_GCBloodDrainOK2.setObjectID(pMonster->getObjectID());
	
				if (!isMaster)
				{
					_GCBloodDrainOK2.addLongData(MODIFY_DURATION, BLOODDRAIN_DURATION);
				}
				pTargetPlayer->sendPacket(&_GCBloodDrainOK2);
			}
		}

		// target
		int targetLevel = 0;
		int targetMaxHP = 0;

		if (pEnemy->isSlayer()) 
		{
			Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pEnemy);
			targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
			targetMaxHP = pTargetSlayer->getHP(ATTR_MAX);
		}
		else if (pEnemy->isVampire()) 
		{
			Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pEnemy);
			targetLevel = pTargetVampire->getLevel();
			targetMaxHP = pTargetVampire->getHP(ATTR_MAX);
		}
		else if (pEnemy->isOusters()) 
		{
			Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pEnemy);
			targetLevel = pTargetOusters->getLevel();
			targetMaxHP = pTargetOusters->getHP(ATTR_MAX);
		}
		else if (pEnemy->isMonster())
		{
			Monster* pEnemyMonster = dynamic_cast<Monster*>(pEnemy);

			// �������ϴ� �������� ������ �ɾ��ش�.
			Timeval DelayTurn;
			DelayTurn.tv_sec = 4;
			DelayTurn.tv_usec = 500000;
			pEnemyMonster->addAccuDelay(DelayTurn);

			if ( ( pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599 
#endif
			)
				&& pMonster->getClanType()==pEnemyMonster->getClanType())
			{
				// ���� clan�� �������̸� �� ���̶�� �� �� ������ -_-;
			}
			else
			{
				pEnemyMonster->addEnemy(pMonster);
			}

			targetLevel = pEnemyMonster->getLevel();
			targetMaxHP = pEnemyMonster->getHP(ATTR_MAX);
		}

		// �ڽ��̳� ���� ��.. HP�� ���� ���� 15~25%
		HP_t maxHP = max((int)pMonster->getHP(ATTR_MAX), targetMaxHP);
		HP_t drainHP = maxHP*(rand()%11+15)/100; // 15~25%

		// �ѹ��� 1000�̻� �� ����.
		if ( pMonster->getMonsterType() >= 717 )
			drainHP = min((int)drainHP, 2000);
		else
			drainHP = min((int)drainHP, 1000);

		// ������ HP�� �÷��ش�.
		HP_t CurrentHP = pMonster->getHP();
		HP_t MaxHP	   = pMonster->getHP(ATTR_MAX);
		HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + (int)drainHP);

		// �����̾��� HP�� �����Ѵ�.
		pMonster->setHP(NewHP);

		GCStatusCurrentHP gcStatusCurrentHP;
		gcStatusCurrentHP.setObjectID(pMonster->getObjectID());
		gcStatusCurrentHP.setCurrentHP(NewHP);
		pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &gcStatusCurrentHP);

		// ���� ���� ���� HP�� ���δ�.
		// ����� �� �������� ���ٸ�.. MaxHP�� 10~15% damage
		// by sigi. 2002.9.14
		int drainDamage = 0;
		int myLevel = pMonster->getLevel();

		if (targetLevel > myLevel)
		{
			drainDamage = targetMaxHP * (rand()%6+10) / 100;
		}
		else
		{
			// ���� 5���̸��� 1%�� ��~
			int damagePercent = min(30, (rand()%6+10+(myLevel-targetLevel)));
			drainDamage = targetMaxHP * damagePercent / 100;
		}
		
		if (drainDamage > 0)
		{
			//decreaseHP(pZone, pEnemy, drainDamage);
			EffectDecreaseHP* pEffect = new EffectDecreaseHP(pEnemy);
			pEffect->setPoint(drainDamage);
			pEffect->setDeadline( 20 );	// 2�� ��
			pEffect->setUserObjectID( pMonster->getObjectID() );
			pEnemy->addEffect(pEffect);
			pEnemy->setFlag(Effect::EFFECT_CLASS_DECREASE_HP);
		}

		// ���� ��� ���̰�..
		list<Creature *> cList;
		cList.push_back(pEnemy);
		cList.push_back(pMonster);
		pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &_GCBloodDrainOK3 , cList);

		// ���� ����
		return true;
	}

	__END_CATCH

	return false;
}

BloodDrain g_BloodDrain;
