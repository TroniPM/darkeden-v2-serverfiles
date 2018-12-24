/////////////////////////////////////////////////////////////////////////////
// Filename : PKTErrorHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTErrorHandler.h"
#include "PKTError.h"
#include "MPlayer.h"
#include "MJob.h"
#include "Assert.h"


// ���� �Լ�
void PKTErrorHandler::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	PKTError* pError = dynamic_cast<PKTError*>(pPacket);
	Assert( pError != NULL );

	cout << "--------------------------------------------------" << endl;
	cout << "RECV [" << pPlayer->getJob()->getName() << "] Error : " << pError->nError << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV [%s] Error : %d", pPlayer->getJob()->getName().c_str(), pError->nError );
	filelog( MOFUS_PACKET_FILE, "RECV : [%s] %s", pPlayer->getJob()->getName().c_str(), pPacket->toString().c_str() );

	// ���� �ڵ带 ����
	pPlayer->setErrorCode( pError->getErrorCode() );

	// �α׾ƿ� ������
	pPlayer->sendLogout();

	// �۾� ��
	pPlayer->setEnd();
}

