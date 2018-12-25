//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.cpp
// Written by  : 쉭
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectLoginEvent.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "PetInfo.h"
#include "CreatureUtil.h"
#include "Assert.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "types/PetTypes.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCModifyInformation.h"
#include "VariableManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectLoginEvent::EffectLoginEvent(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_Delay = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoginEvent::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoginEvent::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL || !pCreature->isPC() ) return;

	setNextTime(600);
	setDeadline(999999);

	m_Delay += 600;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
	Assert( pGamePlayer != NULL );

	Statement* pStmt;
		BEGIN_DB
		{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery( "UPDATE `Slayer` SET PlayTime += 600 where Name = '%s'",
							pCreature->getName().c_str());
				if(m_Delay >= 3600){
				m_Delay = 0;
				int ItemOrder = Random(796,821);
				pStmt->executeQuery("INSERT INTO GoodsListObject (World, PlayerID, Name, GoodsID, Num, Status) Values (1, '%s', '%s', %d, 1, 'NOT')", pGamePlayer->getID().c_str(), pCreature->getName().c_str(), ItemOrder);
				}
				SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)

	__END_CATCH
}

void EffectLoginEvent::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoginEvent::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectLoginEvent" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	//cout << "EffectLoginEvent 지웁니다." << endl;

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_LOGIN_EVENT);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_LOGIN_EVENT);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectLoginEvent" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectLoginEvent::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectLoginEvent("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
