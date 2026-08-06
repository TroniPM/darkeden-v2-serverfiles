//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectCurseOfBlood1.h"
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

EffectCurseOfBlood1::EffectCurseOfBlood1(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectCurseOfBlood1::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH 

}

void EffectCurseOfBlood1::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectCurseOfBlood1::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectCurseOfBlood1 " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_CURSE_OF_BLOOD1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_CURSE_OF_BLOOD1);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectCurseOfBlood1 " << "unaffect END" << endl;

	__END_CATCH
}

void EffectCurseOfBlood1::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectCurseOfBlood1 " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectCurseOfBlood1 " << "unaffect END" << endl;

	__END_CATCH
}

string EffectCurseOfBlood1::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCurseOfBlood1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
