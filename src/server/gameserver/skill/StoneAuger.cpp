//////////////////////////////////////////////////////////////////////////////
// Filename    : StoneAuger.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "StoneAuger.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void StoneAuger::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

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
			)
		{
			executeSkillFailException(pOusters, getSkillType());
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}


	__END_CATCH
}

void StoneAuger::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) 
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_WRISTLET;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	if ( input.SkillLevel < 15 ) param.Grade = 0;
	else if ( input.SkillLevel < 30 ) param.Grade = 1;
	else param.Grade = 2;

	SIMPLE_SKILL_OUTPUT result;

	param.addMask( 0, 0, 100 );
	param.addMask( 1, 0, 100 );
	param.addMask(-1, 0, 100 );
	param.addMask( 0, 1, 100 );
	param.addMask( 0,-1, 100 );

	g_SimpleTileMissileSkill.execute(pOusters, X, Y, pOustersSkillSlot, param, result, CEffectID);

	__END_CATCH
}

void StoneAuger::execute(Monster* pMonster, Creature* pEnemy) 
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	SkillInput input(pMonster);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	param.Grade = 2;

	SIMPLE_SKILL_OUTPUT result;

	param.addMask( 0, 0, 100 );
	param.addMask( 1, 0, 100 );
	param.addMask(-1, 0, 100 );
	param.addMask( 0, 1, 100 );
	param.addMask( 0,-1, 100 );

	g_SimpleTileMissileSkill.execute(pMonster, pEnemy->getX(), pEnemy->getY() , param, result);

	__END_CATCH
}


StoneAuger g_StoneAuger;
