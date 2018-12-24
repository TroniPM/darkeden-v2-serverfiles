//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWhitsuntide.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectTorrentialLife.h"
#include "Ousters.h"
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
EffectTorrentialLife::EffectTorrentialLife(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTorrentialLife::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	//cout << "EffectTorrentialLife" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectTorrentialLife" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTorrentialLife::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectTorrentialLife" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters()); // 슬레이어말고는 걸리지 않는다.

	pCreature->removeFlag(Effect::EFFECT_CLASS_TORRENTIALLIFE);

	Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

	OUSTERS_RECORD prev;
	pOusters->getOustersRecord(prev);
	pOusters->initAllStat();
	pOusters->sendRealWearingInfo();
	pOusters->sendModifyInfo(prev);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_TORRENTIALLIFE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectTorrentialLife" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTorrentialLife::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTorrentialLife("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
