//----------------------------------------------------------------------
//
// Filename    : GSGuildMemberLogOnHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSGuildMemberLogOn.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"

	#include "Spackets/SGGuildMemberLogOnOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSGuildMemberLogOnHandler::execute()
// 
//----------------------------------------------------------------------
void GSGuildMemberLogOnHandler::execute ( GSGuildMemberLogOn* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// ����� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	pGuildMember->setLogOn( pPacket->getLogOn() );

	// ���� ������ ���� ��Ŷ�� �����.
	SGGuildMemberLogOnOK sgGuildMemberLogOnOK;
	sgGuildMemberLogOnOK.setGuildID( pGuild->getID() );
	sgGuildMemberLogOnOK.setName( pPacket->getName() );
	sgGuildMemberLogOnOK.setLogOn( pPacket->getLogOn() );
	sgGuildMemberLogOnOK.setServerID( pPacket->getServerID() );


	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgGuildMemberLogOnOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
