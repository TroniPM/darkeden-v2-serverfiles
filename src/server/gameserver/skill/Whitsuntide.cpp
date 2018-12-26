////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "Whitsuntide.h"
#include "EffectComa.h"
#include "EffectKillAftermath.h"
#include "EffectWhitsuntide.h"
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
void Whitsuntide::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
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

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
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
//  �����̾ Vigor Drop Skill�� Tile�� ��������� ����ϴ� Handler
//////////////////////////////////////////////////////////////////////////////
void Whitsuntide::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		if ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 )
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);


		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}


		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Creature* pTargetCreature;

			list<Creature*> cList;
			cList.push_back(pSlayer);

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

				if(pTargetCreature != NULL && pTargetCreature->isSlayer() && pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA ))
				{
					EffectComa* pEffectComa = dynamic_cast<EffectComa*>(pTargetCreature->findEffect( Effect::EFFECT_CLASS_COMA ));
					if ( pEffectComa != NULL && pEffectComa->canResurrect() )
					{
						Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
						pTargetSlayer->removeFlag( Effect::EFFECT_CLASS_COMA );
						pTargetSlayer->deleteEffect( Effect::EFFECT_CLASS_COMA );

						GCRemoveEffect gcRemoveEffect;
						gcRemoveEffect.setObjectID( pTargetSlayer->getObjectID() );
						gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_COMA );
						pZone->broadcastPacket( pTargetSlayer->getX(), pTargetSlayer->getY(), &gcRemoveEffect );

						EffectWhitsuntide* pEffect = new EffectWhitsuntide( pTargetSlayer );
						pEffect->setDeadline( output.Duration );
						pEffect->setBonus( output.Range );
						pTargetSlayer->setFlag( Effect::EFFECT_CLASS_WHITSUNTIDE );
						pTargetSlayer->addEffect( pEffect );

						// ����Ʈ�� �ٿ�����, �ɷ�ġ�� �����Ѵ�.
						SLAYER_RECORD prev;
						pTargetSlayer->getSlayerRecord(prev);
						pTargetSlayer->initAllStat();
						pTargetSlayer->sendRealWearingInfo();
						pTargetSlayer->addModifyInfo(prev, _GCSkillToTileOK2);

						// ����Ʈ ������ �ٽ� �����ش�. by sigi. 2002.11.14
						pTargetSlayer->getEffectManager()->sendEffectInfo(pTargetSlayer, pZone, pTargetSlayer->getX(), pTargetSlayer->getY());

						// ��Ȱ �Ƹ����̵带 �����ϱ� ���ؼ� Aftermath ����Ʈ�� ���δ�.
						// 2002.11.19 ��ȫâ 
						if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH))
						{
							Effect *pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_KILL_AFTERMATH);
							EffectKillAftermath* pEffectKillAftermath = dynamic_cast<EffectKillAftermath*>(pEffect);
							pEffectKillAftermath->setDeadline(5*600);

							bHit = true;
						}
						else
						{
							EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pTargetSlayer);
							pEffectKillAftermath->setDeadline(5*600);
							pTargetSlayer->addEffect(pEffectKillAftermath);
							pTargetSlayer->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
							pEffectKillAftermath->create(pTargetSlayer->getName());
						}

						HP_t CurrentHP = getPercentValue(pTargetSlayer->getHP(ATTR_MAX), output.Damage);
						pTargetSlayer->setHP(CurrentHP, ATTR_CURRENT);
//						pTargetSlayer->setMP(0, ATTR_CURRENT);

						// ������ ü���� ä�����ٴ� ����� �˸���. 
						GCStatusCurrentHP gcStatusCurrentHP;
						gcStatusCurrentHP.setObjectID(pTargetSlayer->getObjectID());
						gcStatusCurrentHP.setCurrentHP(pTargetSlayer->getHP(ATTR_CURRENT));
						pZone->broadcastPacket(pTargetSlayer->getX(), pTargetSlayer->getY(), &gcStatusCurrentHP);

						_GCSkillToTileOK2.addCListElement( pTargetSlayer->getObjectID() );
						_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
						_GCSkillToTileOK2.setSkillType(SkillType);
						_GCSkillToTileOK2.setX(X);
						_GCSkillToTileOK2.setY(Y);
						pTargetSlayer->getPlayer()->sendPacket( &_GCSkillToTileOK2 );

						_GCSkillToTileOK1.addCListElement( pTargetSlayer->getObjectID() );
						_GCSkillToTileOK4.addCListElement( pTargetSlayer->getObjectID() );
						_GCSkillToTileOK5.addCListElement( pTargetSlayer->getObjectID() );
					}
				}
			}

			if(bHit)
			{
				//cout << "Skill Succesfully Attacked(" << output.Damage << ")" << endl;
				shareAttrExp(pSlayer, output.Damage, 1, 1, 8, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			// ����� ����� ����鿡��
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
		
			// ����� �� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			// ����� ���� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);

			//����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡��
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
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

Whitsuntide g_Whitsuntide;
