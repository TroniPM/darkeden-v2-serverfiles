//////////////////////////////////////////////////////////////////////////////
// Filename    : Transfusion.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Transfusion.h"
#include "EffectComa.h"
#include "EffectKillAftermath.h"
#include "RankBonus.h"
#include "Properties.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Transfusion::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	//cout << "Transfusion" << endl;

    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC()
			// HIDE �� ���� �ǻ������ �̻��ϰ� �ȴ�. �ϴ� ���Ƴ���.
			// 2003. 1. 17. DEW
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
			|| ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 && pTargetCreature->isDead() ) )
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}


		ZoneCoord_t X = pTargetCreature->getX();
		ZoneCoord_t Y = pTargetCreature->getY();

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Innate �� �ִٸ� hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		// 15%�� ���
		int	 CurrentHP   = pVampire->getHP(ATTR_CURRENT);
#ifdef __CHINA_SERVER__
		int  RequiredMP  = CurrentHP*15/100; //decreaseConsumeMP(pVampire, pSkillInfo);
		int RecoverHP 	 = CurrentHP*17/100;
#else
		int  RequiredMP  = CurrentHP*12/100; //decreaseConsumeMP(pVampire, pSkillInfo);
		int RecoverHP 	 = CurrentHP*12/100;
#endif
		//bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		bool bHPCheck	 = false;

		Range_t Range = 1;

		// ������ HP�� Full�� �ƴϰ�
		// �ڽ��� HP�� 30�̻�
		if (pVampire->getHP(ATTR_CURRENT) >= 30)
		{
			if (pTargetCreature->isVampire())
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);

				// ����HP+SilverDamage < MaxHP ���� �Ѵ�.
				if (pTargetVampire->getHP(ATTR_CURRENT) + pTargetVampire->getSilverDamage() 
					< pTargetVampire->getHP(ATTR_MAX)) 
					bHPCheck = true;
			}
			/*
			// ���� �̰� �ʿ����.
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				if (pMonster->getHP(ATTR_MAX) < pMonster->getHP(ATTR_MAX_HP)) 
					bHPCHeck = true;
			}
			*/
		}

		if (bTimeCheck && bRangeCheck && bHitRoll && bHPCheck)
		{
			//cout << "Transfusion Success" << endl;

			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);


			// �������� ���� �ð��� ����Ѵ�.
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// TargetCreature�� HP�� ä���
			if (pTargetCreature->isVampire())
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
			
				HP_t maxHP = pTargetVampire->getHP(ATTR_MAX);
				HP_t currentHP = pTargetVampire->getHP(ATTR_CURRENT);
				HP_t newHP = min((int)maxHP, currentHP + RecoverHP);
		
				pTargetVampire->setHP( newHP );

				// HP�� 30%�� �Ǹ�(33% -_-;) ��Ƴ��� �ȴ�.
				if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA))
				{
					//cout << "Target has EFFECT_COMA" << endl;
					if (newHP*3 >= maxHP)
					{
						//cout << "Target HP is over 1/3" << endl;

						EffectComa* pEffectComa = (EffectComa*)(pTargetCreature->findEffect(Effect::EFFECT_CLASS_COMA));
						Assert(pEffectComa != NULL);

						if (pEffectComa->canResurrect())
						{
							//cout << "Can Resurrect!" << endl;

							// Ÿ���� ����Ʈ �Ŵ������� �ڸ� ����Ʈ�� �����Ѵ�.
							pTargetCreature->deleteEffect(Effect::EFFECT_CLASS_COMA);
							pTargetCreature->removeFlag(Effect::EFFECT_CLASS_COMA);

							// �ڸ� ����Ʈ�� ���ư��ٰ� �˷��ش�.
							GCRemoveEffect gcRemoveEffect;
							gcRemoveEffect.setObjectID(pTargetCreature->getObjectID());
							gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
							pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcRemoveEffect);

						 	// ����Ʈ ������ �ٽ� �����ش�. by sigi. 2002.11.14
				            pTargetCreature->getEffectManager()->sendEffectInfo(pTargetCreature, pZone, pTargetCreature->getX(), pTargetCreature->getY());

							// EffectKillAftermath �� ���δ�.
							if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH))
							{
								Effect *pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_KILL_AFTERMATH);
								EffectKillAftermath* pEffectKillAftermath = dynamic_cast<EffectKillAftermath*>(pEffect);
								pEffectKillAftermath->setDeadline(5*600);
							}
							else
							{
								EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pTargetCreature);
								pEffectKillAftermath->setDeadline(5*600);
								pTargetCreature->addEffect(pEffectKillAftermath);
								pTargetCreature->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
								pEffectKillAftermath->create(pTargetCreature->getName());
							}
						}
					}
				}

				// ������ ü���� ä�����ٴ� ����� �˸���.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pTargetVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pTargetVampire->getHP(ATTR_CURRENT));
				pZone->broadcastPacket(X, Y, &gcStatusCurrentHP);

				// �ڽ��� �������� �پ��͵� ��������
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(pVampire->getHP(ATTR_CURRENT));
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP);
			}


			ZoneCoord_t myX = pVampire->getX();
			ZoneCoord_t myY = pVampire->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);

			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(Range);

			_GCSkillToTileOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);
		
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			Player* pPlayer = pVampire->getPlayer();
			Assert(pPlayer != NULL);
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pVampire);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			//cout << "Transfusion Failed" << endl;
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}

    } 
	catch (Throwable & t) 
	{
		//cout << "Transfusion Failed2" << endl;
		executeSkillFailException(pVampire, getSkillType());
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Transfusion::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;
    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone!=NULL);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

        if (rect.ptInRect(X, Y))
		{
			Tile& rTile = pZone->getTile(X, Y);

			if (rTile.hasWalkingCreature())
			{
				Creature* pCreature = rTile.getCreature( Creature::MOVE_MODE_WALKING );

				execute( pVampire, pCreature->getObjectID(), pVampireSkillSlot, CEffectID);
			}
			else
			{
				executeSkillFailException(pVampire, getSkillType());
			}
		}
		else
		{
			executeSkillFailException(pVampire, getSkillType());
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
    }

	__END_CATCH
}


Transfusion g_Transfusion;
