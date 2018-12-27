////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastleDungeon.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionEnterCastleDungeon.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Zone.h"
#include "PaySystem.h"
#include "WarSystem.h"
#include "PacketUtil.h"
#include "GamePlayer.h"
#include "CastleInfoManager.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionEnterCastleDungeon::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	/*if (!g_pVariableManager->isActiveHolyLand())
	{
		return false;
	}*/
	// ���߿� ���������� üũ�ؾ� �ȴ�

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	//cout << "Condition: EnterCastleDungeon" << endl;

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
		bool hasGuildWar = g_pWarSystem->hasCastleActiveWar( m_CastleZoneID );

		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
		Assert(pCastleInfo!=NULL);

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
		Assert(pPC!=NULL);

		GuildID_t GuildID 		= pPC->getGuildID();
		GuildID_t OwnerGuildID 	= pCastleInfo->getGuildID();

		// ������ ���� �� --> �� ���� ��常 �� �� �ִ�.
		// ��� ���� �� --> ���� ��嵵 �� �� �ִ�.
		if ( OwnerGuildID!=SlayerCommon && OwnerGuildID!=VampireCommon && OwnerGuildID!=OustersCommon
			&& GuildID==OwnerGuildID)
		{
			return true;
		}

		if (hasGuildWar)
		{
			GuildID_t AttackGuildID;
			g_pWarSystem->getAttackGuildID( m_CastleZoneID, AttackGuildID );
			if (GuildID==AttackGuildID)
			{
				return true;
			}
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionEnterCastleDungeon::read (PropertyBuffer & propertyBuffer) 
	
{
	try
	{
		// read turn
		m_CastleZoneID = propertyBuffer.getPropertyInt("CastleZoneID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionEnterCastleDungeon::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionEnterCastleDungeon("
		<< "CastleZoneID:" << (int)m_CastleZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
