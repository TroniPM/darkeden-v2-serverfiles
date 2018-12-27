////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateEffect.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "PacketUtil.h"
#include "EffectHellGardenJoin.h"
#include "Effect.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCAddEffect.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCreateEffect::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionCreateEffect::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	Zone* pZone = pCreature2->getZone();
	Assert( pZone != NULL );

	EffectHellGardenJoin* pEffect = new EffectHellGardenJoin( pPC );
	pEffect->setDeadline(3600);
	pCreature2->getEffectManager()->addEffect( pEffect );
	pCreature2->setFlag(Effect::EFFECT_CLASS_HELL_GARDEN_JOIN);

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pPC->getObjectID() );
	gcAddEffect.setEffectID( Effect::EFFECT_CLASS_HELL_GARDEN_JOIN );
	gcAddEffect.setDuration( 3600 );
	pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateEffect::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateEffect("
	    << ")";

	return msg.toString();

	__END_CATCH
}
