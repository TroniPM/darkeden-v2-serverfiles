//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddSMSAddressHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddSMSAddress.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "SMSAddressBook.h"
	#include "Assert.h"

	#include "Gpackets/GCAddressListVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddSMSAddressHandler::execute (CGAddSMSAddress* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GCAddressListVerify gcVerify;

	SMSAddressBook* pBook = pPC->getAddressBook();
	Assert( pBook != NULL );

	SMSAddressElement* pElement = new SMSAddressElement( pBook->popNextEID(), pPacket->getCharacterName(), pPacket->getCustomName(), pPacket->getNumber() );
	int result = pBook->addAddressElement( pElement );

	if ( result != 0 )
	{
		gcVerify.setCode( GCAddressListVerify::ADDRESS_LIST_ADD_FAIL );
		gcVerify.setParameter( result );
		pGamePlayer->sendPacket( &gcVerify );
		SAFE_DELETE( pElement );
		return;
	}

	gcVerify.setCode( GCAddressListVerify::ADDRESS_LIST_ADD_OK );
	gcVerify.setParameter( pElement->getID() );
	pGamePlayer->sendPacket( &gcVerify );

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
