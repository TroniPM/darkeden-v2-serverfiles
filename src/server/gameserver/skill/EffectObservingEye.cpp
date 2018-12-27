//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectObservingEye.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectObservingEye.h"
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
EffectObservingEye::EffectObservingEye(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectObservingEye::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectObservingEye::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectObservingEye::unaffect() 
	
{
	__BEGIN_TRY	

	//cout << "EffectObservingEye" << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectObservingEye" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectObservingEye::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectObservingEye" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer()); // �����̾��� �ɸ��� �ʴ´�.

	pCreature->removeFlag(Effect::EFFECT_CLASS_OBSERVING_EYE);

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
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_OBSERVING_EYE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	// �� ����Ʈ�� ���� �־��� ũ���ĵ��� �����Ѵ�.
	pZone->updateInvisibleScan( pCreature );

	GCOtherModifyInfo gcOtherModifyInfo;
	makeGCOtherModifyInfo(&gcOtherModifyInfo, pSlayer, &prev);
	pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcOtherModifyInfo, pSlayer);

	//cout << "EffectObservingEye" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectObservingEye::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool EffectObservingEye::canSeeInvisibility( Creature* pTarget ) const
	
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_INVISIBILITY ) )
		return true;

	Level_t level;

	if ( pTarget->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pTarget);
		Assert( pVampire != NULL );

		level = pVampire->getLevel();
	}
	else if ( pTarget->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTarget);
		Assert( pMonster != NULL );

		level = pMonster->getLevel();
	}
	else
	{
		// �����̾ ���Ͱ� �ƴϸ� �����ɷ� �Ѵ�.
		return false;
	}

	if ( m_SkillLevel < level + 40 )
		return false;
	else
		return true;
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectObservingEye::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectObservingEye("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
