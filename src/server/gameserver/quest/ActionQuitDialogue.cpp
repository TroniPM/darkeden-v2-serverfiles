////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionQuitDialogue.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ActionQuitDialogue.h"
#include "Creature.h"
#include "Gpackets/GCNPCResponse.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionQuitDialogue::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	// �� �׼��� NPC�� �÷��̾� ���� ��ȭ�� �����Ű�� ������ �ϹǷ�
	// Ư���� �о�鿩�� �� �Ķ���Ͱ� �������� �ʴ´�.

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionQuitDialogue::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse response;
	response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPlayer->sendPacket(&response);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionQuitDialogue::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionQuitDialogue(" << ")";
	return msg.toString();

	__END_CATCH
}
