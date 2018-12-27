////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionContractGnomesHorn.cpp
// Written By  : 
// Description : 
// NPC�� �������� �÷��̾�� �Ĵ� �׼��̴�. �����δ� �ŷ��� 
// �����ϰ� ����� �׼��̸�, �ϴ� ���� �÷��̾�� ���� NPC��
// ���� ������ ��Ŷ���� �����ִ� �� ���̴�.
////////////////////////////////////////////////////////////////////////////////

#include "ActionContractGnomesHorn.h"
#include "Creature.h"
#include "NPC.h"
#include "Script.h"
#include "Trigger.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// ActionContractGnomesHorn �׼��� �׳� Ŭ���̾�Ʈ���� ShopVersion�� �����ִ� ���̹Ƿ�,
// Ư���� �о�鿩�� �� �Ķ���Ͱ� ����.
////////////////////////////////////////////////////////////////////////////////
void ActionContractGnomesHorn::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionContractGnomesHorn::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	FlagSet* pFlagSet = pPC->getFlagSet();
	Assert(pFlagSet != NULL);

	pFlagSet->turnOn( FLAGSET_GNOMES_HORN );
	pFlagSet->save( pPC->getName() );

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_GNOME_CONTRACT_OK );

	pPC->getPlayer()->sendPacket(&gcNPCResponse);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionContractGnomesHorn::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionContractGnomesHorn(" << ")";
	return msg.toString();

	__END_CATCH
}
