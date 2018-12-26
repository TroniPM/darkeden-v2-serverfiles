//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKillTimer.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectKillTimer.h"
#include "Creature.h"
#include "Monster.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectKillTimer::EffectKillTimer(Creature* pCreature, bool kill)
	
{
	__BEGIN_TRY 

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	setTarget(pCreature);
	m_bKill = kill;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectKillTimer::~EffectKillTimer()
	
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillTimer::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectKillTimer" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);

	if ( pCreature == NULL ) return;
	if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		if ( m_bKill )
		{
			pMonster->setHP(0);
		}
		else
		{
			pMonster->getZone()->deleteCreature( pMonster, pMonster->getX(), pMonster->getY() );
		}
	}

	//cout << "EffectKillTimer" << "unaffect END" << endl;
						
	__END_CATCH
}

string EffectKillTimer::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectKillTimer("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}
