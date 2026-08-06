////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPcHasOriginalGold.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Creature.h"
#include "Player.h"
#include "GamePlayer.h"
////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPcHasOriginalGold::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Gold_t PlayerGold = 0;

	switch (pCreature2->getCreatureClass())
	{
		case Creature::CREATURE_CLASS_SLAYER:
		{
			Slayer* pMonster = dynamic_cast<Slayer*>(pCreature2);
			PlayerGold = pMonster->getGold();
			break;
		}
		case Creature::CREATURE_CLASS_VAMPIRE:
		{
			Vampire* pMonster = dynamic_cast<Vampire*>(pCreature2);
			PlayerGold = pMonster->getGold();
			break;
		}
		case Creature::CREATURE_CLASS_OUSTERS:
		{
			Ousters* pMonster = dynamic_cast<Ousters*>(pCreature2);
			PlayerGold = pMonster->getGold();
			break;
		}

		default:
		break;
	}
	if ( PlayerGold == 0 ) return false;

//	_TPOINT tp;
	if(PlayerGold >= m_Gold)return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPcHasOriginalGold::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read turn
		m_Gold = (Gold_t)propertyBuffer.getPropertyInt("Gold");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionPcHasOriginalGold::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPcHasOriginalGold("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
