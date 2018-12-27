//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SharedServerClient.h"
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "GuildManager.h"
#include "Guild.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////////////
// ��� packet�鿡 ���ؼ� profiling�Ѵ�. by sigi. 2002.5.6
//
// ��, �̰� ����ϱ� ���ؼ��� 
// Profile.h�� MAX_PROFILE_SAMPLES += 300�� ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

SharedServerClient::SharedServerClient (Socket* pSocket)
	 
: Player(pSocket)
{
	__BEGIN_TRY

	m_Mutex.setName("SharedServerClient");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

SharedServerClient::~SharedServerClient ()
	 
{
	__BEGIN_TRY

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::processCommand () 
     throw (IOException , Error)
{
	__BEGIN_TRY

	// ����� �ӽ������� ���� ����
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	Packet* pPacket = NULL;

	try {

		// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while (true) 
		{
			// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
			// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
			// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
			// NoSuch����. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				break;
			}
			
			// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
			// �̶� ��Ŷũ��� ����� �����Ѵ�.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);

			// ��Ŷ ���̵� �̻��ϸ� �������� ������ �����Ѵ�.
			if (packetID >= (int)Packet::PACKET_MAX)
			{
				filelog("SharedServerClient.txt", "Packet ID exceed MAX, RECV [%d/%d]" );

				throw InvalidProtocolException("too large packet id");
			}

			try 
			{
				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("SharedServerClient.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d]" );

					throw InvalidProtocolException("too large packet size");
				}
			
				// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					break;

				// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
				// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
				// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
				// �ڵ������� �ʱ�ȭ�ȴ�.
				m_pInputStream->readPacket(pPacket);

				// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.
				#ifdef __PROFILE_PACKETS__
					
					beginProfileEx(	pPacket->getPacketName().c_str() );
					pPacket->execute(this);
					endProfileEx( pPacket->getPacketName().c_str() );

				#else
					pPacket->execute(this);
				#endif
			} 
			catch (IgnorePacketException & igpe) 
			{
				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
					throw InvalidProtocolException("too large packet size");
			
				// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					break;

				// ����Ÿ�� ��� ����������, �� ũ�⸸ŭ �����ϰ�,
				// �ٸ� ��Ŷ�� ó���ϵ��� �Ѵ�....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// ���õ� ��Ŷ��, expire �� ������ ���� �ʰ� �ȴ�.
				// �� ��ȿ�� ��Ŷ���� ©���� �ʰ� ���ش�.
				// ���� �����丮���� ���� �ʴ´�.
			}
		}
	} 
	catch ( InsufficientDataException& ide )
	{
	}

	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
// flush�� ���� �ٸ� �����忡�� ��� ���ۿ� sendPacket�� ȣ���ؼ��� �ȵȴ�.
// (�̷� ���� ������ ������� say�� ���ƿ��� �͹ۿ� ����.)
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::processOutput () 
     throw (IOException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		Player::processOutput();
	} 
	catch (InvalidProtocolException & It) 
	{
		throw DisconnectException("Pipe ������ �ı��� ������ ¥����");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::sendPacket (Packet* pPacket) 
	 
{	
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		Player::sendPacket(pPacket);
	} 
	catch (InvalidProtocolException & It) 
	{
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string SharedServerClient::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	__ENTER_CRITICAL_SECTION(m_Mutex)
	
	msg << "SharedServerClient(SocketID:" << m_pSocket->getSOCKET() << ",Host:" << m_pSocket->getHost() << ")" ;

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return msg.toString();

	__END_CATCH
}

