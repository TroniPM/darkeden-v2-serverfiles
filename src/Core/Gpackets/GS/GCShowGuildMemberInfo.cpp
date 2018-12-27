//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildMemberInfo.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCShowGuildMemberInfo.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCShowGuildMemberInfo::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	BYTE szName, szGuildMemberIntro;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	iStream.read( m_Name, szName );
	iStream.read( m_GuildMemberRank );
	iStream.read( szGuildMemberIntro );

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "too long szGuildMemberIntro length" );

	if ( szGuildMemberIntro > 0 )
		iStream.read( m_GuildMemberIntro, szGuildMemberIntro );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCShowGuildMemberInfo::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	BYTE szGuildMemberIntro = m_GuildMemberIntro.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName length" );

	if ( szGuildMemberIntro > 256 )
		throw InvalidProtocolException( "too long szGuildMemberIntro length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_GuildMemberRank );
	oStream.write( szGuildMemberIntro );

	if ( szGuildMemberIntro > 0 )
		oStream.write( m_GuildMemberIntro );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCShowGuildMemberInfo::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCShowGuildMemberInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCShowGuildMemberInfo::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCShowGuildMemberInfo("
		<< "GuildID:" << m_GuildID
		<< "Name:" << m_Name
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< "GuildMemberIntro:" << m_GuildMemberIntro
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

