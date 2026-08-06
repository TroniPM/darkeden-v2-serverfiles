////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPcHasEffect.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"
#include "GamePlayer.h"
////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPcHasEffect::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());

//	if(pGamePlayer->getSpecialEventCount() == 1){return true;}
	if ( pCreature2->isFlag((Effect::EffectClass)m_EffectClass) == NULL ) return false;

//	_TPOINT tp;
	if(pCreature2->isFlag((Effect::EffectClass)m_EffectClass))return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPcHasEffect::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read turn
		m_EffectClass = propertyBuffer.getPropertyInt("EffectID");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionPcHasEffect::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPcHasEffect("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
