//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddItemToZone.cc 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAddItemToZone.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCAddItemToZone::GCAddItemToZone() 
     
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCAddItemToZone::~GCAddItemToZone() 
    
{
	__BEGIN_TRY

	// �Ҽӵ� ��� ��ü���� �����Ѵ�.
	while ( !m_SubItemInfoList.empty() ) {
		SubItemInfo * pSubItemInfo = m_SubItemInfoList.front();
		SAFE_DELETE(pSubItemInfo);
		m_SubItemInfoList.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddItemToZone::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5( pEIStream->getEncryptCode(),
							pEIStream->readEncrypt( m_ObjectID ),
							pEIStream->readEncrypt( m_X ),
							pEIStream->readEncrypt( m_Y ),
							pEIStream->readEncrypt( m_ItemClass ),
							pEIStream->readEncrypt( m_ItemType ));
	}
	else
#endif
	{
		iStream.read( m_ObjectID );
		iStream.read( m_X );
		iStream.read( m_Y );
		iStream.read( m_ItemClass );
		iStream.read( m_ItemType );
	}

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

	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_Durability );
	iStream.read( m_EnchantLevel );
	iStream.read( m_HeroOption );
	iStream.read( m_HeroOptionAttr );
	iStream.read( m_ItemNum );

	// Sub ������ ������ �о� ���δ�.
    iStream.read( m_ListNum );
	for( int i = 0; i < m_ListNum; i++ ) {
		SubItemInfo * pSubItemInfo = new SubItemInfo();
		pSubItemInfo->read( iStream );
		m_SubItemInfoList.push_back( pSubItemInfo );
	}


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddItemToZone::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt( m_ObjectID ),
							pEOStream->writeEncrypt( m_X ),
							pEOStream->writeEncrypt( m_Y ),
							pEOStream->writeEncrypt( m_ItemClass ),
							pEOStream->writeEncrypt( m_ItemType ));
	}
	else
#endif
	{
		oStream.write( m_ObjectID );
		oStream.write( m_X );
		oStream.write( m_Y );
		oStream.write( m_ItemClass );
		oStream.write( m_ItemType );
	}

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );
	list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
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

	oStream.write( m_Silver );
	oStream.write( m_Grade );
	oStream.write( m_Durability );
	oStream.write( m_EnchantLevel );
	oStream.write( m_HeroOption );
	oStream.write( m_HeroOptionAttr );
	oStream.write( m_ItemNum );

	// Sub �������� ������ ����.
	oStream.write( m_ListNum );

    for ( list<SubItemInfo*>:: const_iterator itr = m_SubItemInfoList.begin(); itr!= m_SubItemInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}


	__END_CATCH
}
