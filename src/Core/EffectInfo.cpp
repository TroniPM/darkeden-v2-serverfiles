//////////////////////////////////////////////////////////////////////
// 
// Filename    : EffectInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : ����Ʈ ���� ����Ʈ ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "EffectInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
EffectInfo::EffectInfo () 
     
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
EffectInfo::~EffectInfo () 
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void EffectInfo::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	clearList();

	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	BYTE listSize;
	iStream.read(listSize);

	for( int i = 0; i < listSize; i++ )
	{
		WORD effectID;
		iStream.read( effectID );
		DWORD len;
		iStream.read( len );

		addListElement( effectID, len );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void EffectInfo::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ListNum );

	list<pair<EffectID_t,DWORD> >::const_iterator itr = m_EList.begin();
	list<pair<EffectID_t,DWORD> >::const_iterator endItr = m_EList.end();

	for ( ; itr != endItr; ++itr )
	{
		oStream.write( (*itr).first );
		oStream.write( (*itr).second );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// EffectInfo::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void EffectInfo::addListElement( EffectID_t EffectID , DWORD Value )
	
{
	__BEGIN_TRY

	m_EList.push_back( pair<WORD,DWORD>(EffectID, Value) );

	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string EffectInfo::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectInfo( "
		<< ",ListNum: " << (int)m_ListNum 
		<< " ListSet(" ;
	list<pair<EffectID_t,DWORD> >::const_iterator itr = m_EList.begin();
	list<pair<EffectID_t,DWORD> >::const_iterator endItr = m_EList.end();

	for ( ; itr != endItr; ++itr )
	{
		msg << (int)(*itr).first << "," << (int)(*itr).second << ",";

	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

