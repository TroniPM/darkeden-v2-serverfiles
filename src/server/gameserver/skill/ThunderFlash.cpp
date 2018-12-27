//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderFlash.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ThunderFlash.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "ZoneUtil.h"
#include <list>

#include "CrossCounter.h"

//////////////////////////////////////////////////////////////////////////////
// ������
// ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
ThunderFlash::ThunderFlash()
	
{
	__BEGIN_TRY

	m_pThunderFlashMask[0].set(0, -1);
	m_pThunderFlashMask[1].set(0,  1);
	m_pThunderFlashMask[2].set(-1,  0);
	m_pThunderFlashMask[3].set(1,  0);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void ThunderFlash::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin(slayerobject)" << endl;

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

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(slayerobject)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// ThunderFlash::execute()
//
//////////////////////////////////////////////////////////////////////
void ThunderFlash::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// �����ϰ� �ִ� ���Ⱑ ���̰ų�, SWORD�� �ƴ϶�� ����� �� ����.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_SWORD)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end" << endl;
			return;
		}

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP�� ����߸���.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();	
			Dir_t       dir = calcDirection(myX, myY, X, Y);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Damage_t SkillDamage = output.Damage;
			Damage_t Damage      = 0;
			bool     bHit        = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			for (int count=0; count<4; count++)
			{
				int tileX = X + m_pThunderFlashMask[count].x;
				int tileY = Y + m_pThunderFlashMask[count].y;

				// ���� Ÿ���� �� �����̰�, �������밡 �ƴ϶��, ���� Ȯ���� �ִ�.
				if (rect.ptInRect(tileX, tileY))
				{
					// Ÿ���� �޾ƿ´�.
					Tile& tile = pZone->getTile(tileX, tileY);

					list<Creature*> targetList;
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						targetList.push_back(pCreature);
					}

					list<Creature*>::iterator itr = targetList.begin();
					for(; itr != targetList.end(); itr++)
					{
						Creature* pTargetCreature = (*itr);
						Assert(pTargetCreature != NULL);

						bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
						bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
						//bool bCanHit        = canHit(pSlayer, pTargetCreature, SkillType);
						bool bCanHit         = true;
						bool bPK             = verifyPK(pSlayer, pTargetCreature);
						bool bRaceCheck      = pTargetCreature->isSlayer() || pTargetCreature->isNPC();
						bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

						if (bMoveModeCheck && bHitRoll && bCanHit && bPK && !bRaceCheck && bZoneLevelCheck)
						{
							CheckCrossCounter(pSlayer, pTargetCreature, Damage, pSkillInfo->getRange());

							bool bCriticalHit = false;

							Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit) + SkillDamage;

							ObjectID_t targetObjectID = pTargetCreature->getObjectID();
							cList.push_back(pTargetCreature);

							_GCSkillToTileOK1.addCListElement(targetObjectID);
							_GCSkillToTileOK2.addCListElement(targetObjectID);
							_GCSkillToTileOK5.addCListElement(targetObjectID);

							// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
							setDamage(pTargetCreature, Damage, pSlayer, SkillType, NULL, &_GCSkillToTileOK1);
							computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);
							increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

							// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
							if (bCriticalHit)
							{
								knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
							}

							// �����̾ �ƴ� ��쿡�� ���� ������ �����Ѵ�.
							if (!pTargetCreature->isSlayer())
							{
								bHit = true;
								if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
								EnemyNum++;
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)

			if (bHit)
			{
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, Damage , 8, 1, 1, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			// ������ ������ ������ ����Ʈ��.
			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
			for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature * pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					// HP�� ��������� ��Ŷ���� ����Ѵ�.
					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// �������� �������� ����߸���.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// ��Ŷ�� �����ش�.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// ��� ������ �ν��Ѵ�.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end" << endl;

	__END_CATCH
}

ThunderFlash g_ThunderFlash;


