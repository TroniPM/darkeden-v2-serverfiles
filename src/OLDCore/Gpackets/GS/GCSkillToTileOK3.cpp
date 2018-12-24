//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK3.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToTileOK3.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK3::GCSkillToTileOK3 () 
     throw ()
{
	__BEGIN_TRY

//	m_CListNum = 0;
	m_Grade = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK3::~GCSkillToTileOK3 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_SkillType );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Grade );
/*	
	iStream.read( m_Duration );
	iStream.read( m_CListNum );

	ObjectID_t m_Value;

	for( int i = 0; i < m_CListNum; i++ ) {
		iStream.read( m_Value );
		m_CList.push_back(m_Value);
	}
*/
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Grade );
/*	
	oStream.write( m_Duration );
	oStream.write( m_CListNum );

	for ( list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		oStream.write( *itr );
	}
*/
	__END_CATCH
}
/*
//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK3::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3::addCListElement( ObjectID_t ObjectID )
	throw()
{
	__BEGIN_TRY

	// Creature ID�� �߰��Ѵ�.
	m_CList.push_back( ObjectID );

	// ũ��ó ID count�� ������Ų��.
	m_CListNum++;

	__END_CATCH

}
*/
/*
//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK3::deleteCListElement()
// 
// Creature List�� ��Ҹ� ���ﶧ �ʿ��� ��� �Լ�.
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3::deleteCListElement()
	throw()
{
	__BEGIN_TRY

	// ũ���� ���̵� �ϳ� �����.
	m_CList.pop_front();
	
	// ũ��ó ����Ʈ ī���͸� �ϳ� �����.
	m_CListNum--;

	__END_CATCH
}
*/

//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK3::execute()
// 
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK3::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToTileOK3Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToTileOK3::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToTileOK3("
		<< "SkillType:" << (int)m_SkillType 
		<< ",ObjectID:" << (int)m_ObjectID
		<< ",Grade:" << (int)m_Grade;
	msg << ")";
	return msg.toString();

	__END_CATCH
}


