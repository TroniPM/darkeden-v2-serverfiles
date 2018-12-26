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
// �����̾� ������Ʈ �ڵ鷯
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

		// NoSuch����. by sigi. 2002.5.2
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
// ��?��̾?Ÿ�� �ڵ鷯
//  �����̾ Vigor Drop Skill�� Tile�� ��������� ����ϴ� Handler
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

						// ����Ʈ�� �ٿ�����, �ɷ�ġ�� �����Ѵ�.
						OUSTERS_RECORD prev;
						pTargetOusters->getOustersRecord(prev);
						pTargetOusters->initAllStat();
						pTargetOusters->sendRealWearingInfo();
						pTargetOusters->addModifyInfo(prev, _GCSkillToTileOK2);

						// ����Ʈ ������ �ٽ� �����ش�. by sigi. 2002.11.14
						pTargetOusters->getEffectManager()->sendEffectInfo(pTargetOusters, pZone, pTargetOusters->getX(), pTargetOusters->getY());

						// ��Ȱ �Ƹ����̵带 �����ϱ� ?��ؼ?Aftermath ����Ʈ�� ���δ�.
						// 2002.11.19 ��ȫâ 
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

						// ������ ü���� ä�����ٴ� ����� �˸���. 
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

			// ����� ����� ����鿡��
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
		
			// ����� �� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			// ����� ���� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);

			//����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡��
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
	
			// ����� ����� ������� packet ����
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			// ����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡�� broadcasing
			// broadcasting�� 5��OK�� ���� ����� ����Ѵ�.
			// ���⿡ ��ϵ� ����� ���� broadcasting���� ���ܵȴ�.
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// ����� �� ����� �� �� �ִ� ����鿡�� broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// ����� ���� ����� �� �� �ִ� ����鿡�� broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

			// ��� delay setting
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
