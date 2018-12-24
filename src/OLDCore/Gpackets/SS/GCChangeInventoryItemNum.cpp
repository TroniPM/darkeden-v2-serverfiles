//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeInventoryItemNum.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCChangeInventoryItemNum.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCChangeInventoryItemNum::GCChangeInventoryItemNum () 
     throw ()
{
	__BEGIN_TRY
	m_ChangedItemListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCChangeInventoryItemNum::~GCChangeInventoryItemNum () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_ChangedItemListNum );

	int i;
	ObjectID_t item;
	ItemNum_t num;
	
	for( i = 0; i < m_ChangedItemListNum; i++ ) {
		iStream.read( item);
		m_ChangedItemList.push_back( item);
	}
	for( i = 0; i < m_ChangedItemListNum; i++ ) {
		iStream.read( num);
		m_ChangedItemNumList.push_back( num);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ChangedItemListNum );

    for ( list<ObjectID_t>:: const_iterator itr = m_ChangedItemList.begin(); itr!= m_ChangedItemList.end(); itr++) {
		oStream.write(*itr);
	}
    for ( list<ItemNum_t>:: const_iterator itr2 = m_ChangedItemNumList.begin(); itr2!= m_ChangedItemNumList.end(); itr2++) {
		oStream.write(*itr2);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCChangeInventoryItemNum::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::addChangedItemListElement( ObjectID_t id, ItemNum_t num)
	throw()
{
	__BEGIN_TRY

	// ���ϴ� ���� �������� List�� �ִ´�.
	m_ChangedItemList.push_back( id);
	m_ChangedItemNumList.push_back( num);

	// ��ȭ ���� ������ �ϳ� ���� ��Ų��.
	m_ChangedItemListNum++;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCChangeInventoryItemNum::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Changed ListNum:" << (int)m_ChangedItemListNum 
		<< " ChangedListSet(";

	int i;
	list<ObjectID_t>::const_iterator itrItem = m_ChangedItemList.begin();
	list<ItemNum_t>::const_iterator itrItemNum = m_ChangedItemNumList.begin();
	for( i = 0; i < m_ChangedItemListNum; i++)
	{
		msg << "(" << (int)(*itrItem) << ","<<(int)(*itrItemNum)<<"),";
		itrItem++;
		itrItemNum++;
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

