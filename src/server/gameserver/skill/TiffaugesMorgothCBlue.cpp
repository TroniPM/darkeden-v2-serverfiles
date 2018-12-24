//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TiffaugesMorgothCBlue.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"

void TiffaugesMorgothCBlue::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
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

	g_SimpleTileMissileSkill.execute(pMonster, pEnemy->getX(), pEnemy->getY(), param, result);

	} catch ( Throwable & t ) {
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH
}

TiffaugesMorgothCBlue g_TiffaugesMorgothCBlue;


