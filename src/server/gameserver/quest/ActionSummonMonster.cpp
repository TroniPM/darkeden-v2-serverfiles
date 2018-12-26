////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSummonMonster.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "Monster.h"
#include "PacketUtil.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSummonMonster::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_Type = (MonsterType_t)propertyBuffer.getPropertyInt("MonsterType");
		m_X = (ZoneCoord_t)propertyBuffer.getPropertyInt("X");
		m_Y = (ZoneCoord_t)propertyBuffer.getPropertyInt("Y");
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
void ActionSummonMonster::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	// 크리쳐의 위치를 가져오자.
	Zone* pZone = pCreature2->getZone();
	Assert( pZone != NULL );

	Monster* pMonster = new Monster(m_Type);
	Assert( pMonster != NULL );

	pZone->addCreature(pMonster , m_X , m_Y , Directions(rand()%8));

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSummonMonster::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSummonMonster("
	    << ")";

	return msg.toString();

	__END_CATCH
}
