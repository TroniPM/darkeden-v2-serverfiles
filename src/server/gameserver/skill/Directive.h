////////////////////////////////////////////////////////////////////////
// Filename    : Directive.h
// Written By  : �輺��
// Description : 
// MonsterAI���� �ൿ�� �����ϴ� Directive�� DirectiveSet�� 
// �����س��� �����̴�.
////////////////////////////////////////////////////////////////////////

#ifndef __DIRECTIVE_H__
#define __DIRECTIVE_H__

#include "Types.h"
#include "Exception.h"
#include <algorithm>

////////////////////////////////////////////////////////////////////////
// ���� ���
////////////////////////////////////////////////////////////////////////

enum
{
	DIRECTIVE_COND_ENEMY_RANGE_MELEE = 0,         //  0
	DIRECTIVE_COND_ENEMY_RANGE_MISSILE,           //  1
	DIRECTIVE_COND_ENEMY_RANGE_CLOSE,         	  //  2
	DIRECTIVE_COND_ENEMY_RANGE_OUT_OF_SIGHT,      //  3
	DIRECTIVE_COND_ENEMY_DYING,                   //  4
	DIRECTIVE_COND_ENEMY_NOT_BLOOD_DRAINED,       //  5
	DIRECTIVE_COND_ENEMY_NOT_GREEN_POISONED,      //  6
	DIRECTIVE_COND_ENEMY_NOT_YELLOW_POISONED,     //  7
	DIRECTIVE_COND_ENEMY_NOT_DARKBLUE_POISONED,   //  8
	DIRECTIVE_COND_ENEMY_NOT_GREEN_STALKERED,     //  9
	DIRECTIVE_COND_ENEMY_NOT_PARALYZED,           //  10
	DIRECTIVE_COND_ENEMY_NOT_DOOMED,              // 11
	DIRECTIVE_COND_ENEMY_NOT_BLINDED,             // 12
	DIRECTIVE_COND_ENEMY_NOT_IN_DARKNESS,         // 13
	DIRECTIVE_COND_ENEMY_NOT_SEDUCTION,        	// 14
	DIRECTIVE_COND_IM_OK,                         // 15
	DIRECTIVE_COND_IM_DYING,                      // 16
	DIRECTIVE_COND_IM_DAMAGED,                    // 17
	DIRECTIVE_COND_IM_HIDING,                     // 18
	DIRECTIVE_COND_IM_WOLF,                       // 19
	DIRECTIVE_COND_IM_BAT,                        // 20
	DIRECTIVE_COND_IM_INVISIBLE,                  // 21
	DIRECTIVE_COND_IM_WALKING_WALL,        		  // 22
	DIRECTIVE_COND_TIMING_BLOOD_DRAIN,     		  // 23

	// 2002.9.4
	DIRECTIVE_COND_MASTER_SUMMON_TIMING,   		  // 24
	DIRECTIVE_COND_MASTER_NOT_READY,   		  	  // 25
	DIRECTIVE_COND_IM_IN_BAD_POSITION,     		  // 26
	DIRECTIVE_COND_FIND_WEAK_ENEMY,               // 27
	DIRECTIVE_COND_ENEMY_NOT_DEATH,        		// 28
	DIRECTIVE_COND_ENEMY_NOT_HALLUCINATION,              // 29

	// 2002.9.16
	DIRECTIVE_COND_TIMING_MASTER_BLOOD_DRAIN,	  // 30

	// 2002.9.23
	DIRECTIVE_COND_TIMING_DUPLICATE_SELF,	  // 31

	// 2002.9.24
	DIRECTIVE_COND_ENEMY_RANGE_IN_MISSILE,		// 32

	// 2002.10.1
	DIRECTIVE_COND_POSSIBLE_SUMMON_MONSTERS,	// 33

	// 2003.4.14
	DIRECTIVE_COND_ENEMY_TILE_NOT_ACID_SWAMP,	// 34

	DIRECTIVE_COND_ENEMY_ON_AIR,				// 35
	DIRECTIVE_COND_ENEMY_ON_SAFE_ZONE,			// 36

	DIRECTIVE_COND_CAN_ATTACK_THROWING_AXE,		// 37

	DIRECTIVE_COND_MAX
};

const string DirectiveCondition2String[] = 
{
	"EnemyRangeMelee",					// 0
	"EnemyRangeMissile",				// 1
	"EnemyRangeClose",					// 2
	"EnemyRangeOutOfSight",				// 3
	"EnemyDying",						// 4
	"EnemyNotBloodDrained",				// 5
	"EnemyNotGreenPoisoned",			// 6
	"EnemyNotYellowPoisoned",			// 7
	"EnemyNotDarkbluePoisoned",			// 8
	"EnemyNotGreenStalkered",			// 9
	"EnemyNotParalyzed",				// 10
	"EnemyNotDoomed",					// 11
	"EnemyNotBlinded",					// 12
	"EnemyNotInDarkness",				// 13
	"EnemyNotSeduction",				// 14

	"ImOK",								// 15
	"ImDying",							// 16
	"ImDamaged",						// 17
	"ImHiding",							// 18
	"ImWolf",							// 19
	"ImBat",							// 20
	"ImInvisible",						// 21

	"ImWalkingWall",					// 22
	"TimingBloodDrain",					// 23

	// 2002.9.4
	"MasterSummonTiming",				// 24
	"MasterNotReady",					// 25
	"ImInBadPosition",					// 26
	"FindWeakEnemy",					// 27
	"EnemyNotDeath",					// 28
	"EnemyNotHallucination",			// 29

	// 2002.9.16
	"TimingMasterBloodDrain",			// 30

	// 2002.9.23
	"TimingDuplicateSelf",				// 31

	// 2002.9.24
	"EnemyRangeInMissile",				// 32
	
	// 2002.10.1
	"PossibleSummonMonsters",			// 33

	// 2003.4.14
	"EnemyTileNotAcidSwamp",			// 34

	"EnemyOnAir",						// 35
	"EnemyOnSafeZone",					// 36
	"CanAttackThrowingAxe",				// 37

	"ConditionMAX"
};

////////////////////////////////////////////////////////////////////////
// �ൿ ���
////////////////////////////////////////////////////////////////////////

enum
{
	DIRECTIVE_ACTION_APPROACH = 0,			// 35   // 0
	DIRECTIVE_ACTION_FLEE,           // 1
	DIRECTIVE_ACTION_USE_SKILL,      // 2 
	DIRECTIVE_ACTION_FORGET,         // 3
	DIRECTIVE_ACTION_CHANGE_ENEMY,   // 4 
	DIRECTIVE_ACTION_MOVE_RANDOM,    // 5
	DIRECTIVE_ACTION_WAIT,    		 // 6
	DIRECTIVE_ACTION_FAST_FLEE,		 // 7
	DIRECTIVE_ACTION_SAY,			// 8

	DIRECTIVE_ACTION_MAX
};

const string DirectiveAction2String[] = 
{
	"Approach",      // 0
	"Flee",          // 1
	"UseSkill",      // 2
	"Forget",        // 3
	"ChangeEnemy",	 // 4
	"MoveRandom",	 // 5
	"Wait",	 		 // 6
	"FastFlee",		 // 7
	"Say",			// 8

	"ActionMAX"
};


////////////////////////////////////////////////////////////////////////
// class Directive
//
// �ϳ��� �׼ǿ� ���� ������ ���ǵ��� ������� Ŭ�����̴�.
// �� ���ǰ�, �� �׼ǿ� �ʿ��� �Ķ����, �׸��� Ȯ��, �߿伺 ����
// ���ĳ��� Ŭ����...
////////////////////////////////////////////////////////////////////////

class Directive
{

///// Member methods /////
	
public:
	Directive() throw();
	~Directive() throw();

public:
	list<int>& getConditions(void) throw() { return m_Conditions; }
	void addCondition(int condition) throw();

	int getAction(void) const throw() { return m_Action; }
	void setAction(int action) throw() { m_Action = action; }

	int getParameter(void) const throw() { return m_Parameter; }
	void setParameter(int parameter) throw() { m_Parameter = parameter; }

	int getRatio(void) const throw() { return m_Ratio; }
	void setRatio(int ratio) throw() { m_Ratio = ratio; }

	int getWeight(void) const throw() { return m_Weight; }
	void setWeight(int weight) throw() { m_Weight = weight; }

	string toString(void) throw();

	bool hasCondition( int condition ) const { return find(m_Conditions.begin(), m_Conditions.end(), condition)!=m_Conditions.end(); }

///// Member data /////
	
protected:
	list<int> m_Conditions;
	int       m_Action;
	int       m_Parameter;
	int       m_Ratio;
	int       m_Weight;

};


////////////////////////////////////////////////////////////////////////
// class DirectiveSet
//
// Directive Ŭ������ �����̴�. ���� Directive�� Weight ������ 
// �̿��Ͽ� ������ �����ϰ� ������� �ߴµ�, �������� ����Ʈ��
// �����ϴ� �� �����Ƽ� �׳� ����ִ� ������� �켱������ ���� ������
// �ν��ϵ��� �ߴ�.(MonsterAI ����)
////////////////////////////////////////////////////////////////////////

class DirectiveSet
{

///// Member methods /////
	
public:
	DirectiveSet() throw();
	~DirectiveSet() throw();

public:
	const list<Directive*>& getDirectives(void) const throw() { return m_Directives; }
	const list<Directive*>& getDeadDirectives(void) const throw() { return m_DeadDirectives; }

	void addDirective(Directive* pDirective) throw();
	void addDeadDirective(Directive* pDirective) throw();

	void clear() throw();

	string getName(void) const throw() { return m_Name; }
	void setName(const string& name) throw() { m_Name = name; }

	bool hasCondition( int condition ) const;

	bool canAttackAir() const { return m_bAttackAir; }
	void setAttackAir(bool bAA) { m_bAttackAir = bAA; }

	bool canSeeSafeZone() const { return m_bSeeSafeZone; }
	void setSeeSafeZone( bool bSS ) { m_bSeeSafeZone = bSS; }

///// Member data /////
protected:
	list<Directive*> m_Directives;
	list<Directive*> m_DeadDirectives;
	string           m_Name;

	bool			 m_bAttackAir;
	bool			 m_bSeeSafeZone;
};

////////////////////////////////////////////////////////////////////////
// class DirectiveSetManager
////////////////////////////////////////////////////////////////////////

class DirectiveSetManager
{
///// Member methods /////
public:
	DirectiveSetManager() throw();
	~DirectiveSetManager() throw();

public:
	// ��ü�� �ʱ�ȭ�Ѵ�.
	void init() throw();

	// DB�κ��� directive set�� �ε��Ѵ�.
	void load() throw();

	// ������ Ÿ���� directive set �����͸� ��ȯ�Ѵ�.
	DirectiveSet* getDirectiveSet(uint index) throw();

protected:
	// ���ڿ��� �Ľ��ؼ� ������ �ε����� directive set�� �����Ѵ�.
	void createDirectiveSet(uint index, const string& name, const string& text, const string& deadtext) throw();

	// directive�� �������� �Ķ���͵��� �Ľ��Ѵ�.
	void parseDirectiveParameter(Directive* pDirective, const string& text, int mode) throw();

	// ���ڿ��κ��� condition ���� �����Ѵ�.
	int  getCondition(const string& token) throw();

	// ���ڿ��κ��� action ���� �����Ѵ�.
	int  getAction(const string& token) throw();

	// ���ڿ��κ��� �Ķ���� ���� �����Ѵ�.
	int  getParameter(const string& token) throw();

	// ���ڿ��κ��� Ȯ���� �����Ѵ�.
	int  getRatio(const string& token) throw();


///// Member data /////
protected:
	uint           m_nSetCount;
	DirectiveSet** m_ppSet;

};

extern DirectiveSetManager* g_pDirectiveSetManager;

#endif // __DIRECTIVESETMANAGER_H__
