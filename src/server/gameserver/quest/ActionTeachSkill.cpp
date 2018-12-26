////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.cpp
// Written By  : 
// Description : 
// NPC�� �÷��̾�� ����� ������ �� �� ���̴� �׼��̴�.
// ���������δ� NPC�� ������ �� �� �ִ� ����� ��Ŷ����
// ������ �� ���̰�, ������ �۾����� ��Ŷ�� �պ��ϴ� ���̿�
// ó���ȴ�.
////////////////////////////////////////////////////////////////////////////////

#include "ActionTeachSkill.h"
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
void ActionTeachSkill::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		// ������ Ÿ���� �о���δ�.
		string domainType = propertyBuffer.getProperty("DomainType");

		if (domainType == "BLADE")        m_DomainType = SKILL_DOMAIN_BLADE;
		else if (domainType == "SWORD")   m_DomainType = SKILL_DOMAIN_SWORD;
		else if (domainType == "GUN")     m_DomainType = SKILL_DOMAIN_GUN;
		//else if (domainType == "RIFLE")   m_DomainType = SKILL_DOMAIN_RIFLE;
		else if (domainType == "ENCHANT") m_DomainType = SKILL_DOMAIN_ENCHANT;
		else if (domainType == "HEAL")    m_DomainType = SKILL_DOMAIN_HEAL;
		else if (domainType == "ETC")     m_DomainType = SKILL_DOMAIN_ETC;
		else if (domainType == "VAMPIRE") m_DomainType = SKILL_DOMAIN_VAMPIRE;
		else throw Error("TeachSkill::read() : �߸��� ��� Ÿ���Դϴ�.");
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
void ActionTeachSkill::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	if (pCreature2->isSlayer())       executeSlayer(pCreature1, pCreature2);
	else if (pCreature2->isVampire()) executeVampire(pCreature1, pCreature2);
	else throw ("ActionTeachSkill::execute() : �� �� ���� �÷��̾� ũ�����Դϴ�!");

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionTeachSkill::executeSlayer (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Slayer*          pSlayer = dynamic_cast<Slayer*>(pCreature2);
	Player*          pPlayer = pCreature2->getPlayer();
	GCTeachSkillInfo teachinfo;

	Assert(pPlayer != NULL);

	// �ϴ� ����� ��� �� �ִ��� üũ�� �Ѵ�.
	if (pSlayer->getGoalExp(m_DomainType) != 0)
	{
		// ��Ŷ�� ����� ������...
		teachinfo.setDomainType(m_DomainType);
		teachinfo.setTargetLevel(0);
		pPlayer->sendPacket(&teachinfo);
		return;
	}

	Level_t     DomainLevel = pSlayer->getSkillDomainLevel(m_DomainType);
	SkillType_t SkillType   = g_pSkillInfoManager->getSkillTypeByLevel(m_DomainType, DomainLevel);

	/*

	// ũ���İ� ��� �� �ִ� ����� ������ Ȯ���Ѵ�.
	LastLearnSkillType = pSlayer->findLastSkill();

	// �÷��̾ ��� ����� �ϳ��� ���ٸ� ���� ��� ����� 1�����̴�.
	// �÷��̾ ��� ����� ����ٸ� ���س��� ����� �����ش�.
	if (LastLearnSkillType == 0)
	{
		targetLevel = 1;
	}
	else if (LastLearnSkillType == SKILL_MAX)
	{
		targetLevel = ALL_SKILL_LEARNED;
	}
	else
	{
		pSkillInfo  = g_pSkillInfoManager->getSkillInfo(LastLearnSkillType);
		targetLevel = pSkillInfo->getLevel() + 1;
	}
	*/

	// ��Ŷ�� ����� ������...
	teachinfo.setDomainType(m_DomainType);
	teachinfo.setTargetLevel(SkillType);

	pPlayer->sendPacket(&teachinfo);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionTeachSkill::executeVampire (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);

	/*
	// ũ���İ� ��� �� �ִ� ����� ������ Ȯ���Ѵ�.
	SkillType_t  LastLearnSkillType = pVampire->findLastSkill();
	SkillInfo*   pSkillInfo         = NULL;
	SkillLevel_t targetLevel        = 0;

	// �÷��̾ ��� ����� �ϳ��� ���ٸ� ���� ��� ����� 1�����̴�.
	// �÷��̾ ��� ����� ����ٸ� ���س��� ����� �����ش�.
	if (LastLearnSkillType == 0)
	{
		targetLevel = 1;
	}
	else if (LastLearnSkillType == SKILL_MAX) 
	{
		targetLevel = ALL_SKILL_LEARNED;
	}
	else
	{
		pSkillInfo  = g_pSkillInfoManager->getSkillInfo(LastLearnSkillType);
		targetLevel = pSkillInfo->getLevel() + 1;
	}
	*/

	Level_t DomainLevel = pVampire->getLevel();

	SkillType_t SkillType = g_pSkillInfoManager->getSkillTypeByLevel(m_DomainType, DomainLevel);


	// ��Ŷ�� ����� ������...
	GCTeachSkillInfo teachinfo;
	teachinfo.setDomainType(m_DomainType);
	teachinfo.setTargetLevel(SkillType);

	// �����Ѵ�.
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&teachinfo);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTeachSkill::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTeachSkill(" << ")";
	return msg.toString();

	__END_CATCH
}
