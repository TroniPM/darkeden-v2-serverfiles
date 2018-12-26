//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStorm.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodySkull.h"
#include "RankBonus.h"

#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodySkull::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Vampire Object Assertion
	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
		    
			return;
		}

		execute(pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodySkull::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;
	try {
		
	SkillInput input(pVampire);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}


	SIMPLE_SKILL_OUTPUT result;

	g_SimpleTileMissileSkill.execute(pVampire, X, Y, pVampireSkillSlot, param, result);

	} catch ( Throwable & t ) {
		executeSkillFailException(pVampire, getSkillType());
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodySkull::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;
	try {
		
	SkillInput input(pMonster);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}


	SIMPLE_SKILL_OUTPUT result;

	g_SimpleTileMissileSkill.execute(pMonster, pMonster->getX(), pMonster->getY(), param, result, 0, true);

	} catch ( Throwable & t ) {
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH
}
BloodySkull g_BloodySkull;
