//////////////////////////////////////////////////////////////////////
// 
// Filename    : GSModifyGuildMember.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GSModifyGuildMember.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GSModifyGuildMember::read ( SocketInputStream& iStream ) 
	 
{
	__BEGIN_TRY

	BYTE szName, szSender;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	iStream.read( m_Name, szName );
	iStream.read( m_GuildMemberRank );
	iStream.read( szSender );

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender == 0" );
	if ( szSender > 20 )
		throw InvalidProtocolException( "too long sender length" );

	iStream.read( m_Sender, szSender );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GSModifyGuildMember::write ( SocketOutputStream& oStream ) const 
     
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szSender = m_Sender.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	if ( szSender == 0 )
		throw InvalidProtocolException( "szSender= 0" );
	if ( szSender > 20 )
		throw InvalidProtocolException( "too long szSender length" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_GuildMemberRank );
	oStream.write( szSender );
	oStream.write( m_Sender );


	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GSModifyGuildMember::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GSModifyGuildMemberHandler::execute(this, pPlayer);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GSModifyGuildMember::toString () const
    
{
	StringStream msg;

	msg << "GSModifyGuildMember ("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< "GuildMemberRank:" << m_GuildMemberRank
		<< "Sender:" << m_Sender
		<< " )";

	return msg.toString();
}

