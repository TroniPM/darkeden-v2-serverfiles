//////////////////////////////////////////////////////////////////////////////
// Filename    : Regeneration.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GloryGround.h"
#include "EffectGloryGround.h"
#include "EffectDarkness.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void GloryGround::execute( Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID )
	throw(Error)
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

		Creature* pTargetCreature = pZone->getCreature(ObjectID);
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

void GloryGround::execute( Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID )
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
//		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
//		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_GLORYGROUND);
		bool bTileCheck	 = false;

        VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && bTileCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// ��ų ������ ����Ѵ�.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 3;

		int oX, oY;

		for(oY = -2; oY <= 2; oY++)
		{
			for(oX = -2; oX <= 2; oX++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
					if (rect.ptInRect(tileX, tileY))
					{
						Tile& tile = pZone->getTile(tileX, tileY);
						EffectDarkness* pEffect = (EffectDarkness*)(tile.getEffect(Effect::EFFECT_CLASS_DARKNESS));
						if (pEffect != NULL)
						{
								ObjectID_t effectObjectID = pEffect->getObjectID();
								pZone->deleteEffect(effectObjectID);

								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setXY(tileX, tileY);
								gcDeleteEffectFromTile.setObjectID(effectObjectID);
								gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DARKNESS);
								pZone->broadcastPacket(tileX, tileY, &gcDeleteEffectFromTile);
						}
					}
			}
		}

			for(oY = -2; oY <= 2; oY++)
			for(oX = -2; oX <= 2; oX++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);

					if (tile.canAddEffect())
					{
						if (tile.getEffect(Effect::EFFECT_CLASS_GLORYGROUND) != NULL)
						{
							executeSkillFailNormal(pSlayer, getSkillType(), NULL);

							return;
						}
					}
				}
			}


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
					EffectGloryGround* pEffect = new EffectGloryGround(pZone, tileX, tileY);
					pEffect->setDeadline(output.Duration);
					pEffect->setDamage( output.Damage );
					pEffect->setUserObjectID( pSlayer->getObjectID() );
					pEffect->setSlayer();
					pEffect->setDelay( output.Tick );
					pEffect->setNextTime( 0 );

					ObjectRegistry& objectRegister = pZone->getObjectRegistry();
					objectRegister.registerObject(pEffect);

					pZone->addEffect(pEffect);
					tile.addEffect(pEffect);
					}	
				}
			}

			// ����ġ�� �ø���.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToTileOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);


			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);

/*			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);
*/
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			list<Creature*> cList;
			cList.push_back( pSlayer );

			cList = pZone->broadcastSkillPacket( X, Y, X, Y, &_GCSkillToTileOK5, cList );

			//pZone->broadcastPacket( X, Y, &_GCSkillToTileOK3, cList );
			//pZone->broadcastPacket( X, Y, &_GCSkillToTileOK4, cList );

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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

GloryGround g_GloryGround;
