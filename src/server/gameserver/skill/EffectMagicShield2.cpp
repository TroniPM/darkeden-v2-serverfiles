//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectMagicShield2.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMagicShield2::EffectMagicShield2(Creature* pCreature)
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
void EffectMagicShield2::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectMagicShield2" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// �÷��׸� ����.
	pCreature->removeFlag(Effect::EFFECT_CLASS_MAGIC_SHIELD2);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pCreature);
	Assert( pTargetSlayer != NULL );

	SLAYER_RECORD prev;

	pTargetSlayer->getSlayerRecord(prev);
	pTargetSlayer->initAllStat();
	pTargetSlayer->sendRealWearingInfo();
	pTargetSlayer->sendModifyInfo(prev);

	// ����Ʈ�� �����϶�� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_MAGIC_SHIELD2);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectMagicShield2" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMagicShield2::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMagicShield2::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMagicShield2("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

