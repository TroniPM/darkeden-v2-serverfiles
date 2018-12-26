//--------------------------------------------------------------------------------
// 
// Filename    : UpdateServerPlyaer.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "UpdateServerPlayer.h"
#include "Assert.h"
#include "Packet.h"
#include "Upackets/CUBeginUpdate.h"
#include "Upackets/CURequest.h"
#include "Upackets/CUEndUpdate.h"
#include "Upackets/CURequestLoginMode.h"

//--------------------------------------------------------------------------------
//
// constructor
//
// *CAUTION*
//
// ������Ʈ ������ �÷��̾�� ������ ������ Ŭ���̾�Ʈ�� �����ϱ� ������, ������ 
// �÷��̾� Ŭ�������� ������½�Ʈ���� ���õ� �κи��� ���������ָ� �ȴ�. �ֳ��ϸ�, 
// ������ ũ�⸦ �� �� ���� ���¿��� ����� ���۸��ϰ� �Ǹ� ������ ���� ������ �ֱ� 
// �����̴�. ����, ���۸����� �ʴ� ��� ����� ����ؾ� �ϰڴ�. �� �Է� �κ��� 
// ������ ���� ���۸��� �ص� �����ϴ�. 
//
// �����Ҷ�, �ٸ� �÷��̾� ���� Ŭ�����ʹ� �޸�, Player Ŭ������ �����ڸ� ���������
// ȣ������ �ʴ´�. �̴� SocketOutputStream �� �������� �ʴ� Player�� ����Ʈ �����ڸ�
// ȣ���ϵ��� �ϱ� ���ؼ��̴�. 
//
//--------------------------------------------------------------------------------
//static int maxIdleSec         = 60 * 5;      // 5��.
static int maxIdleSec         = 30; // 20��

// Http ������� �ٲ�� ������ �� �̻� buffer�� ���� �ʿ����� �ʴ�.
// Ȥ�ö� SocketInputStream�� resize �Ǵ����� Ȯ���� ���߰���.
// by sigi. 2002.11.11
const int clientBufferSize = 1024;	

UpdateServerPlayer::UpdateServerPlayer ( Socket * pSocket )
	 
//: m_pSocket(pSocket), m_PlayerStatus(USPS_NONE)
: m_PlayerStatus(USPS_NONE)
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

	Assert( m_pInputStream == NULL );
	Assert( m_pOutputStream == NULL );

	try {
		// �����Է½�Ʈ���� �״�� �������ش�.
		m_pInputStream = new SocketInputStream( m_pSocket, clientBufferSize );
	} catch (Error& t) {
		filelog("updateServerPlayerBUG.txt", "%s", t.toString().c_str());
		throw;
	} catch (Throwable& t) {
		filelog("updateServerPlayerBUG.txt", "%s", t.toString().c_str());
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------------------
UpdateServerPlayer::~UpdateServerPlayer ()
	 
{
	__BEGIN_TRY
		
	// �� � �÷��̾� ��ü�� ������ ������, �� ���´� �α׾ƿ��̾�� �Ѵ�.
	// �� � �÷��̾ ���� ���� ��Ű����, �� ���¸� �α׾ƿ����� ������ �Ѵ�.
	Assert( m_PlayerStatus == USPS_END_SESSION );

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// parse packet and execute handler for the packet
//
// ��Ŷ���丮�� ������� �ʴ� ������ �ʿ���� �����̴�. -_-;
//
//--------------------------------------------------------------------------------
void UpdateServerPlayer::processCommand () 
     
{
	__BEGIN_TRY

	//__BEGIN_DEBUG

	bool bLog = false;

	/*
	if (getSocket()->getHost()=="211.208.59.138"
		|| getSocket()->getHost()=="202.30.110.120")
	{
		bLog = true;
	}
	*/

	//try {

		// ����� �ӽ������� ���� ����
		char header[szPacketHeader];
		PacketID_t packetID;
		PacketSize_t packetSize;

		if (isPenaltyFlag(PENALTY_TYPE_KICKED)) {
			throw DisconnectException("He is had penalty");
		}

		//--------------------------------------------------------------------------------
		// UpdateServerPlayer �� ������ blocking socket �̶�� ���� ������ ��!
		//--------------------------------------------------------------------------------
		bool bInsufficientData = false;

		while ( true ) {

			m_pInputStream->peek( &header[0] , szPacketHeader );
			memcpy( &packetID   , &header[0]          , szPacketID );
			memcpy( &packetSize , &header[szPacketID] , szPacketSize );

			if (bLog)
			{
				//cout << "packetID:" << packetID << ",packetSize:" << szPacketHeader + packetSize << endl;
				StringStream msg;
				msg << "packetID:" << packetID << ",packetSize:" << szPacketHeader + packetSize;
				filelog("badUser.txt", "%s", msg.toString().c_str());
			}

			switch ( packetID ) {

				case Packet::PACKET_CU_BEGIN_UPDATE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CUBeginUpdate[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUBeginUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_BEGIN_SESSION )
							throw InvalidProtocolException("invalid packet order");

						// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
						// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// ��Ŷ �ϳ��� �о�����, expire time �� �����Ѵ�.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// ������ Packet::read()�� ȣ���ϸ� ���ο��� ��Ŷ ����� ���� ������.
						// ���⼭�� ���� ������� �Ѵ�...
						m_pInputStream->skip( szPacketHeader );

						CUBeginUpdate cuBeginUpdate;
						cuBeginUpdate.read( *m_pInputStream );
						//cout << "before execute" << endl;

						if (bLog)
						{
							filelog("badUser.txt", "%s", cuBeginUpdate.toString().c_str());

							try {
								cuBeginUpdate.execute( this );
							} catch (Throwable& t) {
								filelog("badUser.txt", "%s", t.toString().c_str());
							}
						}
						else
						{
							cuBeginUpdate.execute( this );
						}	
						//cout << "after execute" << endl;
					}
					break;

				case Packet::PACKET_CU_REQUEST :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CURequest[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}

						if ( packetSize > CURequest::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE_LIST && 
							 m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE )
							throw InvalidProtocolException("invalid packet order");

						// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
						// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// ��Ŷ �ϳ��� �о�����, expire time �� �����Ѵ�.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;

						// ������ Packet::read()�� ȣ���ϸ� ���ο��� ��Ŷ ����� ���� ������.
						// ���⼭�� ���� ������� �Ѵ�...
						m_pInputStream->skip( szPacketHeader );

						CURequest cuRequest;
						cuRequest.read( *m_pInputStream );
						cuRequest.execute( this );
					}
					break;

				case Packet::PACKET_CU_END_UPDATE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET UCUpdate[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUEndUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE_LIST || 
							 m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE )
							throw InvalidProtocolException("invalid packet order");

						// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
						// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// ��Ŷ �ϳ��� �о�����, expire time �� �����Ѵ�.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// ������ Packet::read()�� ȣ���ϸ� ���ο��� ��Ŷ ����� ���� ������.
						// ���⼭�� ���� ������� �Ѵ�...
						m_pInputStream->skip( szPacketHeader );

						CUEndUpdate cuEndUpdate;
						cuEndUpdate.read( *m_pInputStream );
						cuEndUpdate.execute( this );
					}
					break;

				case Packet::PACKET_CU_REQUEST_LOGIN_MODE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CURequestLoginMode[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUEndUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_BEGIN_SESSION )
							throw InvalidProtocolException("invalid packet order");

						// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
						// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// ��Ŷ �ϳ��� �о�����, expire time �� �����Ѵ�.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// ������ Packet::read()�� ȣ���ϸ� ���ο��� ��Ŷ ����� ���� ������.
						// ���⼭�� ���� ������� �Ѵ�...
						m_pInputStream->skip( szPacketHeader );

						CURequestLoginMode cuRequestLoginMode;
						cuRequestLoginMode.read( *m_pInputStream );
						cuRequestLoginMode.execute( this );
					}
					break;

				default :
					{
						if (bLog)
						{
							//cout << "Invalid Packet ID!!!" << endl;
							filelog("badUser.txt", "Invalid Packet ID");
						}
						throw InvalidProtocolException("invalid packet id");
					}
			}

		}
	//}
	
	//} catch ( InsufficientDataException ) {
// by sigi. 2002.11.9
INSUFFICIENT_DATA:
	if (bInsufficientData)
	{
		// ���� ������ Ż�� ������ ���̴�. ������ ������ �ʿ�� ����.
		        // expire time �� �ʰ����� ��� ������ �����Ѵ�.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
			throw DisconnectException("���� �ð����� �Է����� ���� ���, ������ �����մϴ�.");

	}

//	__END_DEBUG

	__END_CATCH
}
		    

//--------------------------------------------------------------------------------
// ����� ���۸����� �ʱ� ������, �ƹ� �͵� ���� �ʾƵ� �ȴ�.
//--------------------------------------------------------------------------------
void UpdateServerPlayer::processOutput ()
	
{
	__BEGIN_TRY

	// do nothing

	__END_CATCH
}


//--------------------------------------------------------------------------------
// send packet to socket
//--------------------------------------------------------------------------------
void UpdateServerPlayer::sendPacket ( Packet * pPacket )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	__BEGIN_DEBUG

	//cout << "SEND PACKET " << pPacket->getPacketName().c_str() << " to "
//		<< m_pSocket->getHost().c_str() << ":" << m_pSocket->getPort() << endl;

	PacketID_t packetID = pPacket->getPacketID();
	PacketSize_t packetSize = pPacket->getPacketSize();
	m_pSocket->send( &packetID , szPacketID );
	m_pSocket->send( &packetSize , szPacketSize );
	// ��Ŷ�� ���Ͽ� ���� �Ѹ���.
	pPacket->write( m_pSocket );

	//cout << "Send Packet Size : " << pPacket->getPacketSize() << endl;
	//cout << "Send Buffer Size : " << m_pSocket->getSendBufferSize() << endl;

	__END_DEBUG

	__END_CATCH
}


//--------------------------------------------------------------------------------
// disconnect player
//--------------------------------------------------------------------------------
void UpdateServerPlayer::disconnect ( bool bDisconnected )
	
{
	__BEGIN_TRY

	if ( bDisconnected == UNDISCONNECTED ) {

		// ��� ���ۿ� �����ִ� ����Ÿ�� �����Ѵ�.
		m_pOutputStream->flush();

	}

	// ���� ������ �ݴ´�.
	m_pSocket->close();

	// �÷��̾��� ���¸� �α׾ƿ����� �����.
	Assert( m_PlayerStatus != USPS_END_SESSION );
	m_PlayerStatus = USPS_END_SESSION;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// get debug string
//
//--------------------------------------------------------------------------------
string UpdateServerPlayer::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "UpdateServerPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ",Port:" << m_pSocket->getPort() 
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
