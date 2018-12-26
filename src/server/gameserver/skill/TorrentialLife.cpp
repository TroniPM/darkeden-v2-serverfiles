////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "TorrentialLife.h"
#include "EffectComa.h"
#include "EffectKillAftermath.h"
#include "EffectTorrentialLife.h"
#include "Properties.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void TorrentialLife::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Ousters Object Assertion
	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

    try
    {
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType());
		    
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀?컥潔?타일 핸들러
//  뱀파이어가 Vigor Drop Skill을 Tile에 사용했을때 사용하는 Handler
//////////////////////////////////////////////////////////////////////////////
void TorrentialLife::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = pOustersSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t myX = pOusters->getX();
		ZoneCoord_t myY = pOusters->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);

		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}


		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Creature* pTargetCreature;

			list<Creature*> cList;
			cList.push_back(pOusters);

			int oX, oY;
			bool bHit = false;

			for(oX = -1; oX <= 1; oX++)
			for(oY = -1; oY <= 1; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);
		    	if (!tile.canAddEffect()) continue; 

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL && pTargetCreature->isOusters() && pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA ))
				{
					EffectComa* pEffectComa = dynamic_cast<EffectComa*>(pTargetCreature->findEffect( Effect::EFFECT_CLASS_COMA ));
					if ( pEffectComa != NULL && pEffectComa->canResurrect() )
					{
						Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);
						pTargetOusters->removeFlag( Effect::EFFECT_CLASS_COMA );
						pTargetOusters->deleteEffect( Effect::EFFECT_CLASS_COMA );

						GCRemoveEffect gcRemoveEffect;
						gcRemoveEffect.setObjectID( pTargetOusters->getObjectID() );
						gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_COMA );
						pZone->broadcastPacket( pTargetOusters->getX(), pTargetOusters->getY(), &gcRemoveEffect );

						EffectTorrentialLife* pEffect = new EffectTorrentialLife( pTargetOusters );
						pEffect->setDeadline( output.Duration );
						pEffect->setBonus( output.Range );
						pTargetOusters->setFlag( Effect::EFFECT_CLASS_TORRENTIALLIFE );
						pTargetOusters->addEffect( pEffect );

						// 이펙트를 붙였으니, 능력치를 재계산한다.
						OUSTERS_RECORD prev;
						pTargetOusters->getOustersRecord(prev);
						pTargetOusters->initAllStat();
						pTargetOusters->sendRealWearingInfo();
						pTargetOusters->addModifyInfo(prev, _GCSkillToTileOK2);

						// 이펙트 정보를 다시 보내준다. by sigi. 2002.11.14
						pTargetOusters->getEffectManager()->sendEffectInfo(pTargetOusters, pZone, pTargetOusters->getX(), pTargetOusters->getY());

						// 부활 아르바이드를 방지하기 ?㎸漫?Aftermath 이펙트를 붙인다.
						// 2002.11.19 장홍창 
						if (pTargetOusters->isFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH))
						{
							Effect *pEffect = pTargetOusters->findEffect(Effect::EFFECT_CLASS_KILL_AFTERMATH);
							EffectKillAftermath* pEffectKillAftermath = dynamic_cast<EffectKillAftermath*>(pEffect);
							pEffectKillAftermath->setDeadline(5*600);
						}
						else
						{
							EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pTargetOusters);
							pEffectKillAftermath->setDeadline(5*600);
							pTargetOusters->addEffect(pEffectKillAftermath);
							pTargetOusters->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
							pEffectKillAftermath->create(pTargetOusters->getName());
						}

						HP_t CurrentHP = getPercentValue(pTargetOusters->getHP(ATTR_MAX), output.Damage);
						pTargetOusters->setHP(CurrentHP, ATTR_CURRENT);
//						pTargetOusters->setMP(0, ATTR_CURRENT);

						// 주위에 체력이 채워졌다는 사실을 알린다. 
						GCStatusCurrentHP gcStatusCurrentHP;
						gcStatusCurrentHP.setObjectID(pTargetOusters->getObjectID());
						gcStatusCurrentHP.setCurrentHP(pTargetOusters->getHP(ATTR_CURRENT));
						pZone->broadcastPacket(pTargetOusters->getX(), pTargetOusters->getY(), &gcStatusCurrentHP);

						_GCSkillToTileOK2.addCListElement( pTargetOusters->getObjectID() );
						_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
						_GCSkillToTileOK2.setSkillType(SkillType);
						_GCSkillToTileOK2.setX(X);
						_GCSkillToTileOK2.setY(Y);
						pTargetOusters->getPlayer()->sendPacket( &_GCSkillToTileOK2 );

						_GCSkillToTileOK1.addCListElement( pTargetOusters->getObjectID() );
						_GCSkillToTileOK4.addCListElement( pTargetOusters->getObjectID() );
						_GCSkillToTileOK5.addCListElement( pTargetOusters->getObjectID() );
					}
				}
			}

			// 기술을 사용한 사람들에게
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
		
			// 기술을 쓴 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			// 기술을 당한 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);

			//기술을 쓴 사람과 당한 사람을 모두 볼 수 있는 사람들에게
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
	
			// 기술을 사용한 사람에게 packet 전달
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			// 기술을 쓸 사람과 당한 사람을 모두 볼 수 있는 사람들에게 broadcasing
			// broadcasting후 5번OK를 받은 사람을 기록한다.
			// 여기에 기록된 사람은 차후 broadcasting에서 제외된다.
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// 기술을 쓴 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// 기술을 당한 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

			// 기술 delay setting
			pOustersSkillSlot->setRunTime(output.Delay);

		}
		else
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

TorrentialLife g_TorrentialLife;
