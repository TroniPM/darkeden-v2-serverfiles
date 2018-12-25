//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBloodyShout1.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBloodyShout1::EffectBloodyShout1(Creature* pCreature)
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
void EffectBloodyShout1::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyShout1" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isVampire());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_BLOODY_SHOUT1);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLOODY_SHOUT1);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectBloodyShout1" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyShout1::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBloodyShout1::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBloodyShout1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

