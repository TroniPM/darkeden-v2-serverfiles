//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestIP.cpp 
// Written By  :
// Description :
// ������ ���ϴ� ����� IP ��û
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestIP.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestIP member methods
//////////////////////////////////////////////////////////////////////////////

CGRequestIP::CGRequestIP () 
     
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGRequestIP::~CGRequestIP () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGRequestIP::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	BYTE num;
	iStream.read( num );

	if (num > 0)
	{
		iStream.read( m_Name, num );
	}

	__END_CATCH
}
		    
void CGRequestIP::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
		
	BYTE num = m_Name.size();
	oStream.write( num );

	if (num > 0)
	{
		oStream.write( m_Name );
	}

	__END_CATCH
}

void CGRequestIP::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	CGRequestIPHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string CGRequestIP::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGRequestIP( "
		<< ",Name: " << m_Name			
		<< ")";
	return msg.toString();

	__END_CATCH
}
