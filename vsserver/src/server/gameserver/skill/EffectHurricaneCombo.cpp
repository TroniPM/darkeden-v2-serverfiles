//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPotentialExplosion.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHurricaneCombo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "PacketUtil.h"

#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCOtherModifyInfo.h"

EffectHurricaneCombo::EffectHurricaneCombo(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectHurricaneCombo::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectHurricaneCombo::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectHurricaneCombo::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

void EffectHurricaneCombo::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectHurricaneCombo " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	pCreature->removeFlag(Effect::EFFECT_CLASS_HURRICANECOMBO);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BACK_STAB_2);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectHurricaneCombo " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

void EffectHurricaneCombo::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectHurricaneCombo::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHurricaneCombo("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
