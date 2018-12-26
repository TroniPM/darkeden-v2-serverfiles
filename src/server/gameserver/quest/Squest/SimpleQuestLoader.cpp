//--------------------------------------------------------------------------------
// SimpleQuestLoader.cpp
//--------------------------------------------------------------------------------

#include "SimpleQuestLoader.h"
#include "Assert.h"
#include "DB.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "Timeval.h"
#include "SimpleQuest.h"
#include "QuestFactoryManager.h"

void	
SimpleQuestLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

	// ������ quest�� �� ����� �ٽ� load�Ѵ�.
	pPC->removeAllQuest();

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery( 
			"SELECT QuestType, Objective, Reward, Penalty, DayTime FROM SimpleQuest WHERE OwnerID = '%s'",
			pCreature->getName().c_str() );


		while (pResult->next())
		{
			uint i = 0;

			Timeval currentTime;
            getCurrentTime(currentTime);

			Quest::QuestType questType = (Quest::QuestType)pResult->getInt(++i);

			Quest* pQuest = QuestFactoryManager::getInstance()->create( questType );
			Assert(pQuest!=NULL);

			SimpleQuest* pSimpleQuest = dynamic_cast<SimpleQuest*>(pQuest);
			Assert(pSimpleQuest!=NULL);

			pSimpleQuest->setObjective( pResult->getString(++i) );
			pSimpleQuest->addReward( pResult->getString(++i) );
			pSimpleQuest->addPenalty( pResult->getString(++i) );


			int DayTime = pResult->getDWORD(++i);

			// deadline üũ
			if (currentTime.tv_sec < DayTime)
			{
				pSimpleQuest->setDeadline((DayTime - currentTime.tv_sec)* 10);
			}
			else
			{
				pSimpleQuest->setDeadline( 0 );
			}

			// Creature�� QuestManager�� �߰��Ѵ�.
			pSimpleQuest->take( pCreature, false );
			pPC->addQuest( pSimpleQuest );

			//cout << "[SimpleQuest] load : " << pSimpleQuest->toString().c_str() << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

