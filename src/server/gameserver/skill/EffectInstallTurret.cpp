//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectInstallTurret.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectInstallTurret.h"
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
EffectInstallTurret::EffectInstallTurret(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInstallTurret::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInstallTurret::unaffect() 
	
{
	__BEGIN_TRY	

	//cout << "EffectInstallTurret" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectInstallTurret" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInstallTurret::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectInstallTurret" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer()); // �����̾��� �ɸ��� �ʴ´�.

	pCreature->removeFlag(Effect::EFFECT_CLASS_INSTALL_TURRET);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_INSTALL_TURRET);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectInstallTurret" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectInstallTurret::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectInstallTurret("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
