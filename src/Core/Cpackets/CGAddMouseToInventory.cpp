//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToInventory.h"

CGAddMouseToInventory::CGAddMouseToInventory () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddMouseToInventory::~CGAddMouseToInventory () 
    throw ()
{
	__BEGIN_TRY
	m_InventoryItemObjectID = 0;
	__END_CATCH
}

void CGAddMouseToInventory::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_InventoryItemObjectID);
	iStream.read(m_InvenX);
	iStream.read(m_InvenY);

	__END_CATCH
}

void CGAddMouseToInventory::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_InventoryItemObjectID);
	oStream.write(m_InvenX);
	oStream.write(m_InvenY);

	__END_CATCH
}

void CGAddMouseToInventory::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddMouseToInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddMouseToInventory::toString () 
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddMouseToInventory("
		<< "ObjectID2:"    << (int)m_ObjectID 
		<< "ObjectID:"    << (int)m_InventoryItemObjectID 
		<< ",InventoryX:" << (int)m_InvenX 
		<< ",InventoryY:" << (int)m_InvenY 
		<< ")";
	return msg.toString();

	__END_CATCH
}
