//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlazeWalk.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectShadyDouple.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectShadyDouple::EffectShadyDouple(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	m_AttackNum = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShadyDouple::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectShadyDouple " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectShadyDouple " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShadyDouple::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );
	if ( pAttacker == NULL )
	{
		setDeadline(0);
		return;
	}

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		&& !pCreature->isDead()
		&& !pCreature->isFlag( Effect::EFFECT_CLASS_COMA )
		// 무적상태 체크. by sigi. 2002.9.5
		&& canAttack( pAttacker, pCreature )
	   )
	{
		GCModifyInformation gcMI, gcAttackerMI;
		setDamage( pCreature, m_Point, pAttacker, SKILL_SHADY_DOUPLE, &gcMI, &gcAttackerMI );

		if ( pAttacker->isPC() ) computeAlignmentChange( pCreature, m_Point, pAttacker, &gcMI, &gcAttackerMI );
		if ( pCreature->isPC() ) pCreature->getPlayer()->sendPacket( &gcMI );
		if ( pCreature->isDead() ) setDeadline(0);
	}

	m_AttackNum--;

	if ( m_AttackNum > 0 )
	{
		setNextTime(5);
	}
	else setDeadline(0);

//cout << "EffectShadyDouple " << "begin" << endl;
	//cout << "EffectShadyDouple " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShadyDouple::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_SHADY_DOUPLE);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectShadyDouple::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectShadyDouple::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectShadyDouple("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

