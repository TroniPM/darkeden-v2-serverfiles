/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPointHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTPowerPointHandler.h"
#include "PKTPowerPoint.h"
#include "PKTError.h"
#include "PKTSError.h"
#include "MPlayer.h"
#include "MJob.h"
#include "Properties.h"
#include "Assert.h"

// ���� �Լ�
void PKTPowerPointHandler::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	PKTPowerPoint* pPowerPoint = dynamic_cast<PKTPowerPoint*>(pPacket);
	Assert( pPowerPoint != NULL );

	cout << "--------------------------------------------------" << endl;
	cout << "RECV [" << pPlayer->getJob()->getName() << "] PowerPoint (name:" << pPowerPoint->sCharName
		 << ",point:" << pPowerPoint->nPowerPoint << ")" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV [%s] PowerPoint (name:%s,point:%d)", pPlayer->getJob()->getName().c_str(), pPowerPoint->sCharName, pPowerPoint->nPowerPoint );
	filelog( MOFUS_PACKET_FILE, "RECV : [%s] %s", pPlayer->getJob()->getName().c_str(), pPacket->toString().c_str() );

	//////////////////////////////////////////////////////////////////////
	// ���� ��Ŷ Ȯ��.
	//////////////////////////////////////////////////////////////////////
	static int MofusServerCode = g_pConfig->getPropertyInt( "MofusServerCode" );
	// ���� �ڵ� Ȯ��
	bool bCheckGameCode = ( pPowerPoint->getGameCode() == 1 );
	// ���� �ڵ� Ȯ��
	bool bCheckGameServerCode = ( pPowerPoint->getGameServerCode() == MofusServerCode );
	// ĳ���� �̸� Ȯ��
	bool bCheckCharacterName = ( strcasecmp( pPlayer->getJob()->getName().c_str(), pPowerPoint->getCharacterName() ) == 0 );

	if ( !bCheckGameCode || !bCheckGameServerCode || !bCheckCharacterName )
	{
		cout << "--------------------------------------------------" << endl;
		cout << "ERROR CHECK (name:" << pPlayer->getJob()->getName()
			 << ",mofusname:" << pPowerPoint->getCharacterName()
			 << ",gameservercode:" << MofusServerCode
			 << ",mofusgameservercode:" << pPowerPoint->getGameServerCode()
			 << ",gamecode:" << pPowerPoint->getGameCode()
			 << ")" << endl;
		cout << "--------------------------------------------------" << endl;

		filelog( MOFUS_LOG_FILE, "ERROR (name:%s,mofusname:%s,gameservercode:%d,mofusgameservercode:%d)",
									pPlayer->getJob()->getName().c_str(),
									pPowerPoint->getCharacterName(),
									MofusServerCode,
									pPowerPoint->getGameServerCode() );

		// ��Ī ���� Ȯ�� ����
		// �Ŀ�¯ ������ Ȯ�� ���и� �˸���.
		pPlayer->sendSError( MSERR_MATCH );

		// ����ڿ��Դ� ��Ī ���� ������ �˸���.
		pPlayer->setErrorCode( MERR_MATCHING );

		// �۾� ��
		pPlayer->setEnd();

		return;
	}
	//////////////////////////////////////////////////////////////////////

	// �Ŀ� ����Ʈ ����
	// 1ȸ ���۽� ������ �ִ� �Ŀ�¯ ����Ʈ.
	// ���� �Ŀ�¯ ������ 60 ����Ʈ�� �׿� �ְ� 60 ����Ʈ�� ��� �޾Ұ�
	// 1ȸ ���۽� ������ �ִ� �Ŀ�¯ ����Ʈ�� 20 �� ���
	// 20 �� �����Ͽ� �����ϰ� ������ 40 �� ������.
	// ��������� ����ڴ� �Ŀ�¯ ������ �ִ� 60 ����Ʈ�� ��� ��������
	// ��ũ���� DB ���� 20 ����Ʈ�� �����Ǿ� �ִ�.
	static int MaxPowerPoint = 40;

	// 1ȸ ���۽� ������ �ִ� �Ŀ�¯ ����Ʈ ����
	int savepowerpoint = min( pPowerPoint->getPowerPoint(), MaxPowerPoint );

	// ������ �Ŀ� ����Ʈ�� DB�� �����Ͽ� ����
	savePowerPoint( pPlayer->getJob()->getName(), savepowerpoint );

	// ���� �α�
	filelog( MOFUS_LOG_FILE, "SAVE PowerPoint (name:%s,savepoint:%d,recvpoint:%d)",
									pPlayer->getJob()->getName().c_str(),
									savepowerpoint,
									pPowerPoint->getPowerPoint() );

	logPowerPoint( pPlayer->getJob()->getName(), pPowerPoint->getPowerPoint(), savepowerpoint );

	// ���� �Ŀ� ����Ʈ�� ����
	pPlayer->addPowerPoint( savepowerpoint );

	// ó�� �ߴٴ� ����� �Ŀ�¯ ������ �˸���.
	if ( pPowerPoint->isContinue() )
	{
		// �۾��� �� �ִ�.
		pPlayer->sendReceiveOK();
	}
	else
	{
		pPlayer->sendResult();
		pPlayer->sendLogout();

		// �۾� ���̴�.
		pPlayer->setEnd();
	}
}

