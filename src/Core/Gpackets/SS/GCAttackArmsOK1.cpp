//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCAttackArmsOK1.h"
#include "skill/Skill.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK1::GCAttackArmsOK1 ()
     throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	m_ObjectID = 0;
	m_BulletNum = 0;
	m_SkillType = SKILL_ATTACK_ARMS;
	__END_DEBUG
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK1::~GCAttackArmsOK1 ()
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
void GCAttackArmsOK1::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	iStream.read( m_SkillType );
	iStream.read( m_ObjectID );
	iStream.read( m_BulletNum );
	iStream.read( m_bSuccess);

	ModifyInfo::read( iStream);

	__END_DEBUG
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK1::write ( SocketOutputStream & oStream )
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
	oStream.write( m_BulletNum );
	oStream.write( m_bSuccess);

	ModifyInfo::write( oStream);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCAttackArmsOK1Handler::execute( this , pPlayer );
		
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAttackArmsOK1::toString () 
	const throw ()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	StringStream msg;
	msg << "GCAttackArmsOK1("
		<< "SkillType:" << (int)m_SkillType
		<< "ObjectID:" << (int)m_ObjectID
		<< ",BulletNum:" << (int)m_BulletNum
		<< ",Success:" << (int)m_bSuccess
		<< ModifyInfo::toString()
		<< ")";
	return msg.toString();

	__END_DEBUG
	__END_CATCH
}


