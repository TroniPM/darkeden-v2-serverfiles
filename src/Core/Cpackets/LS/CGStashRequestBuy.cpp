//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashRequestBuy.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashRequestBuy.h"

void CGStashRequestBuy::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CGStashRequestBuy::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void CGStashRequestBuy::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGStashRequestBuyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGStashRequestBuy::toString () 
	
{
	StringStream msg;
	msg << "CGStashRequestBuy(" 
	    << ")";
	return msg.toString();
}
