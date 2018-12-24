////////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSell.cpp 
// Written By  : �輺��
// Description : 
// �÷��̾�� �ڽ��� ������ �ִ� �������� ���� NPC����
// �ȱ⸦ ��û�� �� ���̴� ��Ŷ�̴�.
////////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestSell.h"

void CGShopRequestSell::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ObjectID);
	iStream.read(m_ItemObjectID);
	iStream.read(m_OpCode);

	__END_CATCH
}

void CGShopRequestSell::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_ItemObjectID);
	oStream.write(m_OpCode);

	__END_CATCH
}

void CGShopRequestSell::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGShopRequestSellHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGShopRequestSell::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGShopRequestSell("
		<< "ObjectID : " << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
