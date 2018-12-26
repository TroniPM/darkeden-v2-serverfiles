////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionPcGetGold.h"
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
void ActionPcGetGold::read (PropertyBuffer & propertyBuffer)
    
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
void ActionPcGetGold::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	pPC->setGold(pPC->getGold()+m_GoldNum);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPcGetGold::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionPcGetGold("
	    << ")";

	return msg.toString();

	__END_CATCH
}
