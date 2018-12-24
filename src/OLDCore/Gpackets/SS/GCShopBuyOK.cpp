//////////////////////////////////////////////////////////////////////////////
// Filename    : GCShopBuyOK.cpp 
// Written By  : �輺��
// Description : 
// �÷��̾ ���� NPC���� ���� ������ ��û���� ��, ����� 
// ������ �Ǹ� �� ��Ŷ�� �÷��̾�� ���ư���.
//////////////////////////////////////////////////////////////////////////////

#include "GCShopBuyOK.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GCShopBuyOK::GCShopBuyOK() 
	throw ()
{
	__BEGIN_TRY 

	m_ObjectID     = 0;
	m_Version      = 0;
	m_ItemObjectID = 0;
	m_ItemClass    = 0;
	m_ItemType     = 0;
	m_Durability   = 0;
	m_ItemNum      = 0;
	m_Silver       = 0;
	m_Grade       = 0;
	m_EnchantLevel = 0;
	m_Price        = 0;
	
	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCShopBuyOK::~GCShopBuyOK() 
	throw ()
{
	__BEGIN_TRY 
	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCShopBuyOK::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_Version);
	iStream.read(m_ItemObjectID);
	iStream.read(m_ItemClass);
	iStream.read(m_ItemType);

	BYTE optionSize;
	iStream.read(optionSize);
	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}

	iStream.read(m_Durability);
	iStream.read(m_ItemNum);
	iStream.read(m_Silver);
	iStream.read(m_Grade);
	iStream.read(m_EnchantLevel);
	iStream.read(m_Price);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCShopBuyOK::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_Version);
	oStream.write(m_ItemObjectID);
	oStream.write(m_ItemClass);
	oStream.write(m_ItemType);
	
	BYTE optionSize = m_OptionType.size();
	oStream.write(optionSize);
	list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
		oStream.write(optionType);
	}

	oStream.write(m_Durability);
	oStream.write(m_ItemNum);
	oStream.write(m_Silver);
	oStream.write(m_Grade);
	oStream.write(m_EnchantLevel);
	oStream.write(m_Price);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCShopBuyOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCShopBuyOKHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCShopBuyOK::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCShopBuyOK("
		<< "ObjectID:"     << (int)m_ObjectID << ","
	    << "Version:"      << (int)m_Version << ","
		<< "ItemObejctID:" << (int)m_ItemObjectID << ","
		<< "ItemClass:"    << (int)m_ItemClass << ","
		<< "ItemType:"     << (int)m_ItemType << ","
		<< "OptionTypeSize:"   << (int)m_OptionType.size() << ","
		<< "Durability:"   << (int)m_Durability << ","
		<< "ItemNum:"      << (int)m_ItemNum << ","
		<< "Silver:"       << (int)m_Silver << ","
		<< "Grade:"       << (int)m_Grade << ","
		<< "EnchantLEvel:" << (int)m_EnchantLevel << ","
		<< "Price:"        << (int)m_Price
		<< ")";
	return msg.toString();
		
	__END_CATCH
}


