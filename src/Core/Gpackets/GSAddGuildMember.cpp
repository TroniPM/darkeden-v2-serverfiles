//////////////////////////////////////////////////////////////////////
// 
// Filename    : GSAddGuildMember.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GSAddGuildMember.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GSAddGuildMember::read ( SocketInputStream& iStream ) 
	 
{
	__BEGIN_TRY

	BYTE szName, szGuildMemberIntro;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( " too long name length" );

	iStream.read( m_Name, szName );
	iStream.read( m_GuildMemberRank );
	iStream.read( szGuildMemberIntro );

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "too long Guild Member Intro" );

	if ( szGuildMemberIntro != 0 )
		iStream.read( m_GuildMemberIntro, szGuildMemberIntro );
	else
		m_GuildMemberIntro = "";

	iStream.read( m_ServerGroupID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GSAddGuildMember::write ( SocketOutputStream& oStream ) const 
     
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szGuildMemberIntro = m_GuildMemberIntro.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "too long GuildMemberIntro length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_GuildMemberRank );
	oStream.write( szGuildMemberIntro );

	if ( szGuildMemberIntro != 0 )
		oStream.write( m_GuildMemberIntro );

	oStream.write( m_ServerGroupID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GSAddGuildMember::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GSAddGuildMemberHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GSAddGuildMember::toString () const
    
{
	StringStream msg;

	msg << "GSAddGuildMember("
		<< "GuildID:" << m_GuildID
		<< "Name:" << m_Name
		<< "GuildMemberRank:" << m_GuildMemberRank
		<< "GuildMemberIntro:" << m_GuildMemberIntro
		<< ")";

	return msg.toString();
}

