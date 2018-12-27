//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK5.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCKnocksTargetBackOK5.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK5::GCKnocksTargetBackOK5 ()
     
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	__END_DEBUG
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK5::~GCKnocksTargetBackOK5 ()
    
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::read ( SocketInputStream & iStream )
	 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
//	iStream.read( m_X);
//	iStream.read( m_Y );
	iStream.read( m_bSuccess);

	iStream.read( m_SkillType);
	iStream.read( m_dir);
	iStream.read( m_X);
	iStream.read( m_Y);
	__END_DEBUG
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::write ( SocketOutputStream & oStream )
     
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
//	oStream.write( m_X);
//	oStream.write( m_Y);
	oStream.write( m_bSuccess);
	
	oStream.write( m_SkillType);
	oStream.write( m_dir);
	oStream.write( m_X);
	oStream.write( m_Y);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK5::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCKnocksTargetBackOK5Handler::execute( this , pPlayer );
		
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCKnocksTargetBackOK5::toString () 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	StringStream msg;
	msg << "GCKnocksTargetBackOK5("
		<< "ObjectID:" << (int)m_ObjectID 
		<< ",TargetObjectID: " << (int)m_TargetObjectID 
		<< ",Success:"<< (int)m_bSuccess
		<< ",(Dir,X,Y) : " << (int)m_dir << "," << (int)m_X << "," << (int)m_Y
		<< ")";
	return msg.toString();

	__END_DEBUG
	__END_CATCH
}
