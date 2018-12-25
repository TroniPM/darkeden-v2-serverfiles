//--------------------------------------------------------------------------------
// Quest.h
//--------------------------------------------------------------------------------
//
// {START}
//			[WAIT]
//
// [WAIT]
//			take() --> create() --> [ACTIVE]
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
// QuestID�� �ܼ��� �� Quest���п��̴�.
// Thread Safe���� �ʰ�, ���������� ����ȭ���� �ʴ´�.
//--------------------------------------------------------------------------------

#ifndef __QUEST_H__
#define __QUEST_H__

#include "Types.h"
#include "Exception.h"
class Creature;
class QuestEvent;

//#define __ACTIVE_QUEST__


class Quest {
public :
	enum QuestType
	{		
		QUEST_MONSTER_KILL,

		QUEST_MAX
	};

	enum QuestState
	{
		STATE_NULL,
		
		STATE_WAIT,			// QuestBoard���� �������� �޾ư��⸦ ��ٸ��� ����
		STATE_ACTIVE,		// ���� Quest�� �޾Ƽ� �������� ����
		STATE_COMPLETE,		// Quest�� �Ϸ�� ����(Reward �ޱ� ��)
		STATE_END			// Quest�� ���� ����
	};

public :
	Quest() throw (Error) : m_QuestID(m_QuestIDRegistry++), m_State(STATE_NULL)  {}
	virtual ~Quest() throw (Error) { if (m_State!=STATE_NULL) destroy(); }
	
	static void			initQuestIDRegistry();
	QuestID_t			getQuestID()					{ return m_QuestID; }
    void				setQuestID(QuestID_t QuestID)	{ m_QuestID = QuestID; }

	virtual QuestType	getQuestType() const = 0;
	QuestState			getState() const	{ return m_State; }	

	virtual void		create() throw (Error) = 0;
	virtual void		save() throw (Error) = 0;
	virtual void		destroy() throw (Error) {}
	
	virtual bool		checkSuccess(const QuestEvent* pQuestEvent) throw (Error) = 0;
	virtual bool		checkFail() throw (Error) = 0;
	virtual bool		checkComplete() throw (Error) = 0;

	virtual void		take(Creature* pCreature, bool bNewQuest=true) throw (Error) = 0;
	virtual void		giveReward() throw (Error) = 0;
	virtual void		givePenalty() throw (Error) = 0;

	virtual void		heartbeat() throw (Error) = 0;

	virtual string		toString()  = 0;

protected :
	void setState(QuestState qs)	{ m_State = qs; }

protected :
	QuestID_t			m_QuestID;
	QuestState			m_State;

	static QuestID_t	m_QuestIDRegistry;
};

#endif

