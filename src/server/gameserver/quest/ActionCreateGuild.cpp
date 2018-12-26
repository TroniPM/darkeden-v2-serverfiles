////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCreateGuild.cpp
// Written By  : 
// Description :
// NPC�� ���� Ŭ���̾�Ʈ�� �Ͽ��� ��� ����â�� ���� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateGuild.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Gpackets/GCNPCResponse.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGuild::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	// ��� ����â�� ���� �ͻ��̹Ƿ� Ư���� �о���� �μ��� ����.

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGuild::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT(SYSTEM_GUILD);

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_INTERFACE_CREATE_GUILD);
	pPlayer->sendPacket(&okpkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateGuild::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateGuild("
		<< ")";
	return msg.toString();

	__END_CATCH
}
