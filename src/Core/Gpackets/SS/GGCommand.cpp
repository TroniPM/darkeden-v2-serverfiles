//////////////////////////////////////////////////////////////////////
// 
// Filename    : GGCommand.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GGCommand.h"


//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GGCommand::read ( Datagram & iDatagram ) 
	 
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read command
	//--------------------------------------------------
	BYTE szCommand;

	iDatagram.read( szCommand );

	if ( szCommand == 0 )
		throw InvalidProtocolException("szCommand == 0");

	if ( szCommand > 80 )
		throw InvalidProtocolException("too long Command length");

	iDatagram.read( m_Command , szCommand );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GGCommand::write ( Datagram & oDatagram ) const 
     
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write client IP
	//--------------------------------------------------
	BYTE szCommand = m_Command.size();

	if ( szCommand == 0 )
		throw InvalidProtocolException("szCommand == 0");

	if ( szCommand > 80 )
		throw InvalidProtocolException("too long Command length");

	oDatagram.write( szCommand );

	oDatagram.write( m_Command );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GGCommand::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GGCommandHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GGCommand::toString () const
    
{
	StringStream msg;

	msg << "GGCommand("
		<< m_Command 
		<< ")";

	return msg.toString();
}

