////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashOpen.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ActionStashOpen.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Gpackets/GCNPCResponse.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionStashOpen::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY 
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionStashOpen::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY 

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// ���� �÷��̾ ���� �� ������ �����Կ� ���õ� OID��
	// �Ҵ���� �ʾҴٸ� ���⼭ �Ҵ��� �ش�.
	if (pCreature2->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
		if (!pSlayer->getStashStatus()) pSlayer->registerStash();
	}
	else if (pCreature2->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
		if (!pVampire->getStashStatus()) pVampire->registerStash();
	}
	else if (pCreature2->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
		if (!pOusters->getStashStatus()) pOusters->registerStash();
	}

	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_INTERFACE_STASHOPEN);
	pCreature2->getPlayer()->sendPacket(&okpkt);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
string ActionStashOpen::toString () const 
	
{
	__BEGIN_TRY 

	StringStream msg;
	msg << "ActionStashOpen(" << ")";
	return msg.toString();

	__END_CATCH
}
