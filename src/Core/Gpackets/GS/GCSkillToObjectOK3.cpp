//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK3.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToObjectOK3.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK3::GCSkillToObjectOK3 () 
     throw ()
{
	__BEGIN_TRY
	m_Grade = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK3::~GCSkillToObjectOK3 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_SkillType );
	iStream.read( m_TargetX);
	iStream.read( m_TargetY);
	iStream.read( m_Grade);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_TargetX);
	oStream.write( m_TargetY);
	oStream.write( m_Grade);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToObjectOK3Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToObjectOK3::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToObjectOK3("
		<< "SkillType:" << (int)m_SkillType 
		<< ",ObjectID:" << (int)m_ObjectID 
		<< ",TargetXY:" << m_TargetX << "," << m_TargetY 
		<< ",Grade:" << m_Grade 
		<< ")";
	return msg.toString();

	__END_CATCH
}
