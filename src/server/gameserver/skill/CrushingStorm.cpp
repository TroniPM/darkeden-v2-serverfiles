#include "CrushingStorm.h"
#include "EffectCrushingStorm.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCAddEffectToTile.h"
//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void CrushingStorm::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Vampire Object Assertion
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		if (pTargetCreature==NULL	// NoSuch���� ������.. by sigi. 2002.5.2
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
		    
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void CrushingStorm::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// �������� ���� �ð��� ����Ѵ�.
		SkillInput input(pSlayer, pSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck )
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

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

							::setDamage( pMonster, output.Damage, pSlayer, pSkillSlot->getSkillType() );
							pMonster->addEnemy( pSlayer );
						}
						else
						{
							continue;
						}

						GCSkillToObjectOK4 gcSkillToObjectOK4;
						gcSkillToObjectOK4.setTargetObjectID( pTargetCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration(0);
						pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcSkillToObjectOK4 );
					}
				}
			}

			Tile& tile = pZone->getTile(X, Y);

			// ���� ����Ʈ�� �̹� �����Ѵٸ� �����Ѵ�.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_CRUSHING_STORM);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// ����Ʈ ������Ʈ�� �����Ѵ�.
			EffectCrushingStorm* pEffect = new EffectCrushingStorm(pZone, X, Y);
			pEffect->setUserObjectID( pSlayer->getObjectID() );
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(10);
			pEffect->checkPosition();
			pEffect->setDamage(output.Damage);
			pEffect->setBroadcastingEffect(false);

			// Ÿ�Ͽ� ���� ����Ʈ�� OID�� �޾ƾ� �Ѵ�.
			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);
		
			// �� �� Ÿ�Ͽ��ٰ� ����Ʈ�� �߰��Ѵ�.
			pZone->addEffect(pEffect);	
			tile.addEffect(pEffect);

			GCAddEffectToTile gcAddEffect;
			gcAddEffect.setXY( X, Y );
			gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
			gcAddEffect.setObjectID( pEffect->getObjectID() );
			gcAddEffect.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffect, pSlayer );

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setGrade(0);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			_GCSkillToTileOK3.setGrade(0);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setGrade(0);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setGrade(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL, 0);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType(), 0);
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

CrushingStorm g_CrushingStorm;
