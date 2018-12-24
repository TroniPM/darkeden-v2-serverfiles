////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectEnergyDrop.h
// Writer      : ��ȫâ
// Date        : 2002.3.28
// Description :
//               Energy Drop�� --storm���� ����� ������ ������� �����Ǵ�
//               Slayer�� ����̴�.
//               ����� ����ϰ� �Ǹ�, ��� ���� ������ �߽����� 3x3�� ������
//               EffectEnergyDrop Effect�� �ٰ� �ȴ�. EffectEnergyDrop Effect
//               �� ���������� �������� ���ϴ� ����� �ƴ϶�.
//               �ش� ������ Creature���� EffectEnergyDropToCreature Effect��
//               ���̰� �������. EffectEnergyDropToCreature�� EnergyDrop��
//               ��ü �������� 1/3�� �ش��ϴ� Damage�� 3�� �������� �ش� 
//               Creature���� ���ϰ� �������. 
//     
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    ��ȫâ      header file �ۼ�
//
//
////////////////////////////////////////////////////////////////////////////////

#include "MeteoBlaze.h"
#include "EffectMeteoBlaze.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void MeteoBlaze::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
    throw(Error)
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
			|| !canAttack( pOusters, pTargetCreature )
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
// �����̾� Ÿ�� �ڵ鷯
//  �����̾ Energy Drop Skill�� Tile�� ��������� ����ϴ� Handler
//////////////////////////////////////////////////////////////////////////////
void MeteoBlaze::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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


		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 4;

			// ������ ���� ����Ʈ�� Ÿ�Ͽ� �ִٸ� ����� ���� �����Ѵ�.
			Tile& tile = pZone->getTile(X, Y);
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_METEO_BLAZE);
			if(pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// ����Ʈ ������Ʈ�� �����ؼ� Ÿ�Ͽ� ���δ�. 
			//cout << "make EffectObject to Tile" << X << " " << Y << endl;
			EffectMeteoBlaze* pEffect = new EffectMeteoBlaze(pZone, X, Y);
			pEffect->setUserObjectID( pOusters->getObjectID() );
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(0);
			pEffect->setTick(output.Tick);
			pEffect->setDamage(output.Damage);
			pEffect->setLevel(30);

			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);

			// ����Ʈ �������� ��� Creature���� effect�� �ٿ��ش�.
			// Ousters�� ����� ����� ��� ���� Ousters���Դ�
			// �ش����� �ʴ´�.
			bool bEffected = false;
			Creature* pTargetCreature;

			list<Creature*> cList;
			cList.push_back(pOusters);

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);
		    	if (!tile.canAddEffect()) continue; 

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					// 2003. 1. 10. Sequoia
					if( !checkZoneLevelToHitTarget( pTargetCreature ) ) continue;

					if(pTargetCreature->isSlayer()||pTargetCreature->isVampire())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							//cout << "MeteoBlaze to Ousters Success" << endl;
							Player* pTargetPlayer = pTargetCreature->getPlayer();
							bEffected = true;

							bool bCanSee = canSee(pTargetCreature, pOusters);

							_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

							cList.push_back(pTargetCreature);

							if (bCanSee)
							{
								// ������ ���� ������� 
								_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
								_GCSkillToTileOK2.setSkillType(SkillType);
								_GCSkillToTileOK2.setX(X);
								_GCSkillToTileOK2.setY(Y);
								_GCSkillToTileOK2.setDuration(output.Duration);
								_GCSkillToTileOK2.setRange(Range);
								pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
							}
						}
						else
						{
							//cout << "MeteoBlaze to Vampire fail" << endl;
						}
					}
					else if(pTargetCreature->isMonster())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							//cout << "MeteoBlaze to Monster Success" << endl;

							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							pMonster->addEnemy(pOusters);

							// ������ ���� �ְ� �����̾��� �����Ѵ�. by sigi. 2002.6.21
							pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_OUSTERS);
						}

					}
				} // if(pTargetCreature!= NULL)
			}

			// ����� ����� ����鿡��
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			// ����� �� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			//_GCSkillToTileOK3.setDuration(output.Duration);
			//_GCSkillToTileOK3.setRange(Range);

			// ����� ���� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡��
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
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

MeteoBlaze g_MeteoBlaze;
