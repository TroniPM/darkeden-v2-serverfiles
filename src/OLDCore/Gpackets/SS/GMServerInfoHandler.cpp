//----------------------------------------------------------------------
//
// Filename    : GMServerInfoHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GMServerInfo.h"
#include "Properties.h"

#ifdef __LOGIN_SERVER__
	#include "UserInfoManager.h"
	#include "Assert.h"
#endif


//----------------------------------------------------------------------
// 
// GMServerInfoHander::execute()
// 
// ���� ������ �α��� �����κ��� GMServerInfo ��Ŷ�� �ް� �Ǹ�,
// ReconnectLoginInfo�� ���� �߰��ϰ� �ȴ�.
// 
//----------------------------------------------------------------------
void GMServerInfoHandler::execute ( GMServerInfo * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __LOGIN_SERVER__

	ZONEUSERDATA rData;
	WorldID_t WorldID = pPacket->getWorldID();
	ServerGroupID_t ServerGroupID = pPacket->getServerID();
	BYTE MaxCount = pPacket->getZoneUserCount();

	UserInfo * pUserInfo = g_pUserInfoManager->getUserInfo( ServerGroupID, WorldID );

	pUserInfo->setUserNum(0);
	Assert( pUserInfo != NULL );
	for( int count = 0; count < MaxCount; count++ ) {
		pPacket->popZoneUserData( rData );
		pUserInfo->setUserNum( pUserInfo->getUserNum() + rData.UserNum );
	}

#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
