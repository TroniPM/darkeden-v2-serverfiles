//////////////////////////////////////////////////////////////////////////////
// Filename    : DeadlyClaw.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DeadlyClaw.h"
#include "SimpleTileMeleeSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// ������
// ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
DeadlyClaw::DeadlyClaw()
	throw()
{
	__BEGIN_TRY

	m_pDeadlyClawMask[0].set(0,  0);
	m_pDeadlyClawMask[1].set(-1, -1);
	m_pDeadlyClawMask[2].set(0, -1);
	m_pDeadlyClawMask[3].set(1, -1);
	m_pDeadlyClawMask[4].set(-1,  0);
	m_pDeadlyClawMask[5].set(1,  0);
	m_pDeadlyClawMask[6].set(-1,  1);
	m_pDeadlyClawMask[7].set(0,  1);
	m_pDeadlyClawMask[8].set(1,  1);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void DeadlyClaw::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
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
// �����̾� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void DeadlyClaw::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	for (int i=0; i<9; i++)
	{
		param.addMask(m_pDeadlyClawMask[i].x, m_pDeadlyClawMask[i].y, 100);
	}

	g_SimpleTileMeleeSkill.execute(pVampire, X, Y, pVampireSkillSlot, param, result, CEffectID);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void DeadlyClaw::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	SkillInput input(pMonster);
	SkillOutput output; computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = 0;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	for (int i=0; i<9; i++)
	{
		param.addMask(m_pDeadlyClawMask[i].x, m_pDeadlyClawMask[i].y, 100);
	}

	g_SimpleTileMeleeSkill.execute(pMonster, X, Y, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

DeadlyClaw g_DeadlyClaw;
