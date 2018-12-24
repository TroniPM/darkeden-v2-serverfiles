////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPcHasOriginalItems.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPcHasOriginalItems::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());

	Inventory* pInventory = pPC->getInventory();
	if ( pInventory == NULL ) return false;

//	_TPOINT tp;
	cout << " 여긴 문제 없음! " << endl;
	return pInventory->SerchItemCalls( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNumber);
	cout << " 여긴 문제 없음! 2" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPcHasOriginalItems::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read turn
		m_ItemClass = propertyBuffer.getPropertyInt("Class");
		m_ItemType = propertyBuffer.getPropertyInt("Type");
		m_ItemNumber = propertyBuffer.getPropertyInt("Num");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionPcHasOriginalItems::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPcHasOriginalItems("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
