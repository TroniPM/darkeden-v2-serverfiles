////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPayPlay.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionPayPlay.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "PaySystem.h"
#include "GamePlayer.h"
#include "PacketUtil.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionPayPlay::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());

	Assert(pGamePlayer!=NULL);

	// �̹� �������� �ִ� �����... ���������.
	if (pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass())
	{
		return true;
	}

	// �ϴ� zone ��� üũ
	//return pGamePlayer->hasPayPlayFlag(PAY_PLAY_FLAG_ZONE)

	string connectIP = pGamePlayer->getSocket()->getHost();
	
	if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
	{
		sendPayInfo(pGamePlayer);
		return true;
	}
	else
	{
		return false;
	}
#else
	return true;
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionPayPlay::read (PropertyBuffer & propertyBuffer) 
	
{
	/*
	try
	{
		// read turn
		m_Index = propertyBuffer.getPropertyInt("Index");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	*/
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionPayPlay::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionPayPlay("
//		<< "Index:" << (int)m_Index
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
