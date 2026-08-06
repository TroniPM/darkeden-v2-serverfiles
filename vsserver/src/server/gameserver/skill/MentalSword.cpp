//////////////////////////////////////////////////////////////////////////////
// Filename    : MentalSword.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "MentalSword.h"
#include "SimpleMeleeSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MentalSword::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

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
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (rect.ptInRect(pSlayer->getX(), pSlayer->getY())) bTileCheck = false;
			int edge = 1;
			int oX, oY;

			//////////////////////////////////////////////////////////////////////////
			// check
			for(oY = -edge; oY <= edge; oY++)
			for(oX = -edge; oX <= edge; oX++)
			{
				int tileX = pSlayer->getX()+oX;
				int tileY = pSlayer->getY()+oY;
				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);
					if (tile.canAddEffect())
					{
						if ( tile.getEffect(Effect::EFFECT_CLASS_CRUSHING_STORM) != NULL )
						{
							cout << " 밑에 크러싱 스톰 있음"<<endl;
							bTileCheck = true;
						}

					}

				}
			}
	if(bTileCheck){
	cout << " 크러싱 스톰 추가 데미지 효과 넣음 "<<endl;
	output.Damage += getPercentValue(output.Damage,15);
	}

	g_SimpleMeleeSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

void MentalSword::execute(Monster* pMonster, Creature* pCreature)
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
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMeleeSkill.execute(pMonster, pCreature, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

MentalSword g_MentalSword;
