////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeAddItem.cpp 
// Written By  : �輺��
// Description :
////////////////////////////////////////////////////////////////////////////////

// include files
#include "GCTradeAddItem.h"
#include "Assert.h"

////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
GCTradeAddItem::GCTradeAddItem()
	throw()
{
	__BEGIN_TRY

	m_ListNum = 0;
	m_Grade=0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
GCTradeAddItem::~GCTradeAddItem()
	throw()
{
	__BEGIN_TRY

	while (!m_InfoList.empty())
	{
		SubItemInfo* pInfo = m_InfoList.front();
		SAFE_DELETE(pInfo);
		m_InfoList.pop_front();
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void GCTradeAddItem::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_TargetObjectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_ItemObjectID );
	iStream.read( m_ItemClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );
	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}

	BYTE optionSize2;
	iStream.read( optionSize2 );
	for (int i2=0; i2<optionSize2; i2++)
	{
		OptionType_t optionType2;
		iStream.read( optionType2 );
		addOptionType2( optionType2 );
	}

	iStream.read( m_Durability );
	iStream.read( m_ItemNum );
	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_EnchantLevel );
	iStream.read( m_HeroOption );
	iStream.read( m_HeroOptionAttr );
	iStream.read( m_ListNum );
	for (BYTE i = 0; i < m_ListNum; i++) 
	{
		SubItemInfo* pInfo = new SubItemInfo();
		pInfo->read( iStream );
		m_InfoList.push_back( pInfo );
	}
		
	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
////////////////////////////////////////////////////////////////////////////////
void GCTradeAddItem::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_TargetObjectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_ItemObjectID );
	oStream.write( m_ItemClass );
	oStream.write( m_ItemType );
	
	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );

	list<OptionType_t>::const_iterator iOption = m_OptionType.begin();
	for (; iOption!=m_OptionType.end(); iOption++)
	{
		OptionType_t optionType = *iOption;
		oStream.write( optionType );
	}

	BYTE optionSize2 = m_OptionType2.size();
	oStream.write( optionSize2 );
	list<OptionType_t>::const_iterator itr2 = m_OptionType2.begin();
	for (; itr2!=m_OptionType2.end(); itr2++)
	{
		OptionType_t optionType2 = *itr2;
		oStream.write( optionType2 );
	}

	oStream.write( m_Durability );
	oStream.write( m_ItemNum );
	oStream.write( m_Silver );
	oStream.write( m_Grade );
	oStream.write( m_EnchantLevel );
	oStream.write( m_HeroOption );
	oStream.write( m_HeroOptionAttr );
	oStream.write( m_ListNum );
	list<SubItemInfo*>::const_iterator itr = m_InfoList.begin();
	for (; itr!= m_InfoList.end(); itr++) 
	{
		Assert(*itr != NULL);
		(*itr)->write( oStream );
	}
	
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void GCTradeAddItem::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCTradeAddItemHandler::execute( this , pPlayer );

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get packet's debug string
////////////////////////////////////////////////////////////////////////////////
string GCTradeAddItem::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << " GCTradeAddItem("
		<< " TargetObjectID : " << (int)m_TargetObjectID 
		<< " ItemObjectID : "   << (int)m_ItemObjectID 
		<< " ItemClass : "      << (int)m_ItemClass 
		<< " ItemType : "       << (int)m_ItemType 
		<< " OptionTypeSize : "     << (int)m_OptionType.size()
		<< " Durability : "     << (int)m_Durability 
		<< " ItemNum : "        << (int)m_ItemNum 
		<< " Silver : "         << (int)m_Silver
		<< " Grade : "         << (int)m_Grade
		<< " EnchantLevel : "   << (int)m_EnchantLevel
		<< " ListNum : "        << (int)m_ListNum 
		<< " )";
	return msg.toString();
		
	__END_CATCH
}


