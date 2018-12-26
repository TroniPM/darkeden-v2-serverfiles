//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectParalyze.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectMistOfSoul1.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillHandler.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectMistOfSoul1::EffectMistOfSoul1(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectMistOfSoul1::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH 

}

void EffectMistOfSoul1::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMistOfSoul1::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectMistOfSoul1 " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_MIST_OF_SOUL1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_MIST_OF_SOUL1);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectMistOfSoul1 " << "unaffect END" << endl;

	__END_CATCH
}

void EffectMistOfSoul1::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectMistOfSoul1 " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectMistOfSoul1 " << "unaffect END" << endl;

	__END_CATCH
}

string EffectMistOfSoul1::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMistOfSoul1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

