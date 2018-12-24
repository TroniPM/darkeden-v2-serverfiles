//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReadyHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLoadingGearReady.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "ZonePlayerManager.h"
	#include "Zone.h"
	#include "ZoneGroup.h"
	#include "Gpackets/GCLoadGear.h"
	#include "PacketUtil.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Gpackets/GCModifyInformation.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ�� ������ �ε��� ������, ���� �������� CGLoadingGearReady ��Ŷ�� �����Ѵ�.
// �� ��Ŷ�� ���� Ŭ���̾�Ʈ�� Zone�� ť�� PC�� �־��ְ�, ����������
// �÷��̾ IPM���� ZPM���� �ű��.
//////////////////////////////////////////////////////////////////////////////
void CGLoadingGearReadyHandler::execute (CGLoadingGearReady* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);


	
	//--------------------------------------------------------------------------------
	// �÷��̾ IPM���� �����ϰ� ZPM���� �ű��.
	//--------------------------------------------------------------------------------
	try 
	{
		GCLoadGear gcLoadGear;
		makeGCLoadGear(&gcLoadGear, pCreature, 0);
		pGamePlayer->sendPacket(&gcLoadGear);

	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;
		msg << "Critical Error : IPM�� �÷��̾ ���׿�. ���� ������..  - -;\n" << nsee.toString();
		throw Error(msg.toString());
	}
#endif

	__END_DEBUG_EX 
	__END_CATCH
}