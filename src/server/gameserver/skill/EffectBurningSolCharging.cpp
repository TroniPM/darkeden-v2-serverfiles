//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBurningSolCharging.cpp
// Written by  : Sequoia
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBurningSolCharging.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBurningSolCharging::EffectBurningSolCharging(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBurningSolCharging::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBurningSolCharging::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	static Turn_t delay[] = { 10, 10, 300 };
	if ( m_Level >= 3 ) return;

	setNextTime( delay[m_Level] );

//	cout << "upgrade burning sol..." << m_Level << endl;

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList( getSendEffectClass() );
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	m_Level++;

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());
	gcAddEffect.setEffectID(getSendEffectClass());
	gcAddEffect.setDuration(getRemainDuration());
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBurningSolCharging::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBurningSolCharging::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectBurningSolCharging" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_BURNING_SOL_CHARGE_1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList( getSendEffectClass() );
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectBurningSolCharging" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBurningSolCharging::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBurningSolCharging("
		<< "ObjectID:" << getObjectID()
		<< ",Level:" << m_Level
		<< ")";
	return msg.toString();

	__END_CATCH

}

