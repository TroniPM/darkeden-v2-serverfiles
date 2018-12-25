//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUnionOfferList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCUnionOfferList.h"

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCUnionOfferList::~GCUnionOfferList()
    throw ()
{
    __BEGIN_TRY
    while (!m_UnionOfferList.empty())
    {
        SingleGuildUnionOffer* pUnionOffer = m_UnionOfferList.front();

        SAFE_DELETE(pUnionOffer);

        m_UnionOfferList.pop_front();
    }

    m_UnionOfferList.clear();

    __END_CATCH
}

PacketSize_t GCUnionOfferList::getPacketSize() 
{
	PacketSize_t ret = szBYTE;

	list<SingleGuildUnionOffer*>::const_iterator itr = m_UnionOfferList.begin();

	for ( ; itr != m_UnionOfferList.end() ; ++itr )
	{
		ret += (*itr)->getSize();
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCUnionOfferList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szNum;
	iStream.read(szNum);
	for ( int i=0; i<szNum; ++i )
	{
		SingleGuildUnionOffer* pInfo = new SingleGuildUnionOffer;
		pInfo->read(iStream);
		m_UnionOfferList.push_back(pInfo);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCUnionOfferList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szNum = m_UnionOfferList.size();
	oStream.write(szNum);

	list<SingleGuildUnionOffer*>::const_iterator itr = m_UnionOfferList.begin();

	for ( ; itr != m_UnionOfferList.end() ; ++itr )
	{
		(*itr)->write(oStream);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCUnionOfferList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCUnionOfferListHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCUnionOfferList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCUnionOfferList("
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

