//////////////////////////////////////////////////////////////////////
//
// Filename    : UDPManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "UDPManager.h"
#include "Assert.h"

#include "Datagram.h"
#include "DatagramPacket.h"

#include <unistd.h>
//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
UDPManager::UDPManager () 
	
: m_pDatagramSocket(NULL)
{
	__BEGIN_TRY

	// create datagram server socket
	m_pDatagramSocket = new DatagramSocket(19982);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
UDPManager::~UDPManager () 
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pDatagramSocket);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void UDPManager::sendDatagram (Datagram* pDatagram)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

    m_pDatagramSocket->send(pDatagram);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// send datagram packet to login server
//////////////////////////////////////////////////////////////////////
void UDPManager::sendPacket (const string& host , uint port , DatagramPacket* pPacket)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try 
	{
		// �����ͱ׷� ��ü�� �ϳ� �ΰ�, ������ peer �� ȣ��Ʈ�� ��Ʈ�� �����Ѵ�.
		Datagram datagram;

			
		datagram.setHost(host);
		datagram.setPort(port);

		// �����ͱ׷� ��Ŷ�� �����ͱ׷��� ����ִ´�.
		datagram.write(pPacket);
		
		// �����ͱ׷� ������ ���ؼ� �����ͱ׷��� �����Ѵ�.
		m_pDatagramSocket->send(&datagram);
	} 
	catch (Throwable & t) 
	{
        //cerr << "====================================================================" << endl;
		//cerr << t.toString() << endl;
		//cerr << "====================================================================" << endl;
	}

	__END_DEBUG
	__END_CATCH
}

// global variable definition
UDPManager* g_pUDPManager = NULL;
