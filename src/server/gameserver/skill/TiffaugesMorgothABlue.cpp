//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TiffaugesMorgothABlue.h"
#include "SimpleMeleeSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void TiffaugesMorgothABlue::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monsterobject)" << endl;

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

	g_SimpleMeleeSkill.execute(pMonster, pEnemy, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monsterobject)" << endl;

	__END_CATCH
}

TiffaugesMorgothABlue g_TiffaugesMorgothABlue;
