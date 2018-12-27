//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBrambleHalo.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectTiffaugesJoin.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "ZoneUtil.h"
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTiffaugesJoin::EffectTiffaugesJoin(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTiffaugesJoin::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		affect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTiffaugesJoin::affect(Creature* pCastCreature)
	
{
	__BEGIN_TRY

	Assert(pCastCreature != NULL);

	setNextTime( 600 );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTiffaugesJoin::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	
	// cout << "EffectTiffaugesJoin " << "unaffect BEGIN" << endl;
	Assert(pCreature != NULL);

	if ( !pCreature->isSlayer() )
		return;

	Player* pPlayer = dynamic_cast<Player*>(pCreature->getPlayer());
	Assert( pPlayer != NULL );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// Effect를 없애고 알린다.
	pCreature->removeFlag( Effect::EFFECT_CLASS_TIFFAUGES_OLD_JOIN );
	if(pCreature->getZoneID() == 1801){
	transportCreature(pCreature, 1802, pCreature->getX(), pCreature->getY(), true);
	}
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_TIFFAUGES_OLD_JOIN );

	pPlayer->sendPacket( &gcRemoveEffect );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTiffaugesJoin::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		unaffect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTiffaugesJoin::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTiffaugesJoin("
		<< ")";
	return msg.toString();

	__END_CATCH
}

