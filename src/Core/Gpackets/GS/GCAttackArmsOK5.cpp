//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK5.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCAttackArmsOK5.h"
#include "skill/Skill.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK5::GCAttackArmsOK5 ()
     throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	m_SkillType = SKILL_ATTACK_ARMS;

	__END_DEBUG
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK5::~GCAttackArmsOK5 ()
    throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK5::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_SkillType );
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
//	iStream.read( m_X);
//	iStream.read( m_Y );
	iStream.read( m_bSuccess);

	__END_DEBUG
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK5::write ( SocketOutputStream & oStream )
     
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
//	oStream.write( m_X);
//	oStream.write( m_Y);
	oStream.write( m_bSuccess);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK5::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCAttackArmsOK5Handler::execute( this , pPlayer );
		
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAttackArmsOK5::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAttackArmsOK5("
		<< "SkillType:" << (int)m_SkillType 
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",TargetObjectID:" << (int)m_TargetObjectID 
		<< ",Success:"<< (int)m_bSuccess
		<< ")";
	return msg.toString();

	__END_CATCH
}
