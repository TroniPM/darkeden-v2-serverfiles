////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.cpp
// Written By  : 
// Description : 
// NPC가 플레이어에게 기술을 가르쳐 줄 때 쓰이는 액션이다.
// 실제적으로는 NPC가 가르쳐 줄 수 있는 기술을 패킷으로
// 전송해 줄 뿐이고, 나머지 작업들은 패킷이 왕복하는 사이에
// 처리된다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionHeightTeachSkill.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "SkillInfo.h"
#include "Gpackets/GCTeachSkillInfo.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionHeightTeachSkill::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionHeightTeachSkill::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// 일단 클라이언트를 위해서 OK 패킷을 함 날린다.
	GCNPCResponse okpkt;
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&okpkt);

	Slayer*          pSlayer = dynamic_cast<Slayer*>(pCreature2);
	GCTeachSkillInfo teachinfo;

	Assert(pPlayer != NULL);

	// 일단 기술을 배울 수 있는지 체크를 한다.
	if (pSlayer->getGoalExp(pSlayer->getHighestSkillDomain()) != 0)
	{
		// 패킷을 만들어 가지고...
		teachinfo.setDomainType(pSlayer->getHighestSkillDomain());
		teachinfo.setTargetLevel(0);
		pPlayer->sendPacket(&teachinfo);
		return;
	}

	Level_t     DomainLevel = pSlayer->getSkillDomainLevel(pSlayer->getHighestSkillDomain());
	SkillType_t SkillType   = g_pSkillInfoManager->getSkillTypeByLevel(pSlayer->getHighestSkillDomain(), DomainLevel);

	// 패킷을 만들어 가지고...
	teachinfo.setDomainType(pSlayer->getHighestSkillDomain());
	teachinfo.setTargetLevel(SkillType);

	pPlayer->sendPacket(&teachinfo);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionHeightTeachSkill::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionHeightTeachSkill(" << ")";
	return msg.toString();

	__END_CATCH
}
