//////////////////////////////////////////////////////////////////////////////
// Filename    : NooseOfWraith.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PlumyBoar.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// ������
// ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
PlumyBoar::PlumyBoar()
	
{
	__BEGIN_TRY

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void PlumyBoar::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
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
void PlumyBoar::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
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
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;
	
	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}

	g_SimpleTileMissileSkill.execute(pVampire, X, Y, pVampireSkillSlot, param, result, CEffectID, false);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void PlumyBoar::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

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
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}


	g_SimpleTileMissileSkill.execute(pMonster, X, Y, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

PlumyBoar g_PlumyBoar;
