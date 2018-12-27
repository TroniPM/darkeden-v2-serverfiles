//--------------------------------------------------------------------------------
// SimpleQuest.cpp
//--------------------------------------------------------------------------------

#include "SimpleQuest.h"
#include "Creature.h"
#include "QuestPriceReward.h"
#include "QuestPricePenalty.h"
#include "Assert.h"
#include "DB.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
SimpleQuest::SimpleQuest()
	
: m_pOwner(NULL), m_AvailableSecond(0), m_pReward(NULL), m_pPenalty(NULL)
{
	//m_Deadline.tv_sec = m_Deadline.tv_usec = 0;
	setDeadline(99999999);
}

SimpleQuest::~SimpleQuest()
	
{
	__BEGIN_TRY

	if (m_pReward!=NULL)	SAFE_DELETE(m_pReward);
	if (m_pPenalty!=NULL)	SAFE_DELETE(m_pPenalty);

	__END_CATCH
}


//--------------------------------------------------------------------------------
// setDeadline
//--------------------------------------------------------------------------------
void SimpleQuest::setDeadline (Turn_t delay) 
	
{
    __BEGIN_TRY

	// ���� �ð��� �����Ѵ�.
	getCurrentTime(m_Deadline);

	// ��������� �����Ѵ�.
	// �̶�, delay �� 0.1 �ʰ� 1 �̴�.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

// ���� duration(1/10�� ����)
Duration_t 
SimpleQuest::getRemainDuration() const
	
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);
	return (m_Deadline.tv_sec  - currentTime.tv_sec)* 10 +
			(m_Deadline.tv_usec - currentTime.tv_usec) / 100000;

	__END_CATCH
}



//--------------------------------------------------------------------------------
// destroy
//--------------------------------------------------------------------------------
void
SimpleQuest::destroy() 
	
{
	__BEGIN_TRY

	Assert(m_pOwner!=NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		cout << "DELETE FROM SimpleQuest WHERE OwnerID = '" << m_pOwner->getName().c_str() << "'" << endl;

		pStmt->executeQuery(
			"DELETE FROM SimpleQuest WHERE OwnerID = '%s'", 
				m_pOwner->getName().c_str()); 

		/*
		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		*/
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// checkFail
//--------------------------------------------------------------------------------
bool		
SimpleQuest::checkFail() 
	
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	return currentTime >= m_Deadline;	

	__END_CATCH
}

//--------------------------------------------------------------------------------
// heartbeat
//--------------------------------------------------------------------------------
void		
SimpleQuest::heartbeat()
	
{
	__BEGIN_TRY

	if (m_State==STATE_ACTIVE)
	{
		processActive();
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// process Active
//--------------------------------------------------------------------------------
void		
SimpleQuest::processActive() 
	
{
	__BEGIN_TRY

	if (checkFail())
	{
		processFail();
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// process Fail
//--------------------------------------------------------------------------------
void
SimpleQuest::processFail()
	
{
	__BEGIN_TRY

	givePenalty();
	destroy();

	setState( STATE_END );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// take
//--------------------------------------------------------------------------------
void		
SimpleQuest::take(Creature* pCreature, bool bNewQuest) 
	
{
	__BEGIN_TRY

	setOwner( pCreature );
	
	// ó�� ���� ����Ʈ�� ��츸.. �ð� ������ DB������ �Ѵ�	
	if (bNewQuest)
	{
		getCurrentTime(m_Deadline);
		m_Deadline.tv_sec += m_AvailableSecond;	

		create();
	}

	setState( STATE_ACTIVE );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// give Reward
//--------------------------------------------------------------------------------
void		
SimpleQuest::giveReward() 
	
{
	__BEGIN_TRY

	if (m_pReward!=NULL && m_pOwner!=NULL)
	{
		m_pReward->affect( m_pOwner );
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// give Penalty
//--------------------------------------------------------------------------------
void		
SimpleQuest::givePenalty() 
	
{
	__BEGIN_TRY

	if (m_pPenalty!=NULL && m_pOwner!=NULL)
	{
		m_pPenalty->affect( m_pOwner );
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add Reward
//--------------------------------------------------------------------------------
void				
SimpleQuest::addReward(QuestPrice* pQuestPrice) 
	
{
	__BEGIN_TRY

	Assert(pQuestPrice!=NULL);
	m_pReward = pQuestPrice;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add Penalty
//--------------------------------------------------------------------------------
void				
SimpleQuest::addPenalty(QuestPrice* pQuestPrice) 
	
{
	__BEGIN_TRY

	Assert(pQuestPrice!=NULL);	
	m_pPenalty = pQuestPrice;

	__END_CATCH
}

//
void        
SimpleQuest::addReward(const string& text) 
	
{
	__BEGIN_TRY

	QuestPrice* pQuestPrice = new QuestPriceReward;

	pQuestPrice->setPrice( text );

	addReward( pQuestPrice );

	__END_CATCH
}

void        
SimpleQuest::addPenalty(const string& text) 
	
{
	__BEGIN_TRY

	QuestPrice* pQuestPrice = new QuestPricePenalty;

	pQuestPrice->setPrice( text );

	addPenalty( pQuestPrice );

	__END_CATCH
}

string
SimpleQuest::getRewardToString() const 
	
{
	__BEGIN_TRY

	if (m_pReward==NULL)
		return "";

	return m_pReward->toString();

	__END_CATCH
}

string      
SimpleQuest::getPenaltyToString() const 
	
{
	__BEGIN_TRY

	if (m_pReward==NULL)
		return "";

	return m_pPenalty->toString();

	__END_CATCH
}


