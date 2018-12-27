//--------------------------------------------------------------------------------
// 
// Filename    : CUBeginUpdate.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CUBeginUpdate.h"
#include "Properties.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CUBeginUpdate::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	static WORD GuildVersion = atoi( g_pConfig->getProperty("GuildVersion").c_str() );
	static WORD KeyVersion = atoi( g_pConfig->getProperty("KeyVersion").c_str() );
	static WORD InfoVersion = atoi( g_pConfig->getProperty("InfoVersion").c_str() );

	iStream.read( m_Version );

	if ( m_Version >= GuildVersion )
	{
		iStream.read( m_GuildVersion );
		m_Type = TWO_VERSION_KEY_FRONT;
	}
	else if ( m_Version >= KeyVersion )
	{
		m_Type = ONE_VERSION_KEY_BACK;
	}
	else m_Type = OLD_UPDATE;

	if ( m_Version >= InfoVersion )
	{
		iStream.read( m_InfoVersion );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// �������κ��� ���� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CUBeginUpdate::read ( Socket * pSocket ) 
	
{
	__BEGIN_TRY

	static WORD GuildVersion = atoi( g_pConfig->getProperty("GuildVersion").c_str() );
	static WORD KeyVersion = atoi( g_pConfig->getProperty("KeyVersion").c_str() );
	static WORD InfoVersion = atoi( g_pConfig->getProperty("InfoVersion").c_str() );

	pSocket->receive( &m_Version , szWORD );

	if ( m_Version >= GuildVersion )
	{
		pSocket->receive( &m_GuildVersion, szWORD );
		m_Type = TWO_VERSION_KEY_FRONT;
	}
	else if ( m_Version >= KeyVersion )
	{
		m_Type = ONE_VERSION_KEY_BACK;
	}
	else m_Type = OLD_UPDATE;

	if ( m_Version >= InfoVersion )
	{
		pSocket->receive( &m_InfoVersion, szWORD );
	}

	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void CUBeginUpdate::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	oStream.write( m_Version );
	if ( m_Version >= atoi( g_pConfig->getProperty("GuildVersion").c_str() ) ) oStream.write( m_GuildVersion );
	if ( m_Version >= atoi( g_pConfig->getProperty("InfoVersion").c_str() ) ) oStream.write( m_InfoVersion );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CUBeginUpdate::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	CUBeginUpdateHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CUBeginUpdate::toString () const
	
{
	StringStream msg;

	msg << "CUBeginUpdate("
		<< "Version:" << m_Version
		<< "GuildVersion:" << m_GuildVersion
		<< "InfoVersion:" << m_InfoVersion
		<< ")";

	return msg.toString();
}
