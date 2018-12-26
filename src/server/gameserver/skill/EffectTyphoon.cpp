//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTyphoon.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectTyphoon.h"
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
EffectTyphoon::EffectTyphoon(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTyphoon::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTyphoon::unaffect()
	    
{
    __BEGIN_TRY

	//cout << "EffectTyphoon " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

	//cout << "EffectTyphoon " << "unaffect END" << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTyphoon::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectTyphoon " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_TYPHOON);
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_TYPHOON);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectTyphoon " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTyphoon::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTyphoon("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
