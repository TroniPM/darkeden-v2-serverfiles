//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterKillQuestInfo.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_KILL_QUEST_INFO_H__
#define __MONSTER_KILL_QUEST_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "QuestInfo.h"
#include "MonsterKillQuestStatus.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterKillQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class MonsterKillQuestInfo : public QuestInfo
{
public:
	MonsterKillQuestInfo(QuestID_t questID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, SpriteType_t monsterType, bool isChief, int killCount);
	~MonsterKillQuestInfo();

public:

	virtual string					toString() ;

	virtual MonsterKillQuestStatus*	makeQuestStatus( PlayerCreature* pPC ) ;
	bool	isMonsterKillQuest() const { return true; }

	int		getGoalNum() const { return m_GoalNum; }
	SpriteType_t	getTargetMonsterSpriteType() const { return m_TargetMonsterSpriteType; }

private:
	SpriteType_t	m_TargetMonsterSpriteType;	// ����Ʈ���� ���� ������ ��������Ʈ Ÿ��
	bool			m_IsChief;				// ����Ʈ���� ���� ���Ͱ� chief�̾�� �ϴ°�?
	int				m_GoalNum;			// ����Ʈ���� ���� ���� ��
};

#endif
