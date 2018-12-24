
//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiAmputate.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TiffaugesValkyrjaBlue.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"
#include "SkillUtil.h"
#include "Item.h"

void TiffaugesValkyrjaBlue::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

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
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	bool bRangeCheck = pEnemy != NULL && verifyDistance(pMonster, pEnemy, output.Range );

	// 저 안에서는 Max Range 만 체크한다. -_-;
	if ( !bRangeCheck )
	{
		executeSkillFailNormal(pMonster, param.SkillType, pEnemy);
		return;
	}

	g_SimpleMissileSkill.execute(pMonster, pEnemy, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

TiffaugesValkyrjaBlue g_TiffaugesValkyrjaBlue;


