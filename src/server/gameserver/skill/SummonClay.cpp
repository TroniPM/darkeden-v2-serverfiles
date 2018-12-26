//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonClay.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SummonClay.h"
#include "EffectSummonClay.h"
#include "EffectGroundElemental.h"
#include "RankBonus.h"
#include "EffectDarkness.h"
#include "CreatureUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

#include "MonsterAI.h"

SummonClay::SummonClay() throw()
{
	m_MaskIndex[0] = 4;
	m_ElementalMask[0][0] = POINT(0,1);
	m_ElementalMask[0][1] = POINT(0,-1);
	m_ElementalMask[0][2] = POINT(1,0);
	m_ElementalMask[0][3] = POINT(-1,0);

	m_MaskIndex[1] = 8;
	m_ElementalMask[1][0] = POINT( 0,-1);
	m_ElementalMask[1][1] = POINT(-1,-1);
	m_ElementalMask[1][2] = POINT(-1, 0);
	m_ElementalMask[1][3] = POINT(-1, 1);
	m_ElementalMask[1][4] = POINT( 0, 1);
	m_ElementalMask[1][5] = POINT( 1, 1);
	m_ElementalMask[1][6] = POINT( 1, 0);
	m_ElementalMask[1][7] = POINT( 1,-1);

	m_MaskIndex[2] = 12;
	m_ElementalMask[2][0] = POINT( 0,-1);
	m_ElementalMask[2][1] = POINT(-1,-1);
	m_ElementalMask[2][2] = POINT(-1, 0);
	m_ElementalMask[2][3] = POINT(-1, 1);
	m_ElementalMask[2][4] = POINT( 0, 1);
	m_ElementalMask[2][5] = POINT( 1, 1);
	m_ElementalMask[2][6] = POINT( 1, 0);
	m_ElementalMask[2][7] = POINT( 1,-1);
	m_ElementalMask[2][8] = POINT(-2, 0);
	m_ElementalMask[2][9] = POINT( 2, 0);
	m_ElementalMask[2][10] = POINT( 0,-2);
	m_ElementalMask[2][11] = POINT( 0, 2);

	m_MaskIndex[3] = 24;
	m_ElementalMask[3][0] = POINT( 0,-1);
	m_ElementalMask[3][1] = POINT(-1,-1);
	m_ElementalMask[3][2] = POINT(-1, 0);
	m_ElementalMask[3][3] = POINT(-1, 1);
	m_ElementalMask[3][4] = POINT( 0, 1);
	m_ElementalMask[3][5] = POINT( 1, 1);
	m_ElementalMask[3][6] = POINT( 1, 0);
	m_ElementalMask[3][7] = POINT( 1,-1);
	m_ElementalMask[3][8] = POINT(-2, 0);
	m_ElementalMask[3][9] = POINT(-2,-1);
	m_ElementalMask[3][10] = POINT(-2,-2);
	m_ElementalMask[3][11] = POINT(-1,-2);
	m_ElementalMask[3][12] = POINT( 0,-2);
	m_ElementalMask[3][13] = POINT( 1,-2);
	m_ElementalMask[3][14] = POINT( 2,-2);
	m_ElementalMask[3][15] = POINT( 2,-1);
	m_ElementalMask[3][16] = POINT( 2, 0);
	m_ElementalMask[3][17] = POINT( 2, 1);
	m_ElementalMask[3][18] = POINT( 2, 2);
	m_ElementalMask[3][19] = POINT( 1, 2);
	m_ElementalMask[3][20] = POINT( 0, 2);
	m_ElementalMask[3][21] = POINT(-1, 2);
	m_ElementalMask[3][22] = POINT(-2, 2);
	m_ElementalMask[3][23] = POINT(-2, 1);
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SummonClay::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() <= 10 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() <= 20 ) Grade = 1;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 2;
	else Grade = 3;

    try
    {
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);


		// NPC�� ������ ���� ����.
		if (pTargetCreature==NULL	// NoSuch���� ������.. by sigi. 2002.5.2
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺���� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SummonClay::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// �������� ���� �ð��� ����Ѵ�.
		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);


		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bSatisfyRequire)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

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

					// ���� Ÿ�Ͽ��� ����Ʈ�� �߰��� �� �ִٸ�...
					//if (tile.canAddEffect())	// ������ üũ�ߴ�.
					{
					EffectSummonClay* pEffect = new EffectSummonClay(pZone, tileX, tileY);
					pEffect->setDeadline(output.Duration);

					ObjectRegistry& objectRegister = pZone->getObjectRegistry();
					objectRegister.registerObject(pEffect);

					pZone->addEffect(pEffect);
					tile.addEffect(pEffect);

					GCAddEffectToTile gcAddEffect;
					gcAddEffect.setXY( oX, oY );
					gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
					gcAddEffect.setObjectID( pEffect->getObjectID() );
					gcAddEffect.setDuration( output.Duration );

					pZone->broadcastPacket( oX, oY, &gcAddEffect );
					}	
				}
			}

			ZoneCoord_t myX = pOusters->getX();
			ZoneCoord_t myY = pOusters->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setGrade(Grade);
		
			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			_GCSkillToTileOK3.setGrade(Grade);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setGrade(Grade);
		
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setGrade(Grade);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pOusters);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

SummonClay g_SummonClay;
