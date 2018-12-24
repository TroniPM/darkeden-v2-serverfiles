//////////////////////////////////////////////////////////////////////////////
// Filename    : WindDivider.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "WindDivider.h"
#include "SimpleLinearMeleeSkill.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void WindDivider::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void WindDivider::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_SWORD;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	// ���߿� �ִ� ���͸� üũ�ϱ� ���Ͽ� ���Ƿ� ������.
	// 1 ���� ���� ���� ����, 2 ���� ���� ���� ����
	param.Level			= 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleLinearMeleeSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

void WindDivider::execute(Monster* pMonster, Creature* pTargetCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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
	// ���߿� �ִ� ���͸� üũ�ϱ� ���Ͽ� ���Ƿ� ������.
	// 1 ���� ���� ���� ����, 2 ���� ���� ���� ����
	param.Level			= 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleLinearMeleeSkill.execute(pMonster, pTargetCreature->getX(), pTargetCreature->getY(), param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}


WindDivider g_WindDivider;




