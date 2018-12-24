////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateNotEffect.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "PacketUtil.h"
#include "EffectSevenFoldStone.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCAddEffect.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCreateNotEffect::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_EffectClass = (int)propertyBuffer.getPropertyInt("EffectClass");
		m_EffectTime = (int)propertyBuffer.getPropertyInt("EffectTime");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionCreateNotEffect::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	EffectSevenFoldStone* pEffect = new EffectSevenFoldStone( pPC );
	pEffect->setDeadline( (DWORD)m_EffectTime*10 );
	pEffect->setLevel( (Effect::EffectClass)m_EffectClass );
	pEffect->setEffectType( (Effect::EffectClass)m_EffectClass );
	pEffect->create(pPC->getName());
	pPC->addEffect( pEffect );
	pPC->setFlag( pEffect->getEffectClass() );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pPC->getObjectID() );
	gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
	gcAddEffect.setDuration( (DWORD)m_EffectTime*10 );
	pCreature2->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateNotEffect::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateNotEffect("
	    << ")";

	return msg.toString();

	__END_CATCH
}
