//////////////////////////////////////////////////////////////////////
// 
// Filename    : SGModifyGuildIntroOK.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SGModifyGuildIntroOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::read ( SocketInputStream& iStream ) 
	 
{
	__BEGIN_TRY

	BYTE szGuildIntro;

	iStream.read( m_GuildID );
	iStream.read( szGuildIntro );

	if ( szGuildIntro > 255 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	if ( szGuildIntro > 0 )
		iStream.read( m_GuildIntro, szGuildIntro );
	else
		m_GuildIntro = "";

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::write ( SocketOutputStream& oStream ) const 
     
{
	__BEGIN_TRY

	BYTE szGuildIntro = m_GuildIntro.size();

	if ( szGuildIntro > 255 )
		throw InvalidProtocolException( "too long szGuildIntro length" );

	oStream.write( m_GuildID );
	oStream.write( szGuildIntro );

	if ( szGuildIntro > 0 )
		oStream.write( m_GuildIntro );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void SGModifyGuildIntroOK::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	SGModifyGuildIntroOKHandler::execute(this);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string SGModifyGuildIntroOK::toString () const
    
{
	StringStream msg;

	msg << "SGModifyGuildIntroOK("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildIntro:" << m_GuildIntro
		<< ")";

	return msg.toString();
}

