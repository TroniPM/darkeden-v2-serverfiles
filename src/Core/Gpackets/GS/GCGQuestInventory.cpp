//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGQuestInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCGQuestInventory.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGQuestInventory::GCGQuestInventory () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCGQuestInventory::~GCGQuestInventory () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void GCGQuestInventory::read(SocketInputStream & iStream) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE size;
	iStream.read(size);

	for ( int i=0; i<size; ++i )
	{
		ItemType_t item;
		iStream.read(item);
		m_ItemList.push_back(item);
	}

	__END_CATCH
}

void GCGQuestInventory::write(SocketOutputStream & oStream) 
{
	__BEGIN_TRY

	BYTE size = m_ItemList.size();
	oStream.write(size);

	//cout << "����Ʈ �κ��丮 ���� : " << (int)size << endl;

	list<ItemType_t>::const_iterator itr = m_ItemList.begin();
	list<ItemType_t>::const_iterator endItr = m_ItemList.end();

	for ( ; itr != endItr ; ++itr )
	{
		oStream.write( (*itr) );
		//cout << "	����Ʈ ������ : " << (int)(*itr) << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCGQuestInventory::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCGQuestInventoryHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCGQuestInventory::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCGQuestInventory("
		<< ")";
	return msg.toString();

	__END_CATCH
}

