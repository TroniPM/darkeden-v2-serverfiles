//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReadyHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLoadingReady.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "ZonePlayerManager.h"
	#include "Zone.h"
	#include "ZoneGroup.h"
	#include "Gpackets/GCLoadInventory.h"
	#include "PacketUtil.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Gpackets/GCModifyInformation.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// 클라이언트가 데이터 로딩을 끝내면, 게임 서버에게 CGLoadingReady 패킷을 전송한다.
// 이 패킷을 받은 클라이언트는 Zone의 큐에 PC를 넣어주고, 마지막으로
// 플레이어를 IPM에서 ZPM으로 옮긴다.
//////////////////////////////////////////////////////////////////////////////
void CGLoadingReadyHandler::execute (CGLoadingReady* pPacket , Player* pPlayer)
	 
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
	// 플레이어를 IPM에서 삭제하고 ZPM으로 옮긴다.
	//--------------------------------------------------------------------------------
	try 
	{

		cout << " 여기 됨?"<<endl;
		GCLoadInventory gcLoadInventory;
		makeGCLoadInventory(&gcLoadInventory, pCreature, pPacket->getType());
		cout << " 여기 됨?3"<<endl;
		pGamePlayer->sendPacket(&gcLoadInventory);
		cout << " 여기 됨?2"<<endl;
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;
		msg << "Critical Error : IPM에 플레이어가 없네용. 무슨 일이지..  - -;\n" << nsee.toString();
		throw Error(msg.toString());
	}
#endif

	__END_DEBUG_EX 
	__END_CATCH
}
