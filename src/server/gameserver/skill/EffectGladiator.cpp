//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectGladiator.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "PacketUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCOtherModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGladiator::EffectGladiator(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGladiator::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGladiator::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGladiator::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	//cout << "EffectGladiator" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectGladiator" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGladiator::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectGladiator" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer()); // �����̾��� �ɸ��� �ʴ´�.

	pCreature->removeFlag(Effect::EFFECT_CLASS_GLADIATOR);

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SLAYER_RECORD prev;
	pSlayer->getSlayerRecord(prev);
	pSlayer->initAllStat();
	pSlayer->sendRealWearingInfo();
	pSlayer->sendModifyInfo(prev);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GLADIATOR);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectGladiator" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGladiator::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGladiator::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectGladiator("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
