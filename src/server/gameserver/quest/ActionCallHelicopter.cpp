////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCallHelicopter.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCallHelicopter.h"
#include "NPC.h"
#include "Slayer.h"
#include "GamePlayer.h"
#include "Effect.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionCallHelicopter::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionCallHelicopter::execute (Creature * pCreature1, Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// �����̾�� �� �׼��� ����� �ȴ�.
	if (!pCreature2->isSlayer()) return;
	if (pCreature2->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) || pCreature2->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER)) return;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
	Assert(pSlayer != NULL);

	// �����̾�� ����Ʈ�� �ɾ��ش�.
	if (!pSlayer->isFlag(Effect::EFFECT_CLASS_SLAYER_PORTAL))
		pSlayer->setFlag(Effect::EFFECT_CLASS_SLAYER_PORTAL);

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode(NPC_RESPONSE_INTERFACE_HELICOPTER);
	pPlayer->sendPacket(&gcNPCResponse);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCallHelicopter::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCallHelicopter("
		<< ")";
	return msg.toString();

	__END_CATCH
}
