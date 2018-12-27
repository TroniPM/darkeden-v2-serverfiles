//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeAddItem.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeAddItem.h"

void CGTradeAddItem::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read(m_TargetObjectID);
	iStream.read(m_ItemObjectID);

	__END_CATCH
}

void CGTradeAddItem::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_TargetObjectID); 
	oStream.write(m_ItemObjectID ); 

	__END_CATCH
}

void CGTradeAddItem::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGTradeAddItemHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTradeAddItem::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGTradeAddItem(" 
		<< "TargetObjectID:" << (int)m_TargetObjectID
		<< ",ItemObjectID:" << (int)m_ItemObjectID
		<< ")";
	return msg.toString();

	__END_CATCH
}
