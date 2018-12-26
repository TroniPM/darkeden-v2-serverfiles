//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDivineSpirits.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDivineSpirits.h"
#include "Ousters.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDivineSpirits::EffectDivineSpirits(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineSpirits::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectDivineSpirits" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_DIVINE_SPIRITS);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
	Assert( pTargetOusters != NULL );

//	OUSTERS_RECORD prev;

//	pTargetOusters->getOustersRecord(prev);
//	pTargetOusters->initAllStat();
//	pTargetOusters->sendRealWearingInfo();
//	pTargetOusters->sendModifyInfo(prev);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DIVINE_SPIRITS);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectDivineSpirits" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineSpirits::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDivineSpirits::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDivineSpirits("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

