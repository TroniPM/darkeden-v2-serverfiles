//////////////////////////////////////////////////////////////////////////////
// Filename    : HeavenGround.cpp
// SkillName   : ������ ����ҽ������
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HeavenGround.h"
#include "EffectHeavenGround.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void HeavenGround::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
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
		if ( pTargetCreature==NULL )
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void HeavenGround::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange()) && checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y)) bTileCheck = true;

		bool bUseSkill	 = false;
		bUseSkill=true;
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck && bUseSkill)
		{
			// ����Ʈ�� ���ӽð��� ����Ѵ�.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t    Range    = 3;

			int oX, oY;
			
			list<Creature*> cList;
			// 5 * 5 ��Χ
			for(oY = -2; oY <= 2; oY++)
			for(oX = -2; oX <= 2; oX++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				// ����Ƿ���ڵ�ͼ��С
				//cout << "HeavenGround setup1" << endl;
				if (rect.ptInRect(tileX, tileY))
				{
					//cout << "HeavenGround setup2" << endl;
					Tile& tile = pZone->getTile(tileX, tileY);

					if (tile.canAddEffect())
					{
						//cout << "HeavenGround setup3" << endl;
						if (tile.getEffect(Effect::EFFECT_CLASS_MERCY_GROUND) != NULL || 
							tile.getEffect(Effect::EFFECT_CLASS_SUMMON_CLAY) != NULL)  // �ʴȴ�� slayer
						{
							//cout << "HeavenGround setup4" << endl;
							executeSkillFailNormal(pSlayer, getSkillType(), NULL);
							return;
						}

						Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_HEAVEN_GROUND);
						if (pOldEffect != NULL)
						{
							ObjectID_t effectID = pOldEffect->getObjectID();
							pZone->deleteEffect(effectID);// fix me
						}

						// ȥ����ǰ�ڵ�����˺���Ч��
								/*
								case 0:	e = Effect::EFFECT_CLASS_PROMINENCE;	break;		// ������ Oust
								case 1: e = Effect::EFFECT_CLASS_ACID_SWAMP;	break;		// �������� vamp
								case 2: e = Effect::EFFECT_CLASS_BLOODY_WALL;   break;		// Ѫǽ     vamp
								case 3: e = Effect::EFFECT_CLASS_GREEN_POISON;  break;		// ӫ��֮�� vamp
								case 4: e = Effect::EFFECT_CLASS_HELLFIRE;	    break;      // ������   oust
								*/
							Effect* pDeleteEffect=NULL;
							// ������ Oust
							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_DARKNESS);
							if (pDeleteEffect!=NULL)
							{
								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);
				

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DARKNESS);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								//cout << "DeleteEffect[" <<  Effect::EFFECT_CLASS_PROMINENCE << "]" << endl;
							}

							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_PROMINENCE);
							if (pDeleteEffect!=NULL)
							{
								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);
				

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_PROMINENCE);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								//cout << "DeleteEffect[" <<  Effect::EFFECT_CLASS_PROMINENCE << "]" << endl;
							}
							// �������� vamp
							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_ACID_SWAMP);
							if (pDeleteEffect!=NULL)
							{
 								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
 								pZone->deleteEffect(effectObjectID);
 								//tile.deleteEffect(effectObjectID);
								GCDeleteEffectFromTile gcDeleteEffectFromTile;
 								gcDeleteEffectFromTile.setXY(tileX, tileY);
 								gcDeleteEffectFromTile.setObjectID(effectObjectID);
 								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_ACID_SWAMP);
 								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								pDeleteEffect->setDeadline(1);
								cout << "DeleteEffect[" <<  "Effect::EFFECT_CLASS_ACID_SWAMP" << "]" << endl;
							}
							// Ѫǽ     vamp
							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL);
							if (pDeleteEffect!=NULL)
							{
								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_BLOODY_WALL);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								//cout << "DeleteEffect[" <<  (int)Effect::EFFECT_CLASS_BLOODY_WALL << "]" << endl;
							}
							// ӫ��֮�� vamp
							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_GREEN_POISON);
							if (pDeleteEffect!=NULL)
							{
								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_GREEN_POISON);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								//cout << "DeleteEffect[" <<  (int)Effect::EFFECT_CLASS_GREEN_POISON << "]" << endl;
							}
							// ������   oust
							pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_HELLFIRE);
							if (pDeleteEffect!=NULL)
							{
								ObjectID_t effectObjectID = pDeleteEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_HELLFIRE);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
								//cout << "DeleteEffect[" <<  (int)Effect::EFFECT_CLASS_HELLFIRE << "]" << endl;
							}

						
					}
					else
					{
						executeSkillFailNormal(pSlayer, getSkillType(), NULL);
						return;
					}
				}
			}

			// �����ϸ� ������ �ٸ� �� �ǹǷ� ���⼭ �ٿ��ش�.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			for(oY = -2; oY <= 2; oY++)
			for(oX = -2; oX <= 2; oX++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);

					// ���� Ÿ�Ͽ��� ����Ʈ�� �߰��� �� �ִٸ�...
					//if (tile.canAddEffect())	// ������ üũ�ߴ�.
					{
				
						// ����Ʈ Ŭ������ �����Ѵ�.
						EffectHeavenGround* pEffect = new EffectHeavenGround(pZone , tileX, tileY);
						// ����Ч���˺�
						pEffect->setUserObjectID( pSlayer->getObjectID() );
						pEffect->setDamage( output.Damage );
						pEffect->setTick( output.Tick );
						pEffect->setNextTime(0);
						pEffect->setSlayer();
						pEffect->setLevel( pSkillInfo->getLevel()/2 );
						pEffect->setDeadline(output.Duration);

						// ע�Ἴ��Ч��
						pZone->registerObject(pEffect);
						pZone->addEffect(pEffect);
						tile.addEffect(pEffect);

						if (oX==0 && oY==0)
						{
							GCAddEffectToTile gcAddEffectToTile;
							gcAddEffectToTile.setEffectID(pEffect->getEffectClass());
							gcAddEffectToTile.setObjectID(pEffect->getObjectID());
							gcAddEffectToTile.setXY(X, Y);
							gcAddEffectToTile.setDuration(output.Duration);

							pZone->broadcastPacket(X, Y, &gcAddEffectToTile, pSlayer);

							pEffect->setBroadcastingEffect(true);
						}
						else
						{
							pEffect->setBroadcastingEffect(false);
						}
					}	
				}	
			}

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);

			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(Range);
			//_GCSkillToTileOK2.addShortData(MODIFY_VISION, SANCTUARY_SIGHT);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(Range);
			_GCSkillToTileOK4.setDuration(output.Duration);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(Range);
			_GCSkillToTileOK5.setDuration(output.Duration);

			_GCSkillToTileOK6.setOrgXY(myX, myY);
			_GCSkillToTileOK6.setSkillType(SkillType);
			_GCSkillToTileOK6.setX(X);
			_GCSkillToTileOK6.setY(Y);
			_GCSkillToTileOK6.setDuration(output.Duration);
			_GCSkillToTileOK6.setRange(Range);
			//_GCSkillToTileOK6.addShortData(MODIFY_VISION, SANCTUARY_SIGHT);

			// EXP UP!
			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel( pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1);

			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToTileOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);

			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				if (canSee(pTargetCreature, pSlayer)) pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				else pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK6);
			}

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pSlayer);

			list<Creature*> watcherList = pZone->getWatcherList(myX, myY, pSlayer);

			// watcherList���� cList�� ������ �ʰ�, caster(pSlayer)�� �� �� ���� ����
			// OK4�� ������.. cList�� �߰��Ѵ�.
			for(list<Creature*>::const_iterator itr = watcherList.begin(); itr != watcherList.end(); itr++)
			{
				bool bBelong = false;
				for(list<Creature*>::const_iterator tItr = cList.begin(); tItr != cList.end(); tItr++)
					if (*itr == *tItr)
						bBelong = true;

				Creature* pWatcher = (*itr);
				if (bBelong == false && canSee(pWatcher, pSlayer) == false)
				{
					//Assert(pWatcher->isPC());	// �翬 PC��.. Zone::getWatcherList�� PC�� return�Ѵ�
					if (!pWatcher->isPC())
					{
						//cout << "HeavenGround : ��ó ����Ʈ�� PC�� �ƴմϴ�." << endl;
						GCSkillFailed1 _GCSkillFailed1;
						_GCSkillFailed1.setSkillType(getSkillType());
						pSlayer->getPlayer()->sendPacket(&_GCSkillFailed1);

						//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
						return;
					}
					pWatcher->getPlayer()->sendPacket(&_GCSkillToTileOK4);
					cList.push_back(*itr);
				}
			}
					
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList, false);

						
			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

HeavenGround g_HeavenGround;
