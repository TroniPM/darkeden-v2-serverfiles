//////////////////////////////////////////////////////////////////////////////
// Filename    : CGWithdrawTaxHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGWithdrawTax.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "GuildManager.h"
	#include "CastleInfoManager.h"
	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCModifyInformation.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGWithdrawTaxHandler::execute (CGWithdrawTax* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GuildID_t guildID = pPC->getGuildID();
	Gold_t gold = pPacket->getGold();

	list<CastleInfo*> pCastleInfoList = g_pCastleInfoManager->getGuildCastleInfos( guildID );
	if ( pCastleInfoList.empty() )
	{
		GCNPCResponse fail;
		fail.setCode( NPC_RESPONSE_WITHDRAW_TAX_FAIL );

		pGamePlayer->sendPacket( &fail );
		return;
	}

	bool bOwner = false;
	list<CastleInfo*>::iterator itr = pCastleInfoList.begin();
	CastleInfo* pCastleInfo = NULL;
	for ( ; itr != pCastleInfoList.end() ; itr++ )
	{
		if ( (*itr)->getZoneID() == pPC->getZoneID() )
		{
			pCastleInfo = (*itr);
			bOwner = true;
			break;
		}
	}

	if ( !g_pGuildManager->isGuildMaster( guildID, pPC )	// ��� �����Ͱ� �ƴϴ�.
		|| !bOwner											// �� �÷��̾��� ��尡 ������ ���� �ƴϴ�.
		|| gold == 0										// �峭ġ��~
		|| pCastleInfo->getTaxBalance() < gold				// ���� ���ڶ���.
	)
	{
		GCNPCResponse fail;
		fail.setCode( NPC_RESPONSE_WITHDRAW_TAX_FAIL );

		pGamePlayer->sendPacket( &fail );
		return;
	}

	// ��� ������ �����Ǿ���. ���� ���� ã�Ƽ� �÷��̾�� �־��ش�.
	Gold_t remainBalance = pCastleInfo->decreaseTaxBalanceEx( gold );
	pPC->increaseGoldEx( gold );

	// ������� ���� �þ�ٴ� ������ �����ش�.
	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );

	pGamePlayer->sendPacket( &gcMI );

	// ���� ã�� �� �����ߴٰ� �˸���.
	GCNPCResponse success;
	success.setCode( NPC_RESPONSE_WITHDRAW_TAX_OK );
	success.setParameter( remainBalance );

	pGamePlayer->sendPacket( &success );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

