//--------------------------------------------------------------------------------
//
// Filename    : CURequestLoginModeHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CURequestLoginMode.h"

#ifdef __UPDATE_SERVER__
	#include <sys/dir.h>
	#include "UpdateServerPlayer.h"
	#include "Properties.h"
	#include "Upackets/UCRequestLoginMode.h"

#endif


//--------------------------------------------------------------------------------
//
// �α��� ��带 Ȯ���ؼ� �˷��ش�
//
//--------------------------------------------------------------------------------
void CURequestLoginModeHandler::execute ( CURequestLoginMode * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	static bool bWebLogin = g_pConfig->getPropertyInt( "WebLogin" ) == 1;

	cout << ( bWebLogin ? ( "weblogin" ) : ( "normal login" ) ) << endl;

	UCRequestLoginMode ucRequestLoginMode;
	if ( bWebLogin )
		ucRequestLoginMode.setLoginMode( LOGIN_MODE_WEBLOGIN );
	else
		ucRequestLoginMode.setLoginMode( LOGIN_MODE_NORMAL );

	pUpdateServerPlayer->sendPacket( &ucRequestLoginMode );

	if ( bWebLogin )
		throw DisconnectException();

#endif
		
	__END_CATCH
}

