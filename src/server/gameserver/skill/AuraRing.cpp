//////////////////////////////////////////////////////////////////////////////
// Filename    : AuraRing.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "AuraRing.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void AuraRing::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
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
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = false;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	// Holy Smashing �� �ִٸ� ������ 10% ����
	if ( pSlayer->hasRankBonus( RankBonus::RANK_BONUS_HOLY_SMASHING ) )
	{
		RankBonus* pRankBonus = pSlayer->getRankBonus( RankBonus::RANK_BONUS_HOLY_SMASHING );
		Assert( pRankBonus != NULL );

		param.SkillDamage += pRankBonus->getPoint();
	}

	g_SimpleMissileSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

void AuraRing::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	SkillInput input(pMonster);
	SkillOutput output;
	computeOutput(input, output);

	// ���Ͱ� ġ�� ?ϰ�쿡�?������ 50% �߰�
	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage + (input.INTE/10);
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = false;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMissileSkill.execute(pMonster, pEnemy, param, result);
	//g_SimpleMeleeSkill.execute(pMonster, pEnemy, param, result);
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}


AuraRing g_AuraRing;


