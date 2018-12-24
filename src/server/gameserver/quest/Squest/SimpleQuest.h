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
	SimpleQuest() throw (Error);
	virtual ~SimpleQuest() throw (Error);

	void 				setDeadline (Turn_t delay) throw ();
	Duration_t		 	getRemainDuration() const throw();

	//virtual void		create() throw (Error) = 0;
	virtual void        save() throw (Error) = 0;
	virtual void		destroy() throw (Error);

	//virtual bool		checkSuccess(const QuestEvent* pQuestEvent) const throw (Error) = 0;
	virtual bool		checkFail() throw (Error);
	//virtual bool		checkComplete() const throw (Error) = 0;

	virtual void		take(Creature* pCreature, bool bNewQuest=true) throw (Error);
	virtual void		giveReward() throw (Error);
	virtual void		givePenalty() throw (Error);

	virtual void		heartbeat() throw (Error);

	void				setOwner(Creature* pOwner) throw (Error)	{ m_pOwner = pOwner; }
	void				setAvailableSecond(int sec) throw (Error)	{ m_AvailableSecond = sec; }
	void				addReward(QuestPrice* pQuestPrice) throw (Error);
	void				addPenalty(QuestPrice* pQuestPrice) throw (Error);

public :
	virtual void		setObjective(const string& text) throw (Error) = 0;
	virtual string		getObjectiveToString() const throw (Error) = 0;
	virtual void		addReward(const string& text) throw (Error);
	virtual void		addPenalty(const string& text) throw (Error);
	virtual string		getRewardToString() const throw (Error);
	virtual string		getPenaltyToString() const throw (Error);

	virtual string		toString() const throw (Error) = 0;

protected :
	virtual void		processActive() throw (Error);
	virtual void		processFail() throw (Error);

protected :
	Creature*			m_pOwner;
	int					m_AvailableSecond;
	Timeval				m_Deadline;
	QuestPrice*			m_pReward;
	QuestPrice*			m_pPenalty;
};

#endif

