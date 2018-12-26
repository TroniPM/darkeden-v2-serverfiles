////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : TurnUndead.cpp
////////////////////////////////////////////////////////////////////////////////

#include "TurnUndead.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void TurnUndead::execute(Slayer * pSlayer, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Slayer Object Assertion
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Player* pPlayer = pSlayer->getPlayer();
		Assert( pPlayer != NULL );

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		int  RequiredMP		= (int)pSkillInfo->getConsumeMP();
		bool bManaCheck		= hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck		= verifyRunTime(pSkillSlot);
		bool bRangeCheck	= verifyDistance(pSlayer, X, Y, pSkillInfo->getRange()) && checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll		= HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			bool bHit = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if ( oX == 0 && oY == 0 ) continue;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				// Ÿ�Ͽ� �ִ� ũ��ó���� ����Ʈ�� �����.
				list<Creature*> targetList;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					targetList.push_back( pCreature );
				}
				if(tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					targetList.push_back( pCreature );
				}
				if(tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
					targetList.push_back( pCreature );
				}

				list<Creature*>::iterator itr = targetList.begin();
				for ( ; itr != targetList.end(); itr++ )
				{
					Creature* pTargetCreature = (*itr);
					Assert( pTargetCreature != NULL );

					if( checkZoneLevelToHitTarget( pTargetCreature ) && !pTargetCreature->isSlayer()
						   	&& !pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA)
						   	&& canAttack( pSlayer, pTargetCreature )
					)
					{
						if(pTargetCreature->isVampire() || pTargetCreature->isOusters())
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();

							bHit = true;

							// �������� �����Ų��.
							GCModifyInformation gcMI;
							::setDamage( pTargetCreature, output.Damage, pSlayer, pSkillSlot->getSkillType(), &gcMI );

							// HP �� ���ߴٰ� ����ڿ��� ������.
							pTargetPlayer->sendPacket(&gcMI);

							GCSkillToObjectOK2 gcSkillToObjectOK2;
							gcSkillToObjectOK2.setObjectID( 1 );    // �ǹ� ����.
							gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
							gcSkillToObjectOK2.setDuration(0);
						}
						else if(pTargetCreature->isMonster())
						{
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							bHit = true;

							::setDamage( pMonster, output.Damage, pSlayer, pSkillSlot->getSkillType() );
							pMonster->addEnemy( pSlayer );
						}
						else
						{
							continue;
						}

						if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
						EnemyNum++;

						GCSkillToObjectOK4 gcSkillToObjectOK4;
						gcSkillToObjectOK4.setTargetObjectID( pTargetCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration(0);
						pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcSkillToObjectOK4 );

						// ������ �ø���.
						increaseAlignment( pSlayer, pTargetCreature, _GCSkillToSelfOK1 );
					}
				}
			}

			if(bHit)
			{
				//cout << "Skill Succesfully Attacked(" << output.Damage << ")" << endl;
				shareAttrExp(pSlayer, output.Damage, 1, 1, 8, _GCSkillToSelfOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1, maxEnemyLevel, EnemyNum);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);
			}

            // ��Ŷ�� ����� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);

			// ����� ����� ������� packet ����
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);

			// ��� delay setting
			pSkillSlot->setRunTime(output.Delay);

		}
		else
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

void TurnUndead::execute(Monster* pMonster)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Slayer Object Assertion
	Assert(pMonster != NULL);

    try
    {
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType = getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t X = pMonster->getX();
		ZoneCoord_t Y = pMonster->getY();

		int  RequiredMP		= (int)pSkillInfo->getConsumeMP();
		bool bManaCheck		= hasEnoughMana(pMonster, RequiredMP);
		bool bRangeCheck	= verifyDistance(pMonster, pMonster->getX(), pMonster->getY(), pSkillInfo->getRange()) && checkZoneLevelToUseSkill(pMonster);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (bManaCheck && bRangeCheck)
		{
			// calculate damage and duration time
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if ( oX == 0 && oY == 0 ) continue;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				// Ÿ�Ͽ� �ִ� ũ��ó���� ����Ʈ�� �����.
				list<Creature*> targetList;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					targetList.push_back( pCreature );
				}
				if(tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					targetList.push_back( pCreature );
				}
				if(tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
					targetList.push_back( pCreature );
				}

				list<Creature*>::iterator itr = targetList.begin();
				for ( ; itr != targetList.end(); itr++ )
				{
					Creature* pTargetCreature = (*itr);
					Assert( pTargetCreature != NULL );

					if( checkZoneLevelToHitTarget( pTargetCreature ) && !pTargetCreature->isMonster()
						   	&& !pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA)
						   	&& canAttack( pMonster, pTargetCreature )
					)
					{
						if(pTargetCreature->isSlayer() || pTargetCreature->isVampire() || pTargetCreature->isOusters())
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();

							// �������� �����Ų��.
							GCModifyInformation gcMI;
							::setDamage( pTargetCreature, output.Damage, pMonster, getSkillType(), &gcMI );

							// HP �� ���ߴٰ� ����ڿ��� ������.
							pTargetPlayer->sendPacket(&gcMI);

							GCSkillToObjectOK2 gcSkillToObjectOK2;
							gcSkillToObjectOK2.setObjectID( 1 );    // �ǹ� ����.
							gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
							gcSkillToObjectOK2.setDuration(0);
						}

						GCSkillToObjectOK4 gcSkillToObjectOK4;
						gcSkillToObjectOK4.setTargetObjectID( pTargetCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration(0);
						pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcSkillToObjectOK4 );
					}
				}
			}

			_GCSkillToSelfOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);

			// ����� ����� ������� packet ����
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pMonster);

		}
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}


TurnUndead g_TurnUndead;
