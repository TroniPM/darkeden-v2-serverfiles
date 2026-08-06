//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MagmaticEruption.h"
#include "EffectMagmaticEruption.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MagmaticEruption::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);


		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType(), 0);
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType(), 0);
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void MagmaticEruption::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_BLADE || !pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pSlayer, pSkillSlot->getSkillType(), 0);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// 데미지와 지속 시간을 계산한다.
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

		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			Tile& tile = pZone->getTile(X, Y);

			// 같은 이펙트가 이미 존재한다면 삭제한다.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_MAGMATIC_EUPTION);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}
	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		int tx = X + i;
		int ty = Y + j;

		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;

		// 현재 이펙트가 붙어있는 타일을 받아온다.
		Tile& tile = pZone->getTile(tx, ty);

		// 타일 안에 존재하는 오브젝트들을 검색한다.
		const slist<Object*>& oList = tile.getObjectList();
		slist<Object*>::const_iterator itr = oList.begin();
		for (; itr != oList.end(); itr++) 
		{
			Assert(*itr != NULL);

			Object* pObject = *itr;
			Assert(pObject != NULL);

			if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
			{
				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				Assert(pCreature != NULL);

				// 무적상태 체크. by sigi. 2002.9.5
				// 산 면역. by sigi. 2002.9.13
				if ( pSlayer != NULL &&
					( !canAttack( pSlayer, pCreature )
					|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
					|| !canHit( pSlayer, pCreature, SKILL_MAGMATIC_ERUPTION ) )
				)
				{
					continue;
				}

				// 2003.1.10 by Sequoia
				// 안전지대 체크
				if( !checkZoneLevelToHitTarget( pSlayer) ) continue;

				if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
				{
					GCModifyInformation gcAttackerMI;
					GCModifyInformation gcDefenderMI;

					Damage_t damage = output.Damage;

					if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
						damage += getPercentValue(damage,20);
						::setDamage( pVampire, damage, pSlayer, SKILL_MAGMATIC_ERUPTION, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					}
					else if (pCreature->isOusters()) 
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
						damage += getPercentValue(damage,20);
						::setDamage( pOusters, damage, pSlayer, SKILL_MAGMATIC_ERUPTION, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					} 
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
						damage += getPercentValue(damage,20);					
						::setDamage( pMonster, damage, pSlayer, SKILL_MAGMATIC_ERUPTION, NULL, &gcAttackerMI, true, false );
					}
					else continue; // 아우스터즈나 NPC 상대로... -_-

					if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pSlayer->getPlayer()->sendPacket(&gcAttackerMI);
				}
			}
		}
	}
			checkMine( pZone, X, Y );

			// 이펙트 오브젝트를 생성한다.
			EffectMagmaticEruption* pEffect = new EffectMagmaticEruption(pZone, X, Y);
			pEffect->setUserObjectID( pSlayer->getObjectID() );
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(10);
			pEffect->checkPosition();
			pEffect->setDamage(output.Damage/2);
			pEffect->setBroadcastingEffect(false);

			// 타일에 붙은 이펙트는 OID를 받아야 한다.
			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);
		
			// 존 및 타일에다가 이펙트를 추가한다.
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

MagmaticEruption g_MagmaticEruption;
