//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectEaglesEye1.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectEaglesEye1::EffectEaglesEye1(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectEaglesEye1::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectEaglesEye1" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_EAGLES_EYE1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pCreature);
	Assert( pTargetSlayer != NULL );

	SLAYER_RECORD prev;

	pTargetSlayer->getSlayerRecord(prev);
	pTargetSlayer->initAllStat();
	pTargetSlayer->sendRealWearingInfo();
	pTargetSlayer->sendModifyInfo(prev);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_EAGLES_EYE1);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectEaglesEye1" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectEaglesEye1::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectEaglesEye1::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectEaglesEye1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

