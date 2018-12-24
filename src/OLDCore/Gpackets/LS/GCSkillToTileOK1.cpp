//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToTileOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK1::GCSkillToTileOK1 () 
     throw ()
{
	__BEGIN_TRY

	m_CListNum = 0;
	m_Grade = 0;


	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToTileOK1::~GCSkillToTileOK1 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_SkillType );
	iStream.read( m_CEffectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Duration );
	iStream.read( m_Range);
	iStream.read( m_Grade );
	
	iStream.read( m_CListNum );

	ObjectID_t m_Value;
	int i;

	for( i = 0; i < m_CListNum; i++ ) {
		iStream.read( m_Value );
		m_CList.push_back( m_Value );
	}

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_CEffectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Duration );
	oStream.write( m_Range);
	oStream.write( m_Grade );
	
	oStream.write( m_CListNum );
	for ( list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		oStream.write( *itr );
	}

	ModifyInfo::write( oStream);
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK1::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::addCListElement( ObjectID_t ObjectID )
	throw()
{
	__BEGIN_TRY

	// Creature ID�� �߰��Ѵ�.
	m_CList.push_back( ObjectID );

	// ũ��ó ID count�� ������Ų��.
	m_CListNum++;

	__END_CATCH

}

/*
//////////////////////////////////////////////////////////////////////
//
// GCSkillToTileOK1::deleteCListElement()
// 
// Creature List�� ��Ҹ� ���ﶧ �ʿ��� ��� �Լ�.
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::deleteCListElement()
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
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToTileOK1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToTileOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToTileOK1::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCSkillToTileOK1("
		<< "SkillType:" << (int)m_SkillType 
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",X:"  << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Duration:" << (int)m_Duration 
		<< ",Range:"<< (int)m_Range 
		<< ",Grade:" << (int)m_Grade 
		<< ",CListNum:" << (int)m_CListNum 
		<< "CListSet(";

	for ( list<ObjectID_t>::const_iterator itr = m_CList.begin(); itr!= m_CList.end() ; itr++ ) {
		msg << (int)(*itr) << ","; 
	}

	msg << ")";

	msg << ModifyInfo::toString();

	msg << ")";

	return msg.toString();

	__END_CATCH
}


