////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPcHasItems.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPcHasItems::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());

	Inventory* pInventory = pPC->getInventory();
	if(pGamePlayer->getSpecialEventCount() == 1 || pCreature2->isFlag(Effect::EFFECT_CLASS_HI_PASS)){return true;}
	if ( pInventory == NULL ) return false;

//	_TPOINT tp;
	cout << " 여긴 문제 없음! " << endl;
	return pInventory->SerchItemCalls( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNumber);
	cout << " 여긴 문제 없음! 2" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPcHasItems::read (PropertyBuffer & propertyBuffer) 
	
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
string ConditionPcHasItems::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPcHasItems("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
