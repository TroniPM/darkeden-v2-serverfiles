//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSetAfire.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSuddenBlast.h"
#include "Slayer.h"
#include "Player.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

EffectSuddenBlast::EffectSuddenBlast(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_bBroadcastingEffect = false;

	__END_CATCH
}

void EffectSuddenBlast::affect() 
{
	__BEGIN_TRY

	if ( m_pTarget == NULL || m_pTarget->getObjectClass() != OBJECT_CLASS_CREATURE )
	{
		setDeadline(0);
		return;
	}
	affect( dynamic_cast<Creature*>(m_pTarget) );

	__END_CATCH
}

void EffectSuddenBlast::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert( pCreature != NULL );
	if ( pCreature->isDead() )
	{
		setDeadline(0);
		return;
	}

	Creature* pAttacker = pCreature->getZone()->getCreature( m_CasterOID );
	Damage_t damage = m_Damage / m_TotalTimes;
	if ( m_Times == m_TotalTimes ) damage += m_Damage % m_TotalTimes;
	if ( !canAttack( pAttacker, pCreature ) ) return;

	GCModifyInformation gcMI, gcAttackerMI;

	::setDamage( pCreature, damage, pAttacker, SKILL_SUDDEN_BLAST, &gcMI, &gcAttackerMI );

	if ( pCreature->isDead() && pAttacker != NULL && pAttacker->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pAttacker);
		Exp_t exp = computeCreatureExp( pCreature, KILL_EXP );
		shareOustersExp( pOusters, exp, gcAttackerMI );
		increaseAlignment( pAttacker, pCreature, gcAttackerMI );
		setDeadline(0);
	}

	if ( pAttacker != NULL && pAttacker->isPC() )
	{
		computeAlignmentChange(pCreature, damage, pAttacker, &gcMI, &gcAttackerMI);
		pAttacker->getPlayer()->sendPacket( &gcAttackerMI );
	}

	if ( pCreature->isPC() )
	{
		pCreature->getPlayer()->sendPacket( &gcMI );
	}

	--m_Times;

	if ( m_Times == 0 ) 
	{
		setDeadline(0);
		if ( pAttacker != NULL )
		{
			knockbackCreature( pCreature->getZone(), pCreature, pAttacker->getX(), pAttacker->getY() );
			knockbackCreature( pCreature->getZone(), pCreature, pAttacker->getX(), pAttacker->getY() );
			knockbackCreature( pCreature->getZone(), pCreature, pAttacker->getX(), pAttacker->getY() );
			knockbackCreature( pCreature->getZone(), pCreature, pAttacker->getX(), pAttacker->getY() );
		}
	}
	else 
		setNextTime( m_Tick );

	__END_CATCH
}

void EffectSuddenBlast::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectSuddenBlast " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectSuddenBlast " << "unaffect END" << endl;

    __END_CATCH
}

void EffectSuddenBlast::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectSuddenBlast " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	//cout << "EffectSuddenBlast " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

string EffectSuddenBlast::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSuddenBlast("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
