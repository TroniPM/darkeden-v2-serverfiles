//////////////////////////////////////////////////////////////////////////////
// Filename    : Typhoon.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Typhoon.h"
#include "SimpleMeleeSkill.h"
#include "EffectTyphoon.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Typhoon::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
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
	param.ItemClass     = Item::ITEM_CLASS_BLADE;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	//cout << "Typhoon damage = " << output.Damage << endl;

	g_SimpleMeleeSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	if (result.bSuccess)
	{
		//cout << "Typhoon Success" << endl;
		Zone* pZone = pSlayer->getZone();
		Assert(pZone!=NULL);

		Creature* pCreature = pZone->getCreature( TargetObjectID );

		if (pCreature!=NULL)
		{
			// ������ ��츸 delay�� �߰��Ѵ�.
			// player���� client���� ó���ϰ� �Ǿ��ִ�.
			if (pCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				// delay���� ( + 1�� )
				if (!pMonster->isMaster()
#ifdef __UNDERWORLD__
						&& !pMonster->isUnderworld() && pMonster->getMonsterType() != 599
#endif
				)
				{
					Timeval delay;
					delay.tv_sec  = 1;
					delay.tv_usec = 0;//500000;
					pMonster->addAccuDelay(delay);
				}
			}
		}
	}
	
	// ��뿡�� �������� �� ���� ����Ʈ�� �ٿ��ش�.

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Typhoon g_Typhoon;
