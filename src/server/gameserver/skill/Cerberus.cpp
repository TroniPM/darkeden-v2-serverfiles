//////////////////////////////////////////////////////////////////////////////
// Filename    : TalonOfCrow.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Cerberus.h"
#include "SimpleMeleeSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Cerberus::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampireobject)" << endl;

	SkillInput input(pVampire);
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

	g_SimpleMeleeSkill.execute(pVampire, TargetObjectID, pVampireSkillSlot, param, result, CEffectID);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampireobject)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Cerberus::execute(Monster* pMonster, Creature* pEnemy)
	
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

Cerberus g_Cerberus;
