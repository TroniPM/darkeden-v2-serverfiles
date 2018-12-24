////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestList.cpp
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSimpleQuestList.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Script.h"
#include "ScriptManager.h"
//#include "Quest.h"
#include "NPC.h"
#include "Gpackets/GCNPCAskDynamic.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestList::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionSimpleQuestList::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

/*#ifdef __ACTIVE_QUEST__
	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);

	// m_ScriptID�� ���õ� ������ PublicScriptManager�� ����
	Script* pScript = g_pPublicScriptManager->getScript(m_ScriptID);

	pNPC->setSimpleQuestListScript( pScript );

	// ��Ŷ ����
	GCNPCAskDynamic gcNPCAskDynamic;
	gcNPCAskDynamic.setObjectID(pCreature1->getObjectID());
	gcNPCAskDynamic.setScriptID(m_ScriptID);
	gcNPCAskDynamic.setSubject(pScript->getSubject(0));

	for (uint c=0; c<pScript->getContentCount(); c++)
	{
		gcNPCAskDynamic.addContent(pScript->getContent(c));
	}

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAskDynamic);

	
#endif*/

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSimpleQuestList::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSimpleQuestList("
	    << ")";

	return msg.toString();

	__END_CATCH
}

