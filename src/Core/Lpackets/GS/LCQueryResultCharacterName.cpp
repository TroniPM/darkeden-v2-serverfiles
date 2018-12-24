//--------------------------------------------------------------------------------
// 
// Filename    : LCQueryResultCharacterName.cpp 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "LCQueryResultCharacterName.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void LCQueryResultCharacterName::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read player id
	//--------------------------------------------------
	BYTE szCharacterName;

	iStream.read( szCharacterName );

	if ( szCharacterName == 0 )
		throw InvalidProtocolException("szCharacterName == 0");

	if ( szCharacterName > 20 )
		throw InvalidProtocolException("too large CharacterName length");

	iStream.read( m_CharacterName , szCharacterName );

	//--------------------------------------------------
	// read id existence
	//--------------------------------------------------
	iStream.read( m_bExist );

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void LCQueryResultCharacterName::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write player id
	//--------------------------------------------------
	BYTE szCharacterName = m_CharacterName.size();

	if ( szCharacterName == 0 )
		throw InvalidProtocolException("empty CharacterName");

	if ( szCharacterName > 20 )
		throw InvalidProtocolException("too large CharacterName length");

	oStream.write( szCharacterName );

	oStream.write( m_CharacterName );

	//--------------------------------------------------
	// write id existence
	//--------------------------------------------------
	oStream.write( m_bExist );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void LCQueryResultCharacterName::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCQueryResultCharacterNameHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string LCQueryResultCharacterName::toString () const
	throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "LCQueryResultCharacterName("
		<< "CharacterName:" << m_CharacterName 
		<< ",Exist:" << m_bExist 
		<< ")";
	return msg.toString();
		
	__END_CATCH
}

