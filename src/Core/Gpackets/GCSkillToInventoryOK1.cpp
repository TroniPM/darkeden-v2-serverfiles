//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK1.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSkillToInventoryOK1.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::GCSkillToInventoryOK1 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToInventoryOK1::~GCSkillToInventoryOK1 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_SkillType );
	iStream.read( m_ObjectID );
	iStream.read( m_ItemClass );
	iStream.read( m_ItemType );
	iStream.read( m_CEffectID );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Duration );

	ModifyInfo::read( iStream);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
	oStream.write( m_ItemClass );
	oStream.write( m_ItemType );
	oStream.write( m_CEffectID );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Duration );
	ModifyInfo::write( oStream);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToInventoryOK1::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToInventoryOK1Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSkillToInventoryOK1::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToInventoryOK1("
		<< "SkillType:"  << (int)m_SkillType 
		<< ",ObjectID:"  << (int)m_ObjectID
		<< ",ItemClass: " << (int)m_ItemClass
		<< ",ItemType:"  << (int)m_ItemType
		<< ",CEffectID:" << (int)m_CEffectID 
		<< ",X:"         << (int)m_X
		<< ",Y:"         << (int)m_Y 
		<< ",Duration: " << (int)m_Duration;
	msg << ModifyInfo::toString();
	msg << ")";

	return msg.toString();

	__END_CATCH
}
