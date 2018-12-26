////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPcHasParty.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"
#include "Party.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPcHasParty::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	if(pPC->getPartyID() == 0){
		return false;
	}else{
			LocalPartyManager* pLPM = pPC->getLocalPartyManager();
			Assert(pLPM != NULL);
	
			int nMemberSize = pLPM->getAdjacentMemberSize(pPC->getPartyID(), pCreature2);
			if(nMemberSize >= m_Party){
			return true;
			}
		return false;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPcHasParty::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_Party = propertyBuffer.getPropertyInt("PartyNum");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionPcHasParty::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPcHasParty("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
