//////////////////////////////////////////////////////////////////////////////
// Filename    : HitRoll.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __HITROLL_H__
#define __HITROLL_H__

#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;
class Slayer;
class Vampire;
class Ousters;
class Monster;
class SkillInfo;
class SkillSlot;
class VampireSkillSlot;
class OustersSkillSlot;

//////////////////////////////////////////////////////////////////////////////
// class HitRoll
// ���� ���߱��� �Լ��� �ϳ��� ���ӽ����̽��� ���� ���� ������� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

class HitRoll
{
public:
	// �Ϲ� ���� ���߱��� �Լ�
	static bool isSuccess(Creature* pAttacker, Creature* pDefender, int ToHitBonus = 0);
//	static bool isSuccess(ToHit_t ToHit, Creature* pDefender, int ToHitBonus = 0);

	// �����̾�� ���� ���߱��� �Լ�
	static bool isSuccessMagic(Slayer* pSlayer, SkillInfo* pSkillInfo, SkillSlot* pSkillSlot);

	// �����̾�� ���� ���߱��� �Լ�
	static bool isSuccessMagic(Vampire* pVampire, SkillInfo* pSkillInfo, VampireSkillSlot* pVampireSkillSlot, int BonusPoint = 0);

	// �ƿ콺�ͽ��� ���� ���߱��� �Լ�
	static bool isSuccessMagic(Ousters* pOusters, SkillInfo* pSkillInfo, OustersSkillSlot* pOustersSkillSlot, int BonusPoint = 0);

	// ���Ϳ� ���� ���߱��� �Լ�
	static bool isSuccessMagic(Monster* pMonster, SkillInfo* pSkillInfo);

	// �����̾� �� ���Ϳ� ���� ���߱��� �Լ�
	static bool isSuccessBloodDrain(Creature* pAttacker, Creature* pDefender, int multiplier=3);

	// ���� �迭 ���� ���߱��� �Լ�
	static bool isSuccessCurse(int MagicLevel, Resist_t resist);
	static bool isSuccessVampireCurse(int MagicLevel, Resist_t resist);

	// CurePoison ���߱��� �Լ�
	static bool isSuccessCurePoison(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio = 0);

	// Flare ���߱��� �Լ�
	static bool isSuccessFlare(Creature* pTargetCreature, int SkillLevel);

	// RemoveCurse ���߱��� �Լ�
	static bool isSuccessRemoveCurse(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio = 0);

	// Rebuke ���߱��� �Լ�
	static bool isSuccessRebuke(Slayer* pSlayer, SkillSlot* pSkillSlot, Creature* pDefender);
	static bool isSuccessMistOfSoul(Ousters* pOusters, OustersSkillSlot* pSkillSlot, Creature* pDefender);
	static bool isSuccessVenom(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, Creature* pDefender);
	// Magic Elusion ���߱��� �Լ�
	static bool isSuccessMagicElusion(Slayer* pSlayer);

	// Poison Mesh ���߱��� �Լ�
	static bool isSuccessPoisonMesh(Vampire* pVampire);

	// Illusion Of Avenge ���߱��� �Լ�
	static bool isSuccessIllusionOfAvenge(Slayer *pSlayer);

	// Will Of Life ���߱��� �Լ�
	static bool isSuccessWillOfLife(Vampire* pVampire);

	// ũ��Ƽ�� ��Ʈ ���� �����Ѵ�.
	static bool isCriticalHit(Creature* pCreature, int CriticalBonus=0);

	// �����̾� ���� ��ų�ΰ��� üũ�ϴ� �Լ�
	static bool isSlayerSelfSkill( SkillType_t skillType );
	static bool isOustersSelfSkill( SkillType_t skillType );

	// �ҷ� ������
	static bool isSuccessHallucination( Vampire* pAttacker, Creature* pTarget );

	// �齺�� ������
	static bool isSuccessBackStab( Ousters* pAttacker );
};

#endif
