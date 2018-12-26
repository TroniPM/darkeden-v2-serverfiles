//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAirShield.cpp
// Written by  : Sequoia
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectAirShield.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectAirShield::EffectAirShield(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectAirShield" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_AIR_SHIELD_1);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList( m_ClientEffectClass );
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectAirShield" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAirShield::setLevel(Level_t Level) 
	throw()
{
	m_Level 			= Level;

	if( Level <= GRADE_ADEPT_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_AIR_SHIELD_1;
	else if( Level <= GRADE_EXPERT_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_AIR_SHIELD_2;
	else if( Level <= GRADE_MASTER_LIMIT_LEVEL ) m_ClientEffectClass = EFFECT_CLASS_AIR_SHIELD_3;
	else m_ClientEffectClass = EFFECT_CLASS_AIR_SHIELD_4;
} 

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectAirShield::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectAirShield("
		<< "ObjectID:" << getObjectID()
		<< ",Level:" << m_Level
		<< ",ClientEffectClass:" << (int)m_ClientEffectClass
		<< ",Damage:" << m_Damage
		<< ")";
	return msg.toString();

	__END_CATCH

}

