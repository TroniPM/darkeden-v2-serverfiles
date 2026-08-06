//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPotentialExplosion.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSpiralSlay.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "PacketUtil.h"

#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCOtherModifyInfo.h"

EffectSpiralSlay::EffectSpiralSlay(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectSpiralSlay::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectSpiralSlay::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectSpiralSlay::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

void EffectSpiralSlay::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectSpiralSlay " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	pCreature->removeFlag(Effect::EFFECT_CLASS_SPIRAL_SLAY);

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	SLAYER_RECORD prev;
	pSlayer->getSlayerRecord(prev);
	pSlayer->initAllStat();
	pSlayer->sendRealWearingInfo();
	pSlayer->sendModifyInfo(prev);

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pSlayer->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SPIRAL_SLAY);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectSpiralSlay " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

void EffectSpiralSlay::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectSpiralSlay::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSpiralSlay("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
