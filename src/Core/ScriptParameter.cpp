//////////////////////////////////////////////////////////////////////
// 
// Filename    : ScriptParameter.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ScriptParameter.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ScriptParameter::ScriptParameter() 
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ScriptParameter::~ScriptParameter()  
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void ScriptParameter::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY

	BYTE szName, szValue;

	iStream.read( szName );
	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );

	iStream.read( m_Name, szName );

	iStream.read( szValue );
	if ( szValue == 0 )
		throw InvalidProtocolException( "szValue == 0" );

	iStream.read( m_Value, szValue );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void ScriptParameter::write ( SocketOutputStream & oStream ) 
{
	__BEGIN_TRY
		
	BYTE szName = m_Name.size();
	BYTE szValue = m_Value.size();

	if ( szName == 0 )
		throw InvalidProtocolException( "szName == 0" );
	if ( szValue == 0 )
		throw InvalidProtocolException( "szValue == 0" );

	oStream.write( szName );
	oStream.write( m_Name );
	oStream.write( szValue );
	oStream.write( m_Value );

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ScriptParameter::getSize() 
{
	__BEGIN_TRY

	BYTE szName = m_Name.size();
	BYTE szValue = m_Value.size();

	PacketSize_t PacketSize = szBYTE + szName + szBYTE + szValue;

	return PacketSize;

	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ScriptParameter::toString () 
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ScriptParameter( "
		<< "Name:" << m_Name
		<< ",Value:" << m_Value
		<< ")";

	return msg.toString();

	__END_CATCH

	return NULL;
}

