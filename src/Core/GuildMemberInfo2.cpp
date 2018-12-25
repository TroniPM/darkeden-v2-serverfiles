//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildMemberInfo2.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GuildMemberInfo2.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GuildMemberInfo2::GuildMemberInfo2 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GuildMemberInfo2::~GuildMemberInfo2 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GuildMemberInfo2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szName;

	iStream.read( m_GuildID );
	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName size" );

	iStream.read( m_Name, szName );
	iStream.read( m_Rank );
	iStream.read( m_bLogOn );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GuildMemberInfo2::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	
	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szName > 20 )
		throw InvalidProtocolException( "too long szName size" );

	oStream.write( m_GuildID );
	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( m_Rank );
	oStream.write( m_bLogOn );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GuildMemberInfo2::getSize()
	throw()
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();

	PacketSize_t PacketSize = szGuildID + szBYTE + szName + szGuildMemberRank + szbool;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GuildMemberInfo2::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GuildMemberInfo2( "
		<< "GuildID:" << (int)m_GuildID
		<< ",Name:" << m_Name
		<< ",GuildMemberRank:" << (int)m_Rank
		<< ",LogOn:" << (int)m_bLogOn
		<< ")";

	return msg.toString();

	__END_CATCH
}

