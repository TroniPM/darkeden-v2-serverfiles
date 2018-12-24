//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillFailed2.cc 
// Written By  : elca@ewestsoft.com
// Description : Skill�� ���� ������ �����ִ� ��Ŷ�� ��� ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCSkillFailed2.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillFailed2::GCSkillFailed2 () 
     throw ()
{
	__BEGIN_TRY
	m_Grade = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillFailed2::~GCSkillFailed2 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
	iStream.read( m_SkillType );
	iStream.read( m_Grade );
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_Grade );
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillFailed2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillFailed2::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillFailed2("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",TargetObjectID:" << (int)m_TargetObjectID 
		<< ",SkillType:" << (int)m_SkillType
		<< ")" ;
	return msg.toString();

	__END_CATCH
}


