//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoud.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectLoud.h"
#include "Ousters.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectLoud::EffectLoud(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	//Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoud::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectLoud" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
//	Assert(pCreature->isOusters());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_LOUD);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

//	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
//	Assert( pTargetOusters != NULL );

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_LOUD);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectLoud" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoud::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectLoud::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectLoud("
		<< ")";
	return msg.toString();

	__END_CATCH

}

