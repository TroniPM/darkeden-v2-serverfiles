//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSquallyBarrier1back.h"
#include "Ousters.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSquallyBarrier1back::EffectSquallyBarrier1back(Creature* pCreature)
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
void EffectSquallyBarrier1back::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSquallyBarrier1back" << "unaffect BEGIN" << endl;

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

	//cout << "EffectSquallyBarrier1back" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSquallyBarrier1back::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

void EffectSquallyBarrier1back::setLevel(Level_t Level) 
	throw()
{
	m_Level 			= Level;

	if( Level == 2 ) m_ClientEffectClass = EFFECT_CLASS_SQUALLY_BARRIER2_BACK;
	else m_ClientEffectClass = EFFECT_CLASS_SQUALLY_BARRIER1_BACK;
} 

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSquallyBarrier1back::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSquallyBarrier1back("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

