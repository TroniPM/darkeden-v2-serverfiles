//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildWarInfo.cpp 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GuildWarInfo.h"

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GuildWarInfo::read ( SocketInputStream & iStream )
{
	__BEGIN_TRY

	WarInfo::read( iStream );
	iStream.read( m_CastleID );


	BYTE szName;
	iStream.read( szName );
	if ( szName > 0 ) iStream.read( m_AttackGuildName, szName );

	iStream.read( szName );
	if ( szName > 0 ) iStream.read( m_DefenseGuildName, szName );


	m_GuildIDs.read( iStream );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GuildWarInfo::write ( SocketOutputStream & oStream )
{
	__BEGIN_TRY

	WarInfo::write( oStream );
	oStream.write( m_CastleID );

	BYTE szName = m_AttackGuildName.size();
	oStream.write( szName );
	if ( szName > 0 ) oStream.write( m_AttackGuildName );

	szName = m_DefenseGuildName.size();
	oStream.write( szName );
	if ( szName > 0 ) oStream.write( m_DefenseGuildName );

	m_GuildIDs.write( oStream );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string GuildWarInfo::toString ()
{
	StringStream msg;

	msg << "GuildWarInfo("
		<< "CastleID:" << (int)m_CastleID
		<< ",AttackGuildName:" << m_AttackGuildName
		<< ",DefenseGuildName:" << m_DefenseGuildName
		<< ",RemainTime:" << (int)m_RemainTime
		<< ",Guilds:" << m_GuildIDs.toString()
		<< ")";

	return msg.toString();
}

