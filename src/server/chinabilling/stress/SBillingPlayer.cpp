////////////////////////////////////////////////////////////////
//
// filename		: SBillingPlayer.cpp
//
////////////////////////////////////////////////////////////////

// include files
#include "SBillingPlayer.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"
#include "SBillingPlayerManager.h"

#include "CBillingPacketHeader.h"
#include "CBillingPacketErrorBody.h"

#include "PayUser.h"
#include "PayUserManager.h"
#include "CBillingPacketRequestLoginBody.h"
#include "CBillingPacketResponseLoginBody.h"
#include "CBillingPacketRequestMinusPointBody.h"
#include "CBillingPacketRequestMinusMinuteBody.h"
#include "CBillingPacketRequestLogoutBody.h"
#include "CBillingPacketRequestIntervalValidationBody.h"
#include "CBillingPacketResponseMinusPointBody.h"
#include "CBillingPacketResponseMinusMinuteBody.h"
#include "CBillingPacketResponseLogoutBody.h"
#include "CBillingPacketResponseIntervalValidationBody.h"

const int defaultSBillingPlayerInputStreamSize = 10240;
const int defaultSBillingPlayerOutputStreamSize = 10240;

// constructor
SBillingPlayer::SBillingPlayer()
	throw ( Error )
{
}

// constructor
SBillingPlayer::SBillingPlayer( Socket* pSocket )
	throw ( Error )
{
	__BEGIN_TRY

	Assert( pSocket != NULL );
	m_pSocket = pSocket;

	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket, defaultSBillingPlayerInputStreamSize );
	Assert( m_pInputStream != NULL );

	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket, defaultSBillingPlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );

	__END_CATCH
}

// destructor
SBillingPlayer::~SBillingPlayer()
	throw ( Error )
{
	__BEGIN_TRY

	// delete socket intput stream
	SAFE_DELETE( m_pInputStream );

	// delete socket output stream
	SAFE_DELETE( m_pOutputStream );

	// delete socket
	if ( m_pSocket != NULL )
	{
		m_pSocket->close();
		SAFE_DELETE( m_pSocket );

		filelog( LOGFILE_CBILLING_PLAYER, "Close Socket" );
	}

	__END_CATCH
}

void SBillingPlayer::processInput()
	throw ( IOException, Error )
{
	__BEGIN_TRY

	try
	{
		m_pInputStream->fill();
	}
	catch ( NonBlockingIOException& nbie )
	{
	}

	__END_CATCH
}

void SBillingPlayer::processOutput()
	throw ( IOException, Error )
{
	__BEGIN_TRY

	try
	{
		m_pOutputStream->flush();
	}
	catch ( InvalidProtocolException& )
	{
		throw DisconnectException( "�̻��� ��Ŷ��" );
	}

	__END_CATCH
}

// parse packet and execute packet handler
void SBillingPlayer::processCommand()
	throw ( IOException, Error )
{
	__BEGIN_TRY

	try
	{
		// �Է� ���ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while ( true )
		{
			// ����� ������ ���� ����
			CBillingPacketHeader header;

			// �ϴ� ����� �д´�. peek. �Է¹��ۿ��� �������� �ʴ´�.
			// ����� �������� ������ �н�
			if ( !m_pInputStream->peek( (char*)&header, szCBillingPacketHeaderInfo ) )
				return;

			header.Version_No  = ntohl( header.Version_No );
			header.Packet_Type = ntohl( header.Packet_Type );
			header.Method_Code = ntohl( header.Method_Code );
			header.Return_Code = ntohl( header.Return_Code );
			header.Body_Length = ntohl( header.Body_Length );

			////////////////////////////////////////////////////////////////////////////////////
			// Packet_Type, Method_Code, Return_Code �� ���� �ٵ� ������ �����ϴ��� Ȯ���Ѵ�.
			////////////////////////////////////////////////////////////////////////////////////
			if ( header.Packet_Type != CBILLING_PACKET_RESPONSE )
			{
				cout << "error" << endl;
				cout << header.toString().c_str() << endl;
				return;
				// ������ ����~
			}

			// ������ ���
			if ( header.Return_Code != CBILLING_RETURN_CODE_SUCCESS )
			{
				// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
				if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketErrorBodyInfo )
					return;

				// ���� ������ ������ �о� ����.
				CBillingPacketErrorBody body;
				header.read( *m_pInputStream );
				body.read( *m_pInputStream );

				executeError( header, body );
			}
			else // ������ ���
			{
				switch ( header.Method_Code )
				{
				case CBILLING_METHOD_CODE_INTERVAL_VALIDATION:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseIntervalValidationBodyInfo )
							return;
						
						// ���� ������ ������ �о� ����.
						CBillingPacketResponseIntervalValidationBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeIntervalValidation( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_LOGIN :
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseLoginBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseLoginBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeLogin( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_MINUS_POINT:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseMinusPointBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseMinusPointBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeMinusPoint( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_MINUS_MINUTE:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseMinusMinuteBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseMinusMinuteBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeMinusMinute( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_LOGOUT:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseLogoutBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseLogoutBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeLogout( header, body );

						break;
					}
				default:
					{
						throw Error( "Invaild Code" );

						// ������.
						break;
					}
				}
			}
		}
	}
	catch ( NoSuchElementException& nsee )
	{
		throw Error( nsee.toString() );
	}
	catch ( InsufficientDataException )
	{
		// do nothing
	}

	__END_CATCH
}

// send packet to player's output buffer
void SBillingPlayer::sendPacket( Packet* pPacket )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	//pPacket->write( *m_pOutputStream );

	__END_CATCH
}

// disconnect
void SBillingPlayer::disconnect( bool bDisconnected )
	throw ( InvalidProtocolException, Error )
{
	__BEGIN_TRY

	try
	{
		if ( bDisconnected == UNDISCONNECTED )
		{
			m_pOutputStream->flush();
		}

		m_pSocket->close();
	}
	catch ( InvalidProtocolException& t )
	{
		cerr << "SBillingPlayer::disconnect Exception occur!!" << endl;
		cerr << t.toString() << endl;
		m_pSocket->close();
	}

	__END_CATCH
}

// set socket
void SBillingPlayer::setSocket( Socket* pSocket )
	throw ()
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	SAFE_DELETE( m_pInputStream );
	m_pInputStream = new SocketInputStream( m_pSocket );

	SAFE_DELETE( m_pOutputStream );
	m_pOutputStream = new SocketOutputStream( m_pSocket );

	__END_CATCH
}

// send interval validation packet
void SBillingPlayer::sendIntervalValidation()
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestIntervalValidationBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_INTERVAL_VALIDATION;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestIntervalValidationBodyInfo;

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Interval Validation : " << body.Parameter_Value << " min" << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Interval Validation : %s\n%s\n%s", body.Parameter_Value, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send login packet
void SBillingPlayer::sendLogin( PayUser* pPayUser )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestLoginBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_LOGIN;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestLoginBodyInfo;

	strcpy( body.Login_Name, pPayUser->getName().c_str() );
	strcpy( body.Player_IP, pPayUser->getName().c_str() );
	strcpy( body.Player_MAC, pPayUser->getName().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );
	pPayUser->setSendTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Login : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Login : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send minus point packet
void SBillingPlayer::sendMinusPoint( PayUser* pPayUser )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestMinusPointBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_MINUS_POINT;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestMinusPointBodyInfo;

	strcpy( body.Login_Name, pPayUser->getName().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );
	pPayUser->setSendTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Minus Point : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Minus Point : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send minus minute packet
void SBillingPlayer::sendMinusMinute( PayUser* pPayUser )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestMinusMinuteBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_MINUS_MINUTE;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestMinusMinuteBodyInfo;

	strcpy( body.Login_Name, pPayUser->getName().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );
	pPayUser->setSendTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Minus Minute : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Minus Minute : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send logout packet
void SBillingPlayer::sendLogout( PayUser* pPayUser )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestLogoutBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_LOGOUT;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestLogoutBodyInfo;

	strcpy( body.Login_Name, pPayUser->getName().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );
	pPayUser->setSendTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Logout : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Logout : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	// ���� ������ ©����~
	PayUser* pPayUser = g_pPayUserManager->getUser( body.Login_Name );
	pPayUser->setRecvTime();
	pPayUser->setLeftTime( 0 );

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Error : " << body.Login_Name << endl;
	cout << body.Return_Message << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Error : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	if ( atoi(body.Parameter_Value) != g_pSBillingPlayerManager->getMinusIntervalInt() )
	{
		// ���Ӽ����� �߱� ���� �������� minus interval �� ���� �ʴ�. �׾�� �Ѵ�.
		cerr << "-------------------------------------------------------------------------------" << endl;
		cerr << "Interval configuration is different between gameserver and china billing server" << endl;
		cerr << "gameserver interval : " << g_pSBillingPlayerManager->getMinusIntervalInt() << ", china billing server interval : " << body.Parameter_Value << endl;
		cerr << "-------------------------------------------------------------------------------" << endl;

		filelog( LOGFILE_CBILLING_ERROR, "Different Interval between gameserver and china billing server\ngameserver interval : %d, china billing server interval : %s", g_pSBillingPlayerManager->getMinusIntervalInt(), body.Parameter_Value );

		// �׾��. ���� �Ф�.
		//kill( getpid(), 9 );
	}

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Interval Validation : " << body.Parameter_Value << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Interval Validation : %s\n%s\n%s", body.Parameter_Value, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	PayUser* pPayUser = g_pPayUserManager->getUser( body.Login_Name );
	pPayUser->setRecvTime();

	if ( body.Free_Left_Time + body.Rating_Left_Time <= 0 )
		pPayUser->setLeftTime( 0 );

	// disconnect if no Left Time
#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Login OK : " << body.Login_Name << " has no left time. DISCONNECT" << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s has no left time. DISCONNECT\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

#ifdef __Cout_CBILLING_SYSTEM__
	//	cout << "----------------------------------------------------------------" << endl;
	//	cout << "Response Login OK : " << body.Login_Name << endl;
	//	cout << header.toString().c_str() << endl;
	//	cout << body.toString().c_str() << endl;
#endif
	//	filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	PayUser* pPayUser = g_pPayUserManager->getUser( body.Login_Name );
	pPayUser->setRecvTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Minus Point : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Minus Point : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	PayUser* pPayUser = g_pPayUserManager->getUser( body.Login_Name );
	pPayUser->setRecvTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Minus Minute : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Minus Minute : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void SBillingPlayer::executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	PayUser* pPayUser = g_pPayUserManager->getUser( body.Login_Name );
	pPayUser->setRecvTime();

#ifdef __Cout_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Logout OK : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Logout OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// get debug string
string SBillingPlayer::toString() const
	throw ( Error )
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SBillingPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET()
		<< ",Host:"<< m_pSocket->getHost()
		<< ",ID:" << m_ID
		<< ")";

	return msg.toString();

	__END_CATCH
}

