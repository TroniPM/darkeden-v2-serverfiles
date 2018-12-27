//////////////////////////////////////////////////////////////////////
// 
// Filename    : SGGuildMemberLogOnOK.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SGGuildMemberLogOnOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::read ( SocketInputStream& iStream ) 
	 
{
	__BEGIN_TRY

	BYTE szName;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	iStream.read( m_Name, szName );
	iStream.read( m_bLogOn );
	iStream.read( m_ServerID );
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::write ( SocketOutputStream& oStream ) const 
     
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_bLogOn );
	oStream.write( m_ServerID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void SGGuildMemberLogOnOK::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	SGGuildMemberLogOnOKHandler::execute(this);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string SGGuildMemberLogOnOK::toString () const
    
{
	StringStream msg;

	msg << "SGGuildMemberLogOnOK("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< "LogOn:" << m_bLogOn
		<< "ServerID:" << m_ServerID
		<< ")";

	return msg.toString();
}

