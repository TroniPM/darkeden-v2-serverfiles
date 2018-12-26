
//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiAmputate.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MultiAmputate.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"
#include "SkillUtil.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void MultiAmputate::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_BLADE;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	Creature* pTargetCreature = pSlayer->getZone()->getCreature( TargetObjectID );
	bool bRangeCheck = pTargetCreature != NULL && verifyDistance(pSlayer, pTargetCreature, output.Range );

	// �� �ȿ����� Max Range �� üũ�Ѵ�. -_-;
	if ( !bRangeCheck )
	{
		executeSkillFailNormal(pSlayer, param.SkillType, pTargetCreature);
		return;
	}

	Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
	{
		executeSkillFailException(pSlayer, param.SkillType);
		return;
	}

	g_SimpleMissileSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

void MultiAmputate::execute(Monster* pMonster, Creature* pEnemy)
	
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

	// �� �ȿ����� Max Range �� üũ�Ѵ�. -_-;
	if ( !bRangeCheck )
	{
		executeSkillFailNormal(pMonster, param.SkillType, pEnemy);
		return;
	}

	g_SimpleMissileSkill.execute(pMonster, pEnemy, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

MultiAmputate g_MultiAmputate;


