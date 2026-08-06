//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectTheRoarOfAwakenWarrior.h"
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
EffectTheRoarOfAwakenWarrior::EffectTheRoarOfAwakenWarrior(Creature* pCreature)
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
void EffectTheRoarOfAwakenWarrior::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTheRoarOfAwakenWarrior::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTheRoarOfAwakenWarrior::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	//cout << "EffectTheRoarOfAwakenWarrior" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectTheRoarOfAwakenWarrior" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTheRoarOfAwakenWarrior::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectTheRoarOfAwakenWarrior" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer()); // 슬레이어말고는 걸리지 않는다.

	pCreature->removeFlag(Effect::EFFECT_CLASS_THE_ROAR_OF_AWAKEN_WARRIOR);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_THE_ROAR_OF_AWAKEN_WARRIOR);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectTheRoarOfAwakenWarrior" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTheRoarOfAwakenWarrior::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTheRoarOfAwakenWarrior::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTheRoarOfAwakenWarrior("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
