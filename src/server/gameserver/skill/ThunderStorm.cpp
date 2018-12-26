//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderStorm.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ThunderStorm.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"

void ThunderStorm::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = true;

	SIMPLE_SKILL_OUTPUT result;

	// ��ǥ��ġ+4����
	param.addMask( 0,  0, 100);
	param.addMask(-1, -1, 100);
	param.addMask( 0, -1, 100);
	param.addMask( 1, -1, 100);
	param.addMask(-1,  0, 100);
	param.addMask( 1,  0, 100);
	param.addMask(-1,  1, 100);
	param.addMask( 0,  1, 100);
	param.addMask( 1,  1, 100);

	// �ڽ��� �ֺ��� ����߸���.
	// �ƴϴ�.. --;
	//X = pSlayer->getX();
	//Y = pSlayer->getY();

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void ThunderStorm::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature!=NULL)
	{
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	}
	else
	{
		executeSkillFailException(pSlayer, getSkillType());
	}


	__END_CATCH
}

void ThunderStorm::execute(Monster* pMonster, Creature* pTargetCreature)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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
	param.bExpForTotalDamage = true;

	SIMPLE_SKILL_OUTPUT result;

	// ��ǥ��ġ+4����
	param.addMask( 0,  0, 100);
	param.addMask(-1, -1, 100);
	param.addMask( 0, -1, 100);
	param.addMask( 1, -1, 100);
	param.addMask(-1,  0, 100);
	param.addMask( 1,  0, 100);
	param.addMask(-1,  1, 100);
	param.addMask( 0,  1, 100);
	param.addMask( 1,  1, 100);

	// �ڽ��� �ֺ��� ����߸���.
	// �ƴϴ�.. --;
	//X = pSlayer->getX();
	//Y = pSlayer->getY();
	g_SimpleTileMissileSkill.execute(pMonster, pTargetCreature->getX(), pTargetCreature->getY(), param, result, 0, 0);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ThunderStorm g_ThunderStorm;
