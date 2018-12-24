////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionOriginalDeleteGetGold.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "PacketUtil.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionOriginalDeleteGetGold::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		m_GoldNum = (Gold_t)propertyBuffer.getPropertyInt("Gold");
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
void ActionOriginalDeleteGetGold::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Assert( pGamePlayer != NULL );

	pPC->setGoldEx(pPC->getGold()-m_GoldNum);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionOriginalDeleteGetGold::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionOriginalDeleteGetGold("
	    << ")";

	return msg.toString();

	__END_CATCH
}
