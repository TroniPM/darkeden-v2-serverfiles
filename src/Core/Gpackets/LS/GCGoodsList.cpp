//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGoodsList.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCGoodsList.h"
#include "Assert.h"

#ifdef __GAME_SERVER__
	#include "Item.h"
	#include "ItemInfoManager.h"
	#include "Inventory.h"
	#include "AR.h"
	#include "SR.h"
	#include "SG.h"
	#include "SMG.h"
	#include "Belt.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GCGoodsList::GCGoodsList() 
	throw ()
{
	__BEGIN_TRY

	m_GoodsList.clear();
 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCGoodsList::~GCGoodsList() 
	throw ()
{
	__BEGIN_TRY

	list<GoodsInfo*>::iterator itr = m_GoodsList.begin();
	list<GoodsInfo*>::iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( *itr != NULL ) SAFE_DELETE(*itr);
	}

	m_GoodsList.clear();
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE totalNum;
	iStream.read( totalNum );
	if ( totalNum > MAX_GOODS_LIST ) throw DisconnectException("GCGoodsList : ���� ������ ������ �ʰ��߽��ϴ�.");

	for ( int i=0; i < totalNum ; ++i )
	{
		GoodsInfo* pGI = new GoodsInfo;

		iStream.read( pGI->objectID );
		iStream.read( pGI->itemClass );
		iStream.read( pGI->itemType );
		iStream.read( pGI->grade );

		BYTE optionNum;
		iStream.read( optionNum );

		pGI->optionType.clear();

		for ( int j=0; j < optionNum ; ++j )
		{
			OptionType_t optionType;
			iStream.read( optionType );
			pGI->optionType.push_back( optionType );
		}

		BYTE optionNum2;
		iStream.read( optionNum2 );

		pGI->optionType2.clear();

		for ( int j2=0; j2 < optionNum2 ; ++j2 )
		{
			OptionType_t optionType2;
			iStream.read( optionType2 );
			pGI->optionType2.push_back( optionType2 );
		}
		
		iStream.read( pGI->num );
		iStream.read( pGI->timeLimit );
		iStream.read(pGI->silver);
		iStream.read(pGI->enchantLevel);
		iStream.read(pGI->HeroOption );
		iStream.read(pGI->HeroOptionAttr );

		addGoodsInfo( pGI );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	BYTE totalNum = m_GoodsList.size();
	if ( totalNum > MAX_GOODS_LIST ) throw DisconnectException("GCGoodsList : ������ ������ Ʋ���Ծ����ϴ�.");

	oStream.write( totalNum );
	
	list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
	list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		GoodsInfo* pGI = *itr;
		Assert( pGI != NULL );

		oStream.write( pGI->objectID );
		oStream.write( pGI->itemClass );
		oStream.write( pGI->itemType );
		oStream.write( pGI->grade );
		
		BYTE optionNum = pGI->optionType.size();
		oStream.write( optionNum );

		list<OptionType_t>::const_iterator oitr = pGI->optionType.begin();
		list<OptionType_t>::const_iterator endoItr = pGI->optionType.end();

		for ( ; oitr != endoItr ; ++oitr )
		{
			oStream.write( *oitr );
		}

		BYTE optionNum2 = pGI->optionType2.size();
		oStream.write( optionNum2 );

		list<OptionType_t>::const_iterator oitr2 = pGI->optionType2.begin();
		list<OptionType_t>::const_iterator endoItr2 = pGI->optionType2.end();

		for ( ; oitr2 != endoItr2 ; ++oitr2 )
		{
			oStream.write( *oitr2 );
		}

		oStream.write( pGI->num );
		oStream.write( pGI->timeLimit );
		oStream.write( pGI->silver );
		oStream.write( pGI->enchantLevel );
		oStream.write( pGI->HeroOption );
		oStream.write( pGI->HeroOptionAttr );
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCGoodsList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCGoodsListHandler::execute( this , pPlayer );

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCGoodsList::getPacketSize () const 
	throw ()
{ 
	__BEGIN_TRY
	__BEGIN_DEBUG

	PacketSize_t size = szBYTE;

	list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
	list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		size += (*itr)->getPacketSize();
	}

	return size;

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCGoodsList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCGoodsList(";

	list<GoodsInfo*>::const_iterator itr = m_GoodsList.begin();
	list<GoodsInfo*>::const_iterator endItr = m_GoodsList.end();

	for ( ; itr != endItr ; ++itr )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	return msg.toString();
		
	__END_CATCH
}

