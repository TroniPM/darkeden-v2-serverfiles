//////////////////////////////////////////////////////////////////////////////
// Filename    : Condition.h
// Written By  : 
// Description :
// Ʈ������ �׼��� ����Ǳ� ���ؼ� �����ؾ� �ϴ� ������ ��Ÿ���� Ŭ����.
// �� Ŭ������ ��ӹ޾Ƽ� �ٸ� ��ü���� ���ǵ��� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "Types.h"
#include "Exception.h"
#include <bitset>
#include "PropertyBuffer.h"

//////////////////////////////////////////////////////////////////////////////
// ������� üũ�� ���� �ΰ����� �Ķ���͸� �����ϱ� ���� ����ü��.
//////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	ScriptID_t ScriptID;
	AnswerID_t AnswerID;
} COND_ANSWERED_BY;


////////////////////////////////////////////////////////////////////////////////
//
// class Condition;
//
////////////////////////////////////////////////////////////////////////////////
//
//* isActive() | isPassive() | isNeutral()
//
// ZoneGroupThread�� Ư�� ���� �ִ� ���� Ȥ�� NPC�� ó���� ��, ���� ���� �ִ�
// Ʈ���ŵ��� ��� ������� �����ϴ��� üũ�Ѵ�. �׷���, ���� Ȥ�� NPC���� 
// ��Ŷ �ڵ鷯������ �ǹ̸� ������ passive ������� ���� Ʈ���Ÿ� ������ ����
// �ϰ� �ִ�. passive ����ǵ��� isSatisfied()���� Ư���� üũ�� �Ǵ���..�� ����
// ������ �����ϸ� true �� �����ϰ� �ȴ�. 
//
// ����, ZGT�� ó���� passive ����ǵ��� üũ�� �ʿ䰡 ������ üũ�Ǿ�� �ȵȴ�.
// �̸� ���ؼ� �߰��� �޽����� isActive(), isPassive() �̴�.
//
// neutral ������� active | passive �� �ٿ� �Բ� ���� �� �ִ� ���ǵ��̴�.
//(ex: PC_HAS_SKILL, PC_HAS_ITEM ...)
//
////////////////////////////////////////////////////////////////////////////////

class Creature;

class Condition 
{
public:

	enum ConditionTypes 
	{
		// active conditions
		CONDITION_AT_FIRST,
		CONDITION_AT_TIME,
		CONDITION_FROM_TIME_TO_TIME,
		CONDITION_IDLE,
		CONDITION_EVERY_TIME,

		// passive conditions
		CONDITION_TALKED_BY,
		CONDITION_ANSWERED_BY, // 2000.10.13 �輺���� �߰�
		CONDITION_BLOOD_DRAINED,
		CONDITION_FLAG_ON,
		CONDITION_FLAG_OFF,
		CONDITION_ATTR_COMP,
		CONDITION_RACE_COMP,
		CONDITION_SAME_CLAN,

		CONDITION_ATTACKED_BY,
		CONDITION_DIED_BY,
		CONDITION_RESCUED_BY,
		CONDITION_PC_ATTRIBUTE_COMP,
		CONDITION_PC_HAS_SKILL,
		CONDITION_PC_SKILL_COMP,
		CONDITION_PC_HAS_ITEM,
		CONDITION_PC_DONE_QUEST,
		CONDITION_PC_UNDER_QUEST,
		CONDITION_QUEST_COMPLETED,
		CONDITION_QUEST_STATE,

		// 2002.6.3 by sigi
		CONDITION_PAY_PLAY,
		
		// 2002.9.2 by sigi
		CONDITION_ENTER_MASTER_LAIR,	// conditionüũ�� action��Ҹ� ���� ó���Ѵ�. ó���� ���Ǹ� ���ؼ�-_-;

		// 2003.1.20 by bezz, Sequoia
		CONDITION_ENTER_CASTLE,		// ��Ż�� ���� ���� ������ �� ��
		CONDITION_HAS_ENOUGH_CASTLE_ENTRANCE_FEE,	// ���� �� ����Ḧ ������ �� �ִ���

		// 2003.2.18 by sigi
		CONDITION_ENTER_HOLY_LAND,			// �ƴ��� ������ ������ �� ��
		CONDITION_ENTER_CASTLE_DUNGEON,		// (�ƴ��� ����) �� ���� �ʿ� �������Ҷ�

		CONDITION_HAS_QUEST,
		CONDITION_HAS_INVEN_SPACE,

		CONDITION_CAN_ENTER_PAY_ZONE,		// ���������� �� ��

		CONDITION_CAN_ENTER_BEGINNER_ZONE,	// �׸޸��� ������ �� ��
		CONDITION_CAN_WARP_GATE,			// ���� ����Ʈ ������ �� �ֳ�?
		CONDITION_CAN_ENTER_LEVEL_WAR_ZONE,			// ���� ����Ʈ ������ �� �ֳ�?

		CONDITION_CAN_PET_QUEST,
		CONDITION_CAN_ENTER_EVENT_ZONE,

		CONDITION_EFFECT_FLAG,				// Ư�� ����Ʈ �÷��װ� ���� �ִ°�
		CONDITION_CAN_ENTER_GDR_LAIR,		// ���巹 ���� �� �� �ֳ�

		CONDITION_EXIST_REINFORCE,			// ���� ���� ��û�� ���� �ֳ�

		CONDITION_SIEGE_DEFENDER_SIDE,		// �������ΰ�
		CONDITION_SIEGE_ATTACKER_SIDE,		// �������ΰ�

		CONDITION_NOT_GUILD_MEMBER,			// ��忡 ���� ���� ������?
		CONDITION_IS_GUILD_MEMBER,			// ��忡 ���� �ִ°�?

		CONDITION_CAN_ENTER_QUEST_ZONE,		// ����Ʈ���� �� �� �ִ°�
		CONDITION_PC_HAS_ITEMS, // Ư�� �������� �����ϰ� �ִ°�.
		CONDITION_PC_HAS_GOLD, // Ư�� �ݾ��� �����ϰ� ?ִ°?
		CONDITION_ZONE_HAS_MONSTER, // Ư�� ���Ͱ� �ִ°�.
		CONDITION_PC_HAS_EFFECT, // Ư�� ����Ʈ�� �����ִ°�.
		CONDITION_PC_HAS_PARTY, // ��Ƽ�� �ִ���, ������ �������.
		CONDITION_PC_HAS_ORIGINAL_ITEMS, // Ư�� �������� �����ϰ� �ִ°�.
		CONDITION_PC_HAS_ORIGINAL_GOLD, // Ư�� �ݾ��� �����ϰ� ?ִ°?
		CONDITION_MAX
	};

public :
	virtual ~Condition() throw(Error) {}
	virtual ConditionType_t getConditionType()  = 0;

	virtual bool isActive()  { return false; }
	virtual bool isPassive()  { return false; }
	virtual bool isNeutral()  { return false; }

	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL)  = 0;

	virtual void read(PropertyBuffer & propertyBuffer) throw(Error) = 0;

	virtual string toString()  = 0;

};

// Condition Set 
#define ConditionSet bitset<Condition::CONDITION_MAX>

#endif
