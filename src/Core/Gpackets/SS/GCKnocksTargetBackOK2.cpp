//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK2.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

#include "GCKnocksTargetBackOK2.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK2::GCKnocksTargetBackOK2 ()
     throw ()
{
	__BEGIN_TRY


	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCKnocksTargetBackOK2::~GCKnocksTargetBackOK2 ()
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK2::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_SkillType);
	iStream.read( m_dir );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_ObjectID );

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK2::write ( SocketOutputStream & oStream )
     
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_SkillType);
	oStream.write( m_dir );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_ObjectID );

	ModifyInfo::write( oStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCKnocksTargetBackOK2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCKnocksTargetBackOK2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCKnocksTargetBackOK2::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCKnocksTargetBackOK2("
		<< "ObjectID: " << (int)m_ObjectID
		<< "(Dir,X,Y):" << (int)m_dir << "," << (int)m_X << "," <<(int)m_Y
		<< ModifyInfo::toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}


