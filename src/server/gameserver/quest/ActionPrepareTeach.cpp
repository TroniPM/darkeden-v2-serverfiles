////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareTeach.cpp
// Written By  : 
// Description : 
// ���� NPC�� ������ �� �� �ִ� ����� ������ ���ϴ� �׼��̴�.
// PrepareShop�� ����ϰ� AtFirst ������� �̿��Ͽ� ó��
// �ѹ��� �����ϰ� �ٽô� �������� �ʴ´�.
////////////////////////////////////////////////////////////////////////////////

#include "ActionPrepareTeach.h"
#include "Creature.h"
#include "NPC.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionPrepareTeach::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		// �� NPC�� ������ �� �� �ִ� �ƽ� ������ �о���δ�.
		m_MaxLevel = (SkillLevel_t)propertyBuffer.getPropertyInt("MaxLevel");
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
void ActionPrepareTeach::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	pNPC->setMaxSkillLevel(m_MaxLevel);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPrepareTeach::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionPrepareTeach("
	    << "MaxLevel:" << (int)m_MaxLevel 
		<< ")";

	return msg.toString();

	__END_CATCH
}
