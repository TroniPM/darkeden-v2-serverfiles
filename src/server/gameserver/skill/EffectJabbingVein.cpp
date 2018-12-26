//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectJabbingVein.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectJabbingVein.h"
#include "Ousters.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectJabbingVein::EffectJabbingVein(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	//Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectJabbingVein::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectJabbingVein" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
//	Assert(pCreature->isOusters());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_JABBING_VEIN);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

//	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
//	Assert( pTargetOusters != NULL );

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_JABBING_VEIN);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectJabbingVein" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectJabbingVein::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectJabbingVein::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectJabbingVein("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

