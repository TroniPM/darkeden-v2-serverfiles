//////////////////////////////////////////////////////////////////////////////
// Filename    : HeavenGround.cpp
// SkillName   : ÌìÉñ½µÁÙ ÈËÀàÒ½Éú¼¼ÄÜ
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MagmaDetonation1.h"
#include "EffectMagmaDetonation1.h"

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
// ½½·¹ÀÌ¾î ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void MagmaDetonation1::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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

		// NoSuchÁ¦°Å. by sigi. 2002.5.2
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
// ½½·¹ÀÌ¾î Å¸ÀÏ ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void MagmaDetonation1::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			// ÀÌÆåÆ®ÀÇ Áö¼Ó½Ã°£À» °è»êÇÑ´Ù.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t    Range    = 3;

			int oX, oY;
			list<Creature*> cList;
			// ½ÇÆÐÇÏ¸é ¸¶³ª°¡ ÁÙ¸é ¾È µÇ¹Ç·Î ¿©±â¼­ ÁÙ¿©ÁØ´Ù.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			for(oY = -2; oY <= 2; oY++)
			for(oX = -2; oX <= 2; oX++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);

					// ÇöÀç Å¸ÀÏ¿¡´Ù ÀÌÆåÆ®¸¦ Ãß°¡ÇÒ ¼ö ÀÖ?Ù¸?..
					//if (tile.canAddEffect())	// À§¿¡¼­ Ã¼Å©Çß´Ù.
					{
				
						// ÀÌÆåÆ® Å¬·¡½º¸¦ »ý¼ºÇÑ´Ù.
						EffectMagmaDetonation1* pEffect = new EffectMagmaDetonation1(pZone , tileX, tileY);
						// ÉèÖÃÐ§¹ûÉËº¦
						pEffect->setUserObjectID( pSlayer->getObjectID() );
						pEffect->setDamage( output.Damage );
						pEffect->setTick( output.Tick );
						pEffect->setNextTime(0);
						pEffect->setSlayer();
						pEffect->setLevel( 0 );
						pEffect->setDeadline(output.Duration);

						// ×¢²á¼¼ÄÜÐ§¹û
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

			shareAttrExp(pSlayer, ExpUp, 8, 1, 1, _GCSkillToTileOK1);
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

			// watcherList¿¡¼­ cList¿¡ ¼ÓÇÏÁö ¾Ê°í, caster(pSlayer)¸¦ º¼ ¼ö ¾ø´Â °æ¿ì´Â
			// OK4¸¦ º¸³»°í.. cList¿¡ Ãß°¡ÇÑ´Ù.
			for(list<Creature*>::const_iterator itr = watcherList.begin(); itr != watcherList.end(); itr++)
			{
				bool bBelong = false;
				for(list<Creature*>::const_iterator tItr = cList.begin(); tItr != cList.end(); tItr++)
					if (*itr == *tItr)
						bBelong = true;

				Creature* pWatcher = (*itr);
				if (bBelong == false && canSee(pWatcher, pSlayer) == false)
				{
					//Assert(pWatcher->isPC());	// ´ç¿¬ PC´Ù.. Zone::getWatcherList´Â PC¸¸ returnÇÑ´Ù
					if (!pWatcher->isPC())
					{
						//cout << "HeavenGround : ¿ÓÃ³ ¸®½ºÆ®°¡ PC°¡ ¾Æ´Õ´Ï´Ù." << endl;
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

			SkillSlot* pSkillSlot2 = pSlayer->hasSkill( SKILL_MAGMA_DETONATION2 );
			if(pSkillSlot2 != NULL){
			pSkillSlot->setRunTime(output.Delay);
			pSkillSlot2->setRunTime(output.Delay);
			pSlayer->sendSlayerSkillInfo();
			}else{			
			pSkillSlot->setRunTime(output.Delay);
			}
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

MagmaDetonation1 g_MagmaDetonation1;
