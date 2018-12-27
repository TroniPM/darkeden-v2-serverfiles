//////////////////////////////////////////////////////////////////////
// 
// Filename    : SGAddGuildMemberOK.cpp 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SGAddGuildMemberOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void SGAddGuildMemberOK::read ( SocketInputStream& iStream ) 
	 
{
	__BEGIN_TRY

	iStream.read( m_GuildID );

	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name length" );

	iStream.read( m_Name, szName );
	iStream.read( m_GuildMemberRank );
	iStream.read( m_ServerGroupID );
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void SGAddGuildMemberOK::write ( SocketOutputStream& oStream ) const 
     
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long name size" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_GuildMemberRank );
	oStream.write( m_ServerGroupID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void SGAddGuildMemberOK::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	SGAddGuildMemberOKHandler::execute(this);
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string SGAddGuildMemberOK::toString () const
    
{
	StringStream msg;

	msg << "SGAddGuildMemberOK("
		<< "GuildID:" << (int)m_GuildID
		<< "Name:" << m_Name
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< ")";

	return msg.toString();
}

