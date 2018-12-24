////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.cpp
// Written By  : 
// Description : 
// NPC�� �÷��̾�� ����� ������ �� �� ���̴� �׼��̴�.
// ���������δ� NPC�� ������ �� �� �ִ� ����� ��Ŷ����
// ������ �� ���̰�, ������ �۾����� ��Ŷ�� �պ��ϴ� ���̿�
// ó���ȴ�.
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
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionHeightTeachSkill::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// �ϴ� Ŭ���̾�Ʈ�� ���ؼ� OK ��Ŷ�� �� ������.
	GCNPCResponse okpkt;
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&okpkt);

	Slayer*          pSlayer = dynamic_cast<Slayer*>(pCreature2);
	GCTeachSkillInfo teachinfo;

	Assert(pPlayer != NULL);

	// �ϴ� ����� ��� �� �ִ��� üũ�� �Ѵ�.
	if (pSlayer->getGoalExp(pSlayer->getHighestSkillDomain()) != 0)
	{
		// ��Ŷ�� ����� ������...
		teachinfo.setDomainType(pSlayer->getHighestSkillDomain());
		teachinfo.setTargetLevel(0);
		pPlayer->sendPacket(&teachinfo);
		return;
	}

	Level_t     DomainLevel = pSlayer->getSkillDomainLevel(pSlayer->getHighestSkillDomain());
	SkillType_t SkillType   = g_pSkillInfoManager->getSkillTypeByLevel(pSlayer->getHighestSkillDomain(), DomainLevel);

	// ��Ŷ�� ����� ������...
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
