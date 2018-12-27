//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCKnocksTargetBackOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK1::GCKnocksTargetBackOK1 ()
     
{
	__BEGIN_TRY

	m_ObjectID = 0;
	m_BulletNum = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK1::~GCKnocksTargetBackOK1 ()
    
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK1::read ( SocketInputStream & iStream )
	 
{
	__BEGIN_TRY
		
	iStream.read( m_SkillType );
	iStream.read( m_dir );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_ObjectID );
	iStream.read( m_BulletNum );
	iStream.read( m_bSuccess);

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK1::write ( SocketOutputStream & oStream )
     
{
	__BEGIN_TRY
		
	oStream.write( m_SkillType);
	oStream.write( m_dir );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_ObjectID );
	oStream.write( m_BulletNum );
	oStream.write( m_bSuccess);

	ModifyInfo::write( oStream);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK1::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCKnocksTargetBackOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCKnocksTargetBackOK1::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCKnocksTargetBackOK1("
		<< "ObjectID:"   << (int)m_ObjectID
		<< ",BulletNum:" << (int)m_BulletNum
		<< ",(DIR,X,Y):" << (int)m_dir <<(int)m_X<<(int)m_Y
		<< ",Success:"   << (int)m_bSuccess
		<< ModifyInfo::toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}


