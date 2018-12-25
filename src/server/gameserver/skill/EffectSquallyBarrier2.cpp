//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSquallyBarrier2.h"
#include "Ousters.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSquallyBarrier2::EffectSquallyBarrier2(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSquallyBarrier2::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSquallyBarrier2" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	// 플래그를 끈다.
	pCreature->removeFlag(m_ClientEffectClass);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Ousters* pTargetSlayer = dynamic_cast<Ousters*>(pCreature);
	Assert( pTargetSlayer != NULL );

	OUSTERS_RECORD prev;

	pTargetSlayer->getOustersRecord(prev);
	pTargetSlayer->initAllStat();
	pTargetSlayer->sendRealWearingInfo();
	pTargetSlayer->sendModifyInfo(prev);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(m_ClientEffectClass);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectSquallyBarrier2" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSquallyBarrier2::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSquallyBarrier2::setLevel(Level_t Level) 
	throw()
{
	m_Level 			= Level;
	m_ClientEffectClass = EFFECT_CLASS_SQUALLY_BARRIER2;
} 

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSquallyBarrier2::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSquallyBarrier2("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

