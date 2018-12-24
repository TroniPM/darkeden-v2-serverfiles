/////////////////////////////////////////////////////////////////////////////
// Filename	: MPacketManager.cpp
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "MPacketManager.h"
#include "MPacketID.h"
#include "MPacketHandler.h"
#include "Assert.h"

// send ��Ŷ
#include "PKTConnectAsk.h"
#include "PKTLogout.h"
#include "PKTUserInfo.h"
#include "PKTReceiveOK.h"
#include "PKTResult.h"
#include "PKTSError.h"

// receive ��Ŷ
#include "PKTConnectAccept.h"
#include "PKTConnectAcceptHandler.h"
#include "PKTPowerPoint.h"
#include "PKTPowerPointHandler.h"
#include "PKTError.h"
#include "PKTErrorHandler.h"


// ��Ŷ ID ����� ������ �ϱ� ���� ��ũ��
#define REGISTER_SEND_PACKET_ID( PACKET, PACKET_ID ) \
	MPacketID_t PACKET::getID() const { return PACKET_ID; }

// ��Ŷ �ڵ鷯 ID ����� ������ �ϱ� ���� ��ũ��
#define REGISTER_RECV_PACKET_ID( PACKET, PACKET_ID ) \
	MPacketID_t PACKET::getID() const { return PACKET_ID; } \
	MPacketID_t PACKET##Handler::getID() const { return PACKET_ID; }

// ������� ��ŶID ���
REGISTER_SEND_PACKET_ID( PKTConnectAsk,		PTC_CONNECT_ASK )
REGISTER_SEND_PACKET_ID( PKTLogout,			PTC_LOGOUT )
REGISTER_SEND_PACKET_ID( PKTUserInfo,		PTC_USERINFO )
REGISTER_SEND_PACKET_ID( PKTReceiveOK,		PTC_RECEIVE_OK )
REGISTER_SEND_PACKET_ID( PKTResult,			PTC_RESULT )
REGISTER_SEND_PACKET_ID( PKTSError,			PTC_ERROR )

// �ޱ�� ��Ŷ ID ��� �� �ڵ鷯 ID ���
REGISTER_RECV_PACKET_ID( PKTConnectAccept,	PTS_CONNECT_ACCEPT )
REGISTER_RECV_PACKET_ID( PKTPowerPoint,		PTS_POWERPOINT )
REGISTER_RECV_PACKET_ID( PKTError,			PTS_ERROR )


// ���� ���� ������
struct MPacketManager::IMPL
{
	MPacket*		pCreators[PTC_MAX];
	MPacketHandler*	pHandlers[PTC_MAX];

	IMPL();
	~IMPL();

	// ��Ŷ �����ڸ� �߰��Ѵ�.
	void addCreator( MPacket* pPacket );

	// ��Ŷ �ڵ鷯�� �߰��Ѵ�.
	void addHandler( MPacketHandler* pHandler );
};


// ������
MPacketManager::MPacketManager()
	: m_pImpl( new IMPL )
{
	Assert( m_pImpl != NULL );
}

// �Ҹ���
MPacketManager::~MPacketManager()
{
	SAFE_DELETE( m_pImpl );
}

// �ʱ�ȭ
void MPacketManager::init()
{
	// �ڵ鷯 �� ũ�������� �߰�
	m_pImpl->addCreator( new PKTConnectAccept );
	m_pImpl->addHandler( new PKTConnectAcceptHandler );
	m_pImpl->addCreator( new PKTPowerPoint );
	m_pImpl->addHandler( new PKTPowerPointHandler );
	m_pImpl->addCreator( new PKTError );
	m_pImpl->addHandler( new PKTErrorHandler );
}

// ��Ŷ �����ڸ� �߰��Ѵ�.
void MPacketManager::addCreator( MPacket* pPacket )
{
	Assert( pPacket != NULL );
	m_pImpl->addCreator( pPacket );
}

// ��Ŷ �ڵ鷯�� �߰��Ѵ�.
void MPacketManager::addHandler( MPacketHandler* pHandler )
{
	Assert( pHandler != NULL );
	m_pImpl->addHandler( pHandler );
}

// ���ο� ��Ŷ�� �����ؼ� ��ȯ�Ѵ�.
MPacket* MPacketManager::createPacket( MPacketID_t ID ) const
{
	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	return m_pImpl->pCreators[ID]->create();
}

// ��Ŷ�� �����Ѵ�.
void MPacketManager::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	Assert( pPlayer != NULL );
	Assert( pPacket != NULL );

	MPacketID_t ID = pPacket->getID();

	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	if ( m_pImpl->pHandlers[ID] == NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::execute() Handler is NULL" );
		Assert( false );
	}

	m_pImpl->pHandlers[ID]->execute( pPlayer, pPacket );
}

// ��Ŷ�� �����Ѵ�.
bool MPacketManager::hasHandler( MPacketID_t ID ) const
{
	// �ϴ� ���� Ȯ��
	if ( ID < 0 || ID >= PTC_MAX )
	{
		return false;
	}

	// �ڵ鷯�� �ִ��� Ȯ��
	if ( m_pImpl->pHandlers[ID] == NULL )
	{
		return false;
	}

	return true;
}

// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
MPacketSize_t MPacketManager::getPacketSize( MPacketID_t ID ) const
{
	if ( ID < 0 || ID >= PTC_MAX )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::createPacket() out of ID" );
		Assert( false );
	}

	return m_pImpl->pCreators[ID]->getSize();
}

// ������
MPacketManager::IMPL::IMPL()
{
	// �� �迭�� �ʱ�ȭ�Ѵ�.
	for ( MPacketID_t i = 0; i < PTC_MAX; ++i )
	{
		pCreators[i] = NULL;
		pHandlers[i] = NULL;
	}
}

// �Ҹ���
MPacketManager::IMPL::~IMPL()
{
	// ��Ŷ ������ �� �ڵ鷯�� �����.
	for ( MPacketID_t i = 0; i < PTC_MAX; ++i )
	{
		SAFE_DELETE( pCreators[i] );
		SAFE_DELETE( pHandlers[i] );
	}
}

// ��Ŷ �����ڸ� �߰��Ѵ�.
void MPacketManager::IMPL::addCreator( MPacket* pPacket )
{
	Assert( pPacket != NULL );

	// �ߺ� �˻�
	if ( pCreators[pPacket->getID()] != NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::IMPL::addCreator() dup creator" );
		Assert( false );
	}
	
	// �����ڸ� �߰��Ѵ�.
	pCreators[pPacket->getID()] = pPacket;
}

// ��Ŷ �ڵ鷯�� �߰��Ѵ�.
void MPacketManager::IMPL::addHandler( MPacketHandler* pHandler )
{
	Assert( pHandler != NULL );

	// �ߺ� �˻�
	if ( pHandlers[pHandler->getID()] != NULL )
	{
		filelog( MOFUS_ERROR_FILE, "MPacketManager::IMPL::addHandler() dup handler" );
		Assert( false );
	}

	// �ڵ鷯�� �߰��Ѵ�.
	pHandlers[pHandler->getID()] = pHandler;
}

// global variable
MPacketManager* g_pMPacketManager = NULL;

