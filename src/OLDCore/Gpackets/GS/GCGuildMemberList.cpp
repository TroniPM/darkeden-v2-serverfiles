//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGuildMemberList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCGuildMemberList.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGuildMemberList::GCGuildMemberList()
	throw()
{
	m_Type=0;
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGuildMemberList::~GCGuildMemberList()
	throw()
{
	__BEGIN_TRY
	
	// ��� ����Ʈ�� ��� ��ü�� ����
	clearGuildMemberInfoList();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_Type );

	BYTE ListNum;

	iStream.read( ListNum );
	for ( int i = 0; i < ListNum; i++ )
	{
		GuildMemberInfo* pGuildMemberInfo = new GuildMemberInfo();
		pGuildMemberInfo->read( iStream );
		m_GuildMemberInfoList.push_front( pGuildMemberInfo );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Type );
	BYTE ListNum = m_GuildMemberInfoList.size();
	oStream.write( ListNum );

	GuildMemberInfoListConstItor itr = m_GuildMemberInfoList.begin();
	for ( ; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		(*itr)->write( oStream );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::clearGuildMemberInfoList()
	throw()
{
	__BEGIN_TRY

	// GuildMemberInfoList �� �����Ѵ�
	while( !m_GuildMemberInfoList.empty() )
	{
		GuildMemberInfo* pGuildMemberInfo = m_GuildMemberInfoList.front();
		m_GuildMemberInfoList.pop_front();
		SAFE_DELETE( pGuildMemberInfo );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCGuildMemberList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCGuildMemberListHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCGuildMemberList::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t PacketSize = szBYTE + szBYTE;

	GuildMemberInfoListConstItor itr = m_GuildMemberInfoList.begin();

	for ( ; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCGuildMemberList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCGuildMemberList(";

	slist<GuildMemberInfo*>::const_iterator itr = m_GuildMemberInfoList.begin();
	for ( ; itr != m_GuildMemberInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

