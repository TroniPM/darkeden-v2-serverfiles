//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStriking.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectStriking.h"
#include "Slayer.h"
#include "Player.h"

#include "Gpackets/GCRemoveEffect.h"

EffectStriking::EffectStriking(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

void EffectStriking::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

void EffectStriking::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectStriking::unaffect()
	throw(Error)
{
	//cout << "EffectStriking " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectStriking " << "unaffect END" << endl;
}

void EffectStriking::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectStriking " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// ���� �÷��׸� ������.
	pCreature->removeFlag(Effect::EFFECT_CLASS_STRIKING);

	// �ɷ�ġ�� ���� ����ؼ� �����ش�.
	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	SLAYER_RECORD prev;
	pSlayer->getSlayerRecord(prev);
	pSlayer->initAllStat();
	pSlayer->sendRealWearingInfo();
	pSlayer->sendModifyInfo(prev);

	// ����Ʈ�� ������ٰ� ������ �˸���.
	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_STRIKING);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectStriking " << "unaffect END" << endl;

	__END_CATCH
}

void EffectStriking::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectStriking::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectStriking("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

