//////////////////////////////////////////////////////////////////////
// 
// Filename    : GSQuitGuild.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GSQuitGuild.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GSQuitGuild::read ( SocketInputStream& iStream ) 
	 throw ( ProtocolException , Error )
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
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GSQuitGuild::write ( SocketOutputStream& oStream ) const 
     throw ( ProtocolException , Error )
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

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GSQuitGuild::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GSQuitGuildHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GSQuitGuild::toString () const
    throw ()
{
	StringStream msg;

	msg << "GSQuitGuild ("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< " )";

	return msg.toString();
}

