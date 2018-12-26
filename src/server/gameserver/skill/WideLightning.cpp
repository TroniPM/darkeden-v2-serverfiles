////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : WideLightning.cpp
////////////////////////////////////////////////////////////////////////////////

#include "WideLightning.h"
#include "EffectTileStorm.h"
#include "EffectMonsterTileStorm.h"
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
void WideLightning::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
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
			|| !canAttack( pSlayer, pTargetCreature )
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
//  �����̾ Wide Lightning Skill�� Tile�� ��������� ����ϴ� Handler
//////////////////////////////////////////////////////////////////////////////
void WideLightning::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		// �ϴ� ����� �����ϴ� �ɷ� �ϰ� �������� ���Ҷ�(EffectTileStorm::affect())
		// ���������� HitRoll�� ����Ѵ�.
		// 2003.1.8 by bezz
		//bool bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		bool bTileCheck = false;
		Tile& tile = pZone->getTile(X, Y);
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if(rect.ptInRect(X, Y))
		{
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bTileCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 5;

			EffectTileStorm* pEffect = new EffectTileStorm( pZone, X, Y );
			pEffect->setUserObjectID( pSlayer->getObjectID() );
			pEffect->setDamage( output.Damage );
			pEffect->setSkillType( SkillType );
			pEffect->setStormTime( 1 );
			pEffect->setTick( output.Tick );
			pEffect->setNextTime( output.Tick );

			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);

			// ����� ����� ����鿡��
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			// ����� �� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			//_GCSkillToTileOK3.setRange(Range);

			// ����� ���� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡��
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
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
			list<Creature*> cList;
			cList.push_back( pSlayer );
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

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯
//  �����̾ Wide Lightning Skill�� Tile�� ��������� ����ϴ� Handler
//////////////////////////////////////////////////////////////////////////////
void WideLightning::execute(Monster* pMonster, Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Zone* pZone = pMonster->getZone();

		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pMonster, RequiredMP);
		bool bRangeCheck = verifyDistance(pMonster, pCreature->getX(), pCreature->getY(), pSkillInfo->getRange());

		// �ϴ� ����� �����ϴ� �ɷ� �ϰ� �������� ���Ҷ�(EffectTileStorm::affect())
		// ���������� HitRoll�� ����Ѵ�.
		// 2003.1.8 by bezz
		//bool bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		bool bTileCheck = false;
		Tile& tile = pZone->getTile(pCreature->getX(), pCreature->getY());
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if(rect.ptInRect(pCreature->getX(), pCreature->getY()))
		{
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bRangeCheck && bTileCheck)
		{
			//decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 5;

			EffectMonsterTileStorm* pEffect = new EffectMonsterTileStorm( pZone, pCreature->getX(), pCreature->getY() );
			pEffect->setUserObjectID( pMonster->getObjectID() );
			pEffect->setDamage( output.Damage );
			pEffect->setSkillType( SkillType );
			pEffect->setStormTime( 1 );
			pEffect->setTick( output.Tick );
			pEffect->setNextTime( output.Tick );

			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);
		
			// ����� �� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(pCreature->getX());
			_GCSkillToTileOK3.setY(pCreature->getY());
			//_GCSkillToTileOK3.setRange(Range);

			// ����� ���� ����� �� �� �ִ� ����鿡��
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(pCreature->getX());
			_GCSkillToTileOK4.setY(pCreature->getY());
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡��
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(pCreature->getX());
			_GCSkillToTileOK5.setY(pCreature->getY());
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// ����� ����� ������� packet ����
			//pPlayer->sendPacket(&_GCSkillToTileOK1);

			// ����� �� ����� ���� ����� ��� �� �� �ִ� ����鿡�� broadcasing
			// broadcasting�� 5��OK�� ���� ���??����Ѵ�.
			// ���⿡ ��ϵ� ����� ���� broadcasting���� ���ܵȴ�.
			list<Creature*> cList;
			cList.push_back( pMonster );
			cList = pZone->broadcastSkillPacket(myX, myY, pCreature->getX(), pCreature->getY(), &_GCSkillToTileOK5, cList);
			
			// ����� �� ����� �� �� �ִ� ����鿡�� broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// ����� ���� ����� �� �� �ִ� ����鿡�� broadcasting
			pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &_GCSkillToTileOK4, cList);

		}
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

WideLightning g_WideLightning;
