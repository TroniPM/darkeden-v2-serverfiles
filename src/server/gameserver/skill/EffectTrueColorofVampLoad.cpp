//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectTrueColorofVampLoad.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTrueColorofVampLoad::EffectTrueColorofVampLoad(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTrueColorofVampLoad::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectTrueColorofVampLoad" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_TRUE_COLOR_OF_VAMP_LOAD);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Vampire* pTargetSlayer = dynamic_cast<Vampire*>(pCreature);
	Assert( pTargetSlayer != NULL );

	VAMPIRE_RECORD prev;

	pTargetSlayer->getVampireRecord(prev);
	pTargetSlayer->initAllStat();
	pTargetSlayer->sendRealWearingInfo();
	pTargetSlayer->sendModifyInfo(prev);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_TRUE_COLOR_OF_VAMP_LOAD);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectTrueColorofVampLoad" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTrueColorofVampLoad::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTrueColorofVampLoad::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTrueColorofVampLoad("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

