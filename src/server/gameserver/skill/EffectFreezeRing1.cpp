//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectParalyze.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectFreezeRing1.h"
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

EffectFreezeRing1::EffectFreezeRing1(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectFreezeRing1::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH 

}

void EffectFreezeRing1::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectFreezeRing1::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectFreezeRing1 " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_FREEZE_RING1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_FREEZE_RING1);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectFreezeRing1 " << "unaffect END" << endl;

	__END_CATCH
}

void EffectFreezeRing1::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectFreezeRing1 " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectFreezeRing1 " << "unaffect END" << endl;

	__END_CATCH
}

string EffectFreezeRing1::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectFreezeRing1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

