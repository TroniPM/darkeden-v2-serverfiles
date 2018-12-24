//--------------------------------------------------------------------------------
// 
// Filename    : GCAddMonsterCorpse.cpp
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "GCAddMonsterCorpse.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCAddMonsterCorpse::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE name_length = 0;
		
	iStream.read( m_ObjectID );
	iStream.read( m_MonsterType );

	iStream.read( name_length );
	if (name_length != 0) iStream.read(m_MonsterName, name_length);

	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );
	iStream.read( m_bhasHead );
	iStream.read( m_TreasureCount );
	iStream.read( m_LastKiller );
	iStream.read( m_Level );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCAddMonsterCorpse::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE name_length = m_MonsterName.size();
		
	oStream.write( m_ObjectID );
	oStream.write( m_MonsterType );

	oStream.write( name_length );
	if (m_MonsterName.size() != 0) oStream.write( m_MonsterName );

	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );
	oStream.write( m_bhasHead );
	oStream.write( m_TreasureCount );
	oStream.write( m_LastKiller );
	oStream.write( m_Level );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCAddMonsterCorpse::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddMonsterCorpseHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCAddMonsterCorpse::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddMonsterCorpse("
		<< "ObjectID:" << m_ObjectID
		<< ",MonsterType:" << (int)m_MonsterType
		<< ",MonsterName:" << m_MonsterName
		<< ",X:" << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Dir:" << Dir2String[m_Dir]
		<< ",hasHead:" << (int)m_bhasHead
		<< ",TreasureCount:" << (int)m_TreasureCount
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
