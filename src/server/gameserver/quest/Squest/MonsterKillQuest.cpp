//--------------------------------------------------------------------------------
// MonsterKillQuest.cpp
//--------------------------------------------------------------------------------

#ifdef __QUEST_TEST__
	#include "FakeMonsterInfo.h"
#else
	#include "MonsterInfo.h"
#endif
#include "MonsterKillQuest.h"
#include "QuestPriceReward.h"
#include "QuestPricePenalty.h"
#include "QuestEventMonsterKill.h"
#include "Assert.h"
#include "DB.h"

const int maxMonsterTypeInfo = 10;
const int levelToMonsterTypeDivider = 10;

//--------------------------------------------------------------------------------
// static
//--------------------------------------------------------------------------------
MonsterKillQuestFactory::MonsterTypeInfos	MonsterKillQuestFactory::m_MonsterTypeInfos;


//--------------------------------------------------------------------------------
// create
//--------------------------------------------------------------------------------
void		
MonsterKillQuest::create() 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	Turn_t currentYearTime;
    getCurrentYearTime(currentYearTime);

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
			"INSERT INTO SimpleQuest (OwnerID, QuestType, Objective, Reward, Penalty, YearTime, DayTime) Values ('%s', %d, '%s', '%s', '%s', %d, %d)",
			m_pOwner->getName().c_str(),
			(int)getQuestType(), 
			getObjectiveToString().c_str(), 
			getRewardToString().c_str(), 
			getPenaltyToString().c_str(), 
			currentYearTime, 
			m_Deadline.tv_sec);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save
//--------------------------------------------------------------------------------
void		
MonsterKillQuest::save() 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("-_-");

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// check Success
//--------------------------------------------------------------------------------
bool		
MonsterKillQuest::checkSuccess(const QuestEvent* pQuestEvent)
	throw (Error)
{
	__BEGIN_TRY

	if (getState()==STATE_ACTIVE)
	{
		if (pQuestEvent->getQuestEventType()==QuestEvent::QUEST_EVENT_MONSTER_KILL)
		{
			const QuestEventMonsterKill* pQuestEventMonsterKill = dynamic_cast<const QuestEventMonsterKill*>(pQuestEvent);

			if (*this==*pQuestEventMonsterKill)
			{
				// �� ���� ���δ�.
				decreaseNumber();

				// �� �׿�����.. �Ϸ�
				if (getNumber()==0)
				{
					setState( STATE_COMPLETE );
					return true;
				}

				return false;
			}
		}
	}

	__END_CATCH

	return false;
}

//--------------------------------------------------------------------------------
// check Complete
//--------------------------------------------------------------------------------
bool		
MonsterKillQuest::checkComplete() 
	throw (Error)
{
	__BEGIN_TRY

	__END_CATCH

	return true;
}

//--------------------------------------------------------------------------------
// create
//--------------------------------------------------------------------------------
Quest*				
MonsterKillQuestFactory::create(const QuestCreateInfo* qcInfo) const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(!m_MonsterTypeInfos.empty());

	if (qcInfo==NULL)
	{
		return new MonsterKillQuest(m_MonsterTypeInfos[0]);
	}

	int total = m_MonsterTypeInfos.size();
	int level = qcInfo->getLevel();
	int index = total * level / 100;

	index = max(0, min(index, total)); 

	MonsterKillQuest* pQuest =  new MonsterKillQuest(m_MonsterTypeInfos[index]);
	Assert(pQuest!=NULL);

	// deadline
	int availableMinute = (rand()%6)*10+10;	// 10��~60��

	int goldReward 		= (level+(60-availableMinute)*2)*1000;
	int rankExpReward 	= (level+(60-availableMinute)*2)*1000;
	int goldPenalty 	= getPercentValue(goldReward, 20);
	int rankExpPenalty 	= getPercentValue(rankExpReward, 30);

	QuestPrice* pReward = new QuestPriceReward(goldReward, rankExpReward);
	QuestPrice* pPenalty = new QuestPricePenalty(goldPenalty, rankExpPenalty);

	pQuest->addReward( pReward );
	pQuest->addPenalty( pPenalty );

	pQuest->setAvailableSecond( availableMinute*60 );	// ���� �ʷ�

	return pQuest;


	__END_CATCH
}


//--------------------------------------------------------------------------------
// init MonsterTypeInfos
//--------------------------------------------------------------------------------
void		
MonsterKillQuestFactory::initMonsterTypeInfos()
{
	__BEGIN_TRY

	m_MonsterTypeInfos.clear();

	MonsterType_t monsterType	= 0;
	SpriteType_t spriteType		= 0;

	int maxMonsterInfo = g_pMonsterInfoManager->getMaxMonsterType();
	for (int i=0; i<maxMonsterInfo; i++)
	{
		try
		{
			const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( i );

			if (pMonsterInfo!=NULL)
			{		
				if (!pMonsterInfo->isMaster())
				{
					if (pMonsterInfo->isNormalRegen())
					{
						monsterType = 0;
						spriteType	= pMonsterInfo->getSpriteType();				
					}
					else
					{				
						monsterType = i;
						spriteType	= 0;
					}

					MonsterSelector	mtc(monsterType, spriteType, 1);
					
					m_MonsterTypeInfos.push_back( mtc );
				}
			}

		} catch (NoSuchElementException& ) {
		}
	}

	__END_CATCH
}


string
MonsterKillQuest::toString() const
	throw (Error)
{
	__BEGIN_TRY
	
	StringStream msg;
	
	msg << "���� ���̱�(" << getObjectiveToString() << "), "
		<< "����(" << getRewardToString() << ") : "
		<< "����(" << getPenaltyToString() << ")";

	switch (getState())
	{
		case Quest::STATE_NULL :
		case Quest::STATE_WAIT :
		{
			msg << ", ����ð�(" << (m_AvailableSecond/60) << ")��";
		}
		break;

		case Quest::STATE_COMPLETE :
		case Quest::STATE_END :
			msg << ", �Ϸ�";
		break;

		default :
		{
			msg << ", �����ð�(" << (getRemainDuration()/600) << ")��";
		}
	}

	return msg.toString();

	__END_CATCH
}
