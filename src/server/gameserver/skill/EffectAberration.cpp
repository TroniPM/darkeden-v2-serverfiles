//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAberration.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectAberration.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectAberration::EffectAberration(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAberration::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

void EffectAberration::unaffect() 
	
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAberration::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectAberration" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_ABERRATION);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_ABERRATION);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		Assert( pMonster != NULL );

		pMonster->deleteAllEnemy();
		pZone->monsterScan(pMonster, pMonster->getX(), pMonster->getY(), pMonster->getDir());
	}

	//cout << "EffectAberration" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectAberration::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectAberration("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
