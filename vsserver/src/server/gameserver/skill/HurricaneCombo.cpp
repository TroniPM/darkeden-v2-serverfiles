	//////////////////////////////////////////////////////////////////////////////
// Filename    : HurricaneCombo.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "HurricaneCombo.h"
#include "EffectSleep.h"
#include "SimpleMeleeSkill.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HurricaneCombo::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY
	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);
	
	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

				int tileX = pTargetCreature->getX();				
				int tileY = pTargetCreature->getY();

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

	g_SimpleMeleeSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);
						/*if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_SLEEP ) )
						{
							pTargetCreature->deleteEffect( Effect::EFFECT_CLASS_SLEEP );
						}

						EffectSleep* pEffect = new EffectSleep( pTargetCreature );

						// 맞는 넘한테 SLEEP 이펙트를 걸어준다.
						pEffect->setDeadline( output.Duration );
						pTargetCreature->addEffect( pEffect );
						pTargetCreature->setFlag( Effect::EFFECT_CLASS_SLEEP );

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
						gcAddEffect.setEffectID( Effect::EFFECT_CLASS_SLEEP );
						gcAddEffect.setDuration( output.Duration );
						pZone->broadcastPacket( tileX, tileY, &gcAddEffect );*/


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

HurricaneCombo g_HurricaneCombo;
