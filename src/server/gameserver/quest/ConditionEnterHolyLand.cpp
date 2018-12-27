////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterHolyLand.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionEnterHolyLand.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Zone.h"
#include "PaySystem.h"
#include "WarSystem.h"
#include "GamePlayer.h"
#include "PacketUtil.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "ZoneUtil.h"
#include "VariableManager.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionEnterHolyLand::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	/*if (!g_pVariableManager->isActiveHolyLand())
	{
		return false;
	}*/
	// ���߿� ���������� üũ�ؾ� �ȴ�

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	//cout << "Condition: EnterHolyLand" << endl;

	bool bPayPlay = false;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Assert(pGamePlayer!=NULL);

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	// �̹� �������� �ִ� �����... ���������.
	// �йи� ����� �������� ���
	if (pGamePlayer->isPayPlaying() || pGamePlayer->isFamilyFreePass())
	{
		bPayPlay = true;
	}
	else
	{
		// �ϴ� zone ��� üũ
		string connectIP = pGamePlayer->getSocket()->getHost();
		
		if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
		{
			sendPayInfo(pGamePlayer);
			bPayPlay = true;
		}
	}
#else
	bPayPlay = true;
#endif

	// �� �� ����� castle �� �� �� �ִ�.
	if (bPayPlay)
	{
		// ���� ���� �߿�.. ���� ���� �ο� ������ �Ѵٸ�..
		if (g_pWarSystem->hasActiveRaceWar()
			&& g_pVariableManager->isActiveRaceWarLimiter())
		{
			Zone* pZone = getZoneByZoneID(m_TargetZoneID);
			Assert(pZone!=NULL);

			// �ƴ��� ������ ����
			if (!pZone->isHolyLand())
			{
				return true;
			}

			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );

			// ���� ������ �߾���� �Ѵ�.
			return pPC->isFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET );
		}

		// ���� �� �ƴϸ� �׳� ����.
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionEnterHolyLand::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_TargetZoneID = propertyBuffer.getPropertyInt("TargetZoneID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionEnterHolyLand::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionEnterHolyLand("
		<< "TargetZoneID:" << (int)m_TargetZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
