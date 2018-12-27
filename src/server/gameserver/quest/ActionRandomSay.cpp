////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRandomSay.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRandomSay.h"
#include "Creature.h"
#include "NPC.h"
#include "Script.h"
#include "ScriptManager.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCSay.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionRandomSay::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_StartScriptID = propertyBuffer.getPropertyInt("StartScriptID");
		m_EndScriptID = propertyBuffer.getPropertyInt("EndScriptID");
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
void ActionRandomSay::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature1 != NULL);
	Assert(pCreature2 == NULL);
	Assert(pCreature1->isNPC());

	// RandomSay�� �Ʒ����� ���ٽ���, ������ ����(Start�� End) ���� 
	// ��ũ��Ʈ �� ������ ���� �ϳ��� Ŭ���̾�Ʈ���� ������ ���̴�.
	// �׷��Ƿ� Start�� End ���̿� �������� �ʴ� ��ũ��Ʈ�� ������ ����ϴ�.
	// ��ũ��Ʈ ���̺��� ���� ��, RandomSay�� ����ϴ� ���� 
	// �����Ͱ� �ݵ�� ���������� �����ϰ� ������ �Ѵ�.
	NPC*          pNPC     = dynamic_cast<NPC*>(pCreature1);
	ScriptID_t    scriptID = m_StartScriptID + random() % (m_EndScriptID - m_StartScriptID + 1);
	const Script* pScript  = g_pPublicScriptManager->getScript(scriptID);

	GCNPCSay gcNPCSay;
	gcNPCSay.setObjectID(pNPC->getObjectID());
	gcNPCSay.setScriptID(pScript->getScriptID());
	gcNPCSay.setSubjectID(0);

	Zone * pZone = pNPC->getZone();
	Assert(pZone != NULL);
	pZone->broadcastPacket(pNPC->getX() , pNPC->getY() , &gcNPCSay);

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRandomSay::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRandomSay("
		<< ",ScriptID:"  << (int)m_StartScriptID << "-" << (int)m_EndScriptID
		<< ")";
	
	return msg.toString();
	__END_CATCH
}
