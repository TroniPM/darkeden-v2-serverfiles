//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGQuestInventory.cpp 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromGQuestInventory.h"

void CGUseItemFromGQuestInventory::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read(m_Index);

	__END_CATCH
}
		    
void CGUseItemFromGQuestInventory::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Index);

	__END_CATCH
}

void CGUseItemFromGQuestInventory::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGUseItemFromGQuestInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUseItemFromGQuestInventory::toString () 
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseItemFromGQuestInventory("
		<< ")";
	return msg.toString();

	__END_CATCH
}
