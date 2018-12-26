//////////////////////////////////////////////////////////////////////////////
// Filename    : CGThrowItemHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGThrowItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Zone.h"
	#include "ZoneUtil.h"

	#include "item/HolyWater.h"

	#include "skill/Sniping.h"

	#include "Gpackets/GCThrowItemOK1.h"
	#include "Gpackets/GCThrowItemOK2.h"
	#include "Gpackets/GCThrowItemOK3.h"
	#include "Gpackets/GCSkillFailed1.h"
	#include "Gpackets/GCSkillFailed2.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGThrowItemHandler::execute(CGThrowItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		// ���� �÷��̾��� ���°� ������ �ƴ϶�� �� �����Ѵ�.
		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature* pCreature = pGamePlayer->getCreature();
		// �÷��̾ �����̾ �ƴ϶�� �� �����Ѵ�.
		if (!pCreature->isSlayer()) return;

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert(pSlayer != NULL);

		// ���� ���������� ��� ��� �Ұ�. by sigi. 2002.11.14
		ZoneLevel_t ZoneLevel = pSlayer->getZone()->getZoneLevel(pSlayer->getX(), pSlayer->getY());
		if (ZoneLevel & COMPLETE_SAFE_ZONE)
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType(SKILL_THROW_HOLY_WATER);
			pPlayer->sendPacket(&_GCSkillFailed1);

			return;
		}

		if (pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
		{
			g_Sniping.checkRevealRatio(pCreature, 20, 10);
		}

		SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_THROW_HOLY_WATER);
		Assert(pSkillHandler != NULL);
		pSkillHandler->execute(pSlayer, pPacket->getTargetObjectID(), pPacket->getObjectID(), pPacket->getX(), pPacket->getY());
	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

