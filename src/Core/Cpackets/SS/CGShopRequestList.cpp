//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestList.cpp 
// Written By  : �輺��
// Description :
// �÷��̾ ������ �ִ� ���� ������ ������ ������ �մ� ������ 
// ������ �ٸ� ���, �÷��̾�� �������� ��ǰ�� ����Ʈ�� 
// ��û�ϰ� �ȴ�. �� ��Ŷ�� �׶� ������ �Ǵ� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestList.h"

void CGShopRequestList::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_RackType);

	__END_CATCH
}
		    
void CGShopRequestList::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_RackType);

	__END_CATCH
}

void CGShopRequestList::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGShopRequestListHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGShopRequestList::toString () 
	
{
	StringStream msg;
	msg << "CGShopRequestList(" 
	    << "ObjectID:" << (int)m_ObjectID 
	    << "RackType:" << (int)m_RackType
	    << ")";
	return msg.toString();
}
