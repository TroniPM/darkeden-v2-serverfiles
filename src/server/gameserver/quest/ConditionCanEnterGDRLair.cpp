////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterGDRLair.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterGDRLair.h"
#include "GDRLairManager.h"
#include "Effect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterGDRLair::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

//	return false;

/*	if ( GDRLairManager::Instance().getTotalPCs() > 36 )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "���� �ο��� �ʰ��Ǿ� �� �� �����ϴ�." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}*/

	if ( !GDRLairManager::Instance().canEnter() )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "�ȴ����й���û����." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}

	if ( !pCreature2->isFlag( Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR ) )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "���뵽ʧ��֮��2���ƻ�����˹ä��ʯ��." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterGDRLair::read (PropertyBuffer & propertyBuffer) 
	
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterGDRLair::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterGDRLair("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
