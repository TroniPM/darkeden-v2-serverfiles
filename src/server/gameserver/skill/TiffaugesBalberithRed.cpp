//////////////////////////////////////////////////////////////////////////////
// Filename    : SpitStream.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TiffaugesBalberithRed.h"
#include "SimpleLinearMeleeSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void TiffaugesBalberithRed::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;
	
	g_SimpleLinearMeleeSkill.execute(pMonster, pEnemy->getX(), pEnemy->getY(), param, result);

	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

TiffaugesBalberithRed g_TiffaugesBalberithRed;




