////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRestore.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRestore.h"
#include "Creature.h"
#include "NPC.h"
#include "SkillHandlerManager.h"
#include "Restore.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ActionRestore::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY 
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionRestore::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY 

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	GCNPCResponse okpkt;
	pCreature2->getPlayer()->sendPacket(&okpkt);

	// NPC�� ����...
	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);

	// ��ų �ڵ鷯�� ����...
	SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_RESTORE);
	Assert(pSkillHandler != NULL);

	// ������� �ڵ鷯�� �ٲٰ�...
	Restore* pRestore = dynamic_cast<Restore*>(pSkillHandler);
	
	// ������ �����Ѵ�.
	pRestore->execute(pNPC, pCreature2);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRestore::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRestore("
		<< ")";
	return msg.toString();

	__END_CATCH
}
