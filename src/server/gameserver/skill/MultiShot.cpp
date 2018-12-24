//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiShot.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MultiShot.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "ItemUtil.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// ������ - ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
MultiShot::MultiShot()
	throw()
{
	__BEGIN_TRY

	// SG ����ũ�� ������� ������� �׻� + ����̴�.
	m_pSGMask[0].set(-1, -1);
	m_pSGMask[1].set(0, -1);
	m_pSGMask[2].set(1, -1);
	m_pSGMask[3].set(-1,  0);
	m_pSGMask[4].set(0,  0);
	m_pSGMask[5].set(1,  0);
	m_pSGMask[6].set(-1,  1);
	m_pSGMask[7].set(0,  1);
	m_pSGMask[8].set(1,  1);

	// AR ����ũ�� �ʱ�ȭ��Ų��.
	// SwordWave�� ���������, SwordWave�� ������ ������ 
	// ����ũ�� �̿��� �˻�������. MultiShot�� Ÿ���� ������ ����ũ��
	// �̿��� �˻��Ѵٴ� ���� �����ؾ� �Ѵ�.
	//
	// (-1,-1)(0,-1)(1,-1)
	// (-1, 0)(0, 0)(1, 0)
	// (-1, 1)(0, 1)(1, 1)
	//
	// �� ���⿡ ���� ��� Ÿ���� ���� ����̳ĸ�
	// �����ϸ� ����ũ�� �����ϱ� ����.

	m_pARMask[LEFT][0].set(0,-1);
	m_pARMask[LEFT][1].set(0, 0);
	m_pARMask[LEFT][2].set(0, 1);

	m_pARMask[RIGHT][0].set(0,-1);
	m_pARMask[RIGHT][1].set(0, 0);
	m_pARMask[RIGHT][2].set(0, 1);

	m_pARMask[UP][0].set(-1,0);
	m_pARMask[UP][1].set(0,0);
	m_pARMask[UP][2].set(1,0);

	m_pARMask[DOWN][0].set(-1,0);
	m_pARMask[DOWN][1].set(0,0);
	m_pARMask[DOWN][2].set(1,0);

	m_pARMask[LEFTUP][0].set(1,-1);
	m_pARMask[LEFTUP][1].set(0, 0);
	m_pARMask[LEFTUP][2].set(-1, 1);

	m_pARMask[RIGHTDOWN][0].set(1,-1);
	m_pARMask[RIGHTDOWN][1].set(0, 0);
	m_pARMask[RIGHTDOWN][2].set(-1, 1);

	m_pARMask[LEFTDOWN][0].set(-1,-1);
	m_pARMask[LEFTDOWN][1].set(0, 0);
	m_pARMask[LEFTDOWN][2].set(1, 1);

	m_pARMask[RIGHTUP][0].set(-1,-1);
	m_pARMask[RIGHTUP][1].set(0, 0);
	m_pARMask[RIGHTUP][2].set(1, 1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void MultiShot::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		// �������� ���ų�, �� �迭�� ���Ⱑ �ƴϰų�, SR�̶��
		// �� ����� ����� �� ����.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL 
			|| !isArmsWeapon(pItem))
			// SR�� ��� �����ϰ� ����. by sigi. 2002.12.3
			//	|| pItem->getItemClass() == Item::ITEM_CLASS_SR)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		Item::ItemClass IClass = pItem->getItemClass();
		if (IClass == Item::ITEM_CLASS_SG) 
		{
			SGexecute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
		} 
		else if (IClass == Item::ITEM_CLASS_AR 
				|| IClass == Item::ITEM_CLASS_SMG
				// SR�� ��� �����ϰ� ����. by sigi. 2002.12.3
				|| IClass == Item::ITEM_CLASS_SR) 
		{
			ARSMGexecute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void MultiShot::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		// �������� ���ų�, �� �迭�� ���Ⱑ �ƴϰų�, SR�̶��
		// �� ����� ����� �� ����.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL 
			|| !isArmsWeapon(pItem))
			// SR�� ��� �����ϰ� ����. by sigi. 2002.12.3
			//|| pItem->getItemClass() == Item::ITEM_CLASS_SR)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		Item::ItemClass IClass = pItem->getItemClass();
		if (IClass == Item::ITEM_CLASS_SG) 
		{
			SGexecute(pSlayer, X, Y, pSkillSlot, CEffectID);
		} 
		else if (IClass == Item::ITEM_CLASS_AR 
				|| IClass == Item::ITEM_CLASS_SMG
				// SR�� ��� �����ϰ� ����. by sigi. 2002.12.3
				|| IClass == Item::ITEM_CLASS_SR) 
		{
			ARSMGexecute(pSlayer, X, Y, pSkillSlot, CEffectID);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯 - SG�� ��� ���� ���
//////////////////////////////////////////////////////////////////////////////
void MultiShot::SGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute  Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 	      SkillLevel = pSkillSlot->getExpLevel();

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		Assert(pWeapon != NULL);

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
 
		int  RequiredMP   = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, X, Y, pWeapon->getRange());
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// �Ѿ� ���� ������ ����߸���.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// �ѹ߾������� ������ �ʿ� ����. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// ������, ���� ���ʽ�, ��ǥ�� ������ ���Ѵ�.
		int         ToHitBonus    = 0;
		int         DamageBonus   = 0;
		int         ToHitPenalty  = 0;
		int         DamagePenalty = 0;
		ZoneCoord_t myX           = pSlayer->getX();
		ZoneCoord_t myY           = pSlayer->getY();	
		Dir_t       dir           = calcDirection(myX, myY, X, Y);
		bool        bHit          = false; // �ѹ��̶� �¾Ҵ°��� �����ϱ� ���� ����
		Damage_t    Damage        = 0;     // ���������� ���� �������� �����ϱ� ���� ����

		// SG�� ��쿡�� 4���� �����ؼ� 9������ splash �������� ������.
		int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

		if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// output.ToHit���� �����̱� ������, %���� ������ ���ƿ´�.
			ToHitPenalty = getPercentValue(pSlayer->getToHit(), output.ToHit);

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());
				DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());

				bool bInvokerCheck   = (pTargetCreature->getObjectID() == pSlayer->getObjectID()) ? true : false;
				bool bRaceCheck      = pTargetCreature->isSlayer() || pTargetCreature->isNPC();
				bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty + ToHitBonus);
				bool bPK             = verifyPK(pSlayer, pTargetCreature);
				bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

				if ( !canAttack( pSlayer, pTargetCreature )
					|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				)
				{
					bHitRoll = false;
				}

				if (!bInvokerCheck && !bRaceCheck && bHitRoll && bPK && bZoneLevelCheck)
				{
					bool bCriticalHit = false;

					// �������� ����ؼ� ���Ƽ�� ���Ѵ�.
					// ���ʽ��� ��Ƽ�� ���Ƽ ������ ������ �� ���� �ִ�.
					Damage        = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
					DamagePenalty = getPercentValue(Damage, output.Damage);
					Damage        = max(0, Damage + DamagePenalty + DamageBonus);

					// ���� Ÿ���� �����ϰ��, ���÷��� �������� �Դµ�,
					// ���÷��� �������� �Ϲ� �������� 50%��.
					if (pTargetCreature->getX() != X || pTargetCreature->getY() != Y)
					{
						Damage = Damage/2;
					}

					// �ҵ���̺�ʹ� �޸� ũ�ν� ī���� üũ�� ���� �ʴ´�.
					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					cList.push_back(pTargetCreature);
					_GCSkillToTileOK1.addCListElement(targetObjectID);
					_GCSkillToTileOK2.addCListElement(targetObjectID);
					_GCSkillToTileOK5.addCListElement(targetObjectID);
					
					setDamage(pTargetCreature, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
					computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

					// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature, myX, myY);
					}

					// �����̾� �ƴ� ��쿡�� hit�� �ɷ� �����Ѵ�.
					if (!pTargetCreature->isSlayer())
					{
						bHit = true;
						if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
						EnemyNum++;
					}
				}
			}

			if (bHit)
			{
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

			// �Ѿ� ���ڸ� ���̰�, �Ѿ� ���ڸ� �����ϰ�, ���� �Ѿ� ���ڸ� ���� ������ �������� ����߸���.
			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(getSkillType());
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(getSkillType());
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(getSkillType());
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP();
					}

					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// �������� �������� ����߸���.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// ��Ŷ�� �����ش�.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// ��� ������ �ν��Ѵ�.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯 - AR�̳� SMG�� ��� ���� ���
//////////////////////////////////////////////////////////////////////////////
void MultiShot::ARSMGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute  Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 	      SkillLevel = pSkillSlot->getExpLevel();

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		Assert(pWeapon != NULL);

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
 
		int  RequiredMP   = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, X, Y, pWeapon->getRange());
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// �Ѿ� ���ڴ� ������ ����߸���.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// �ѹ߾������� ������ �ʿ� ����. by sigi. 2002.5.9
			// pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// ������, ���� ���ʽ�, ��ǥ�� ������ ���Ѵ�.
		int         ToHitBonus    = 0;
		int         DamageBonus   = 0;
		int         ToHitPenalty  = 0;
		int         DamagePenalty = 0;
		ZoneCoord_t myX           = pSlayer->getX();
		ZoneCoord_t myY           = pSlayer->getY();	
		Dir_t       dir           = calcDirection(myX, myY, X, Y);
		bool        bHit          = false; // �ѹ��̶� �¾Ҵ°��� �����ϱ� ���� ����
		Damage_t    Damage        = 0;     // ���������� ���� �������� �����ϱ� ���� ����

		// AR�̳� SMG�� ��쿡�� 2���� �����ؼ� 4������ splash �������� ������.
		int Splash = 1 + pSkillSlot->getExpLevel()/30 + 1;

		if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// ���� ���� ���ƿ´�.
			ToHitPenalty  = getPercentValue(pSlayer->getToHit(), output.ToHit);

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());
				DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());

				bool bInvokerCheck   = (pTargetCreature->getObjectID() == pSlayer->getObjectID()) ? true : false;
				bool bRaceCheck      = pTargetCreature->isSlayer() || pTargetCreature->isNPC();
				bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty + ToHitBonus);
				bool bPK             = verifyPK(pSlayer, pTargetCreature);
				bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

				if ( !canAttack( pSlayer, pTargetCreature )
					|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				)
				{
					bHitRoll = false;
				}

				if (!bInvokerCheck && !bRaceCheck && bHitRoll && bPK && bZoneLevelCheck)
				{
					bool bCriticalHit = false;

					// �������� ����ؼ� ���Ƽ�� ���Ѵ�.
					// ���ʽ��� ��Ƽ�� ���Ƽ ������ ������ �� ���� �ִ�.
					Damage        = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
					DamagePenalty = getPercentValue(Damage, output.Damage);
					Damage        = max(0, Damage + DamagePenalty + DamageBonus);

					// ���� Ÿ���� �����ϰ��, ���÷��� �������� �Դµ�,
					// ���÷��� �������� �Ϲ� �������� 50%��.
					if (pTargetCreature->getX() != X || pTargetCreature->getY() != Y)
					{
						Damage = Damage/2;
					}

					// �ҵ���̺�ʹ� �޸� ũ�ν� ī���� üũ�� ���� �ʴ´�.
					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					cList.push_back(pTargetCreature);
					_GCSkillToTileOK1.addCListElement(targetObjectID);
					_GCSkillToTileOK2.addCListElement(targetObjectID);
					_GCSkillToTileOK5.addCListElement(targetObjectID);
							
					setDamage(pTargetCreature, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
					computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

					// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
					}

					// �����̾ �ƴ� ��쿡�� ���� �ɷ� �����Ѵ�.
					if (!pTargetCreature->isSlayer())
					{
						bHit = true;
						if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
						EnemyNum++;
					}
				}
			}

			if (bHit)
			{
				if (bIncreaseExp)
				{
					increaseDomainExp(pSlayer, DomainType , pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
				}
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(getSkillType());
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(getSkillType());
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(getSkillType());
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP();
					}

					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// �������� �������� ����߸���.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// ��Ŷ�� �����ش�.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// ��� ������ �ν��Ѵ�.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute End" << endl;

	__END_CATCH
}

MultiShot g_MultiShot;
