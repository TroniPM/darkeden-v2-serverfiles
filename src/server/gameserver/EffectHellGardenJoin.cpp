//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.cpp
// Written by  : ��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHellGardenJoin.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "PetInfo.h"
#include "CreatureUtil.h"
#include "Assert.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "types/PetTypes.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCModifyInformation.h"
#include "VariableManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHellGardenJoin::EffectHellGardenJoin(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHellGardenJoin::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHellGardenJoin::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL || !pCreature->isPC() ) return;

	setNextTime(600);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
	Assert( pGamePlayer != NULL );

	// ���� ��Ż �ߴ�.
	if(pCreature->getZoneID() != 5030 && pCreature->getZoneID() != 5040 && pCreature->getZoneID() != 5050){
	unaffect(pCreature);
	}
	__END_CATCH
}

void EffectHellGardenJoin::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHellGardenJoin::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectHellGardenJoin" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	//cout << "EffectHellGardenJoin ����ϴ�." << endl;

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_HELL_GARDEN_JOIN);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HELL_GARDEN_JOIN);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectHellGardenJoin" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHellGardenJoin::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHellGardenJoin("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
