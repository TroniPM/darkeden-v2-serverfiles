////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPcHasItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionZoneHasMonster.h"
#include "Creature.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Zone.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionZoneHasMonster::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	MonsterManager* pMM = pCreature2->getZone()->getMonsterManager();
	hash_map< ObjectID_t, Creature* > & monsters = pMM->getCreatures();
	hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		if(m_MonsterType == pMonster->getMonsterType())
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionZoneHasMonster::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		//m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
		m_MonsterType = propertyBuffer.getPropertyInt("MonsterType");
			// 아직 개체수는 지원되지 않습니다.
			//m_ItemNumber = propertyBuffer.getPropertyInt("Num");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionZoneHasMonster::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionZoneHasMonster("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
