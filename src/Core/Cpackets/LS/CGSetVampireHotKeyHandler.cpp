//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSetVampireHotKeyHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSetVampireHotKey.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
//	#include "Vampire.h"
//	#include "Slayer.h"
//	#include "Zone.h"
#endif

void CGSetVampireHotKeyHandler::execute (CGSetVampireHotKey* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

/*	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

//	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) {

	// �� ���¿����� ũ��ó�� �ǰ� �ε��Ǿ���� �ϹǷ�, NULL �� �ƴϾ�� �Ѵ�.
	// PLAYER_INGAME ��ü�� ũ��ó �ε��� �����Ǿ����� �ǹ��Ѵ�.
	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	if (pCreature->isVampire()) {
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		for(int i = 0; i < 8; i++) {
			pVampire->setHotKey(i, pPacket->getHotKey(i));
		}
	}
	
//	}*/

#endif

	__END_DEBUG_EX __END_CATCH
}
