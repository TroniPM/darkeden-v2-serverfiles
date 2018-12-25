//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterAI.h
// Written By  : �輺��
// Description : 
// ������ �ൿ�� �����ϴ� ���� ������ ���ִ� AI Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERAI_H__
#define __MONSTERAI_H__

#include "Creature.h"
#include "Zone.h"
#include "Assert.h"
#include "Timeval.h"
#include "Directive.h"

//////////////////////////////////////////////////////////////////////////////
// ��� ���� ���� ���
//////////////////////////////////////////////////////////////////////////////
enum
{
	SKILL_FAILED_RANGE  = 1,
	SKILL_FAILED_RATIO  = 2,
	SKILL_FAILED_STATUS = 3,

	SKILL_FAILED_MAX
};

//////////////////////////////////////////////////////////////////////////////
// ������ ���� ���
//////////////////////////////////////////////////////////////////////////////
enum
{
	LAST_ACTION_NONE,
	LAST_ACTION_MOVE,
	LAST_ACTION_SKILL,

	LAST_ACTION_SKILL_MAX
};

//////////////////////////////////////////////////////////////////////////////
// ������ ���� ���
//////////////////////////////////////////////////////////////////////////////
enum MoveRule
{
	MOVE_RULE_NORMAL,
	MOVE_RULE_LEFTWALL,
	MOVE_RULE_RIGHTWALL,

	MOVE_RULE_MAX,
};

//////////////////////////////////////////////////////////////////////////////
// class MonsterAI
//////////////////////////////////////////////////////////////////////////////

class Monster;

typedef bool (*ConditionCheckFunction)(Monster* pMonster, Creature* pEnemy);

class MonsterAI
{
public:

public:
	MonsterAI(Monster* pMonster, uint type) throw();
	virtual ~MonsterAI() throw();

public:
	// ������ �Լ�
	bool getDamaged(void)  { return m_bDamaged; }
	void setDamaged(bool value) throw() { m_bDamaged = value; }

	// ���̷�Ƽ�� ���� �Լ�
	void addDirective(Directive* pDirective) throw();

	// ���� �Լ�
	bool checkCondition(int condition, Creature* pEnemy) throw();
	bool checkDirective(Directive* pDirective, Creature* pEnemy) throw();

	// �ൿ �Լ� 
	bool move(ZoneCoord_t ex, ZoneCoord_t ey) throw();
	bool move(Creature* pEnemy, bool bRetreat=false) throw();
	bool approach(Creature* pEnemy) throw() { return move(pEnemy, false); }
	bool flee(Creature* pEnemy) throw();
	int  useSkill(Creature* pEnemy, SkillType_t SkillType, int ratio) throw();

	// �̵� �Լ�
	bool moveNormal(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir) throw();
	bool moveWall(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir, bool bLeft) throw();
	void setMoveRule(MoveRule mr) { m_MoveRule = mr; m_WallCount = 0; }

	// ��Ÿ�� --
	MoveRule	getMoveRule() const			{ return m_MoveRule; }
	int			getWallCount() const		{ return m_WallCount; }

	// �ൿ ���� ���� �Լ� 
	void deal(Creature* pEnemy, const Timeval& currentTime) throw();
	void actDeadAction(Creature* pEnemy) throw();

	// ������ ���� �Լ�
	void setDelay(const Timeval& currentTime) throw();
	void setAttackDelay(const Timeval& currentTime) throw();

	bool canAttackAir() const { return m_pDirectiveSet->canAttackAir(); }
	bool canSeeSafeZone() const { return m_pDirectiveSet->canSeeSafeZone(); }

private:
	// �� AI�� �����ϴ� ��ü
	Monster* m_pBody;

	// AI�� ���� Ÿ��
	uint m_AIType;

	// ���ǰ� ��� ����
	DirectiveSet* m_pDirectiveSet;

	// ����ġ�� �� Ƚ�� ī����
	int m_Panic;     

	// ����ġ�� �ִ� �� Ƚ��
	int m_PanicMax;

	// ����ġ�ٰ� ���缹�� ���,
	// �� ����ġ�� �����ϴ� Ƚ�� ī����
	int m_Courage; 

	// �� ����ġ�� �����ϴ� �ִ� �� Ƚ��
	int m_CourageMax;

	// ���� �Ͽ� �¾Ҵ�, �� �¾Ҵ� �÷���...
	bool m_bDamaged;

	// �̹� �Ͽ� ������ �ߴٴ� �÷���
	int m_LastAction;

	// �̵��ϴ� ���
	MoveRule m_MoveRule;

	// ���� ���� block�� ����==������ �� �� �� �־���ϴ� ����
	Dir_t m_BlockedDir;

	// ��Ÿ�� �� ȸ��
	int m_WallCount;

	// �Լ� �����͵�...
	ConditionCheckFunction m_pCondChecker[DIRECTIVE_COND_MAX];
};

bool checkEnemyRangeMelee(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeMissile(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeClose(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeOutOfSight(Monster* pMonster, Creature* pEnemy);
bool checkEnemyDying(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotBloodDrained(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotGreenPoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotYellowPoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDarkbluePoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotGreenStalkered(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotParalyzed(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDoomed(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotBlinded(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotInDarkness(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotSeduction(Monster* pMonster, Creature* pEnemy);
bool checkImOK(Monster* pMonster, Creature* pEnemy);
bool checkImDying(Monster* pMonster, Creature* pEnemy);
bool checkImDamaged(Monster* pMonster, Creature* pEnemy);
bool checkImHiding(Monster* pMonster, Creature* pEnemy);
bool checkImWolf(Monster* pMonster, Creature* pEnemy);
bool checkImBat(Monster* pMonster, Creature* pEnemy);
bool checkImInvisible(Monster* pMonster, Creature* pEnemy);
bool checkImWalkingWall(Monster* pMonster, Creature* pEnemy);
bool checkTimingBloodDrain(Monster* pMonster, Creature* pEnemy);
// by sigi. 2002.9.4
bool checkMasterSummonTiming(Monster* pMonster, Creature* pEnemy);
bool checkMasterNotReady(Monster* pMonster, Creature* pEnemy);
bool checkImInBadPosition(Monster* pMonster, Creature* pEnemy);
bool checkFindWeakEnemy(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDeath(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotHallucination(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.16
bool checkTimingMasterBloodDrain(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.23
bool checkTimingDuplicateSelf(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.24
bool checkEnemyRangeInMissile(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.10.1
bool checkPossibleSummonMonsters(Monster* pMonster, Creature* pEnemy);

// by Sequoia. 2003.4.14
bool checkEnemyTileNotAcidSwamp(Monster* pMonster, Creature* pEnemy);

bool checkEnemyOnAir(Monster* pMonster, Creature* pEnemy);
bool checkEnemyOnSafeZone(Monster* pMonster, Creature* pEnemy);
bool checkCanAttackThrowingAxe(Monster* pMonster, Creature* pEnemy);

#endif // __MONSTER_H__
