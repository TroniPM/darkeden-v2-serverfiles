//--------------------------------------------------------------------------------
// SimpleQuest.h
//--------------------------------------------------------------------------------
//
// {START}
//			create() --> [WAIT]
//
// [WAIT]
//			take() --> [ACTIVE]
//
// [ACTIVE]
//			processActive()
//			{
//				checkFail() --> givePenalty() --> {END}
//				checkSuccess() --> [COMPLETE]
//			}
// 
// [COMPLETE]
//			checkComplete() --> giveReward() --> {END}
//
// {END}
//			destroy()
//
//
//--------------------------------------------------------------------------------
//
// �ϴ� Quest�� gameserver�󿡼��� �����ȴ�.
// �׷��ٰ�. ���� Quest�� ������, DB�� �����Ѵ�.
// Quest���� ������ �̹� Quest�� �ޱ� ������ üũ�Ǳ� ������
// DB�� ������ �ʿ䰡 ����.
//
// DB table: < SimpleQuest >
//
// pOwner		varchar,	// �� ����Ʈ�� ���� ���
// QuestType 	int, 
// Objective 	text,
// Bonus 		text,
// Penalty 		text,
// Deadline		datetime,
//--------------------------------------------------------------------------------


#ifndef __SIMPLE_QUEST_H__
#define __SIMPLE_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Quest.h"
#include "Timeval.h"
#include "Creature.h"
#include "QuestPrice.h"
#include <list>


class SimpleQuest : public Quest {
public :
	SimpleQuest();
	virtual ~SimpleQuest();

	void 				setDeadline (Turn_t delay);
	Duration_t		 	getRemainDuration() ;

	//virtual void		create()  = 0;
	virtual void        save()  = 0;
	virtual void		destroy();

	//virtual bool		checkSuccess(const QuestEvent* pQuestEvent)  = 0;
	virtual bool		checkFail();
	//virtual bool		checkComplete()  = 0;

	virtual void		take(Creature* pCreature, bool bNewQuest=true);
	virtual void		giveReward();
	virtual void		givePenalty();

	virtual void		heartbeat();

	void				setOwner(Creature* pOwner) 	{ m_pOwner = pOwner; }
	void				setAvailableSecond(int sec) 	{ m_AvailableSecond = sec; }
	void				addReward(QuestPrice* pQuestPrice);
	void				addPenalty(QuestPrice* pQuestPrice);

public :
	virtual void		setObjective(const string& text)  = 0;
	virtual string		getObjectiveToString()  = 0;
	virtual void		addReward(const string& text);
	virtual void		addPenalty(const string& text);
	virtual string		getRewardToString() ;
	virtual string		getPenaltyToString() ;

	virtual string		toString()  = 0;

protected :
	virtual void		processActive();
	virtual void		processFail();

protected :
	Creature*			m_pOwner;
	int					m_AvailableSecond;
	Timeval				m_Deadline;
	QuestPrice*			m_pReward;
	QuestPrice*			m_pPenalty;
};

#endif

