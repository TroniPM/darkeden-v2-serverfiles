//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSimyunEnterLoop.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "DB.h"
#include "VSDateTime.h"
#include "time.h"

EffectSimyunEnterLoop::EffectSimyunEnterLoop(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

EffectSimyunEnterLoop::~EffectSimyunEnterLoop()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectSimyunEnterLoop::affect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectSimyunEnterLoop::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

    __END_CATCH
}

void EffectSimyunEnterLoop::unaffect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	pCreature->removeFlag(getEffectClass());

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());

	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	destroy( pCreature->getName() );

	__END_CATCH
}

void EffectSimyunEnterLoop::create (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "INSERT INTO CanEnterGDRLair "
			<< "(OwnerID , YearTime, DayTime, EnemyName)"
			<< " VALUES ('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , '" << m_EnemyName
			<< "')";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO CanSimyun (OwnerID , LimitDateTime) VALUES ('%s', %ld )",
								ownerID.c_str(), m_Deadline.tv_sec);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectSimyunEnterLoop::destroy (const string & ownerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM CanSimyun WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectSimyunEnterLoop::save (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		pStmt->executeQuery("UPDATE CanSimyun SET LimitDateTime = %ld WHERE OwnerID = '%s'",
								m_Deadline.tv_sec, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectSimyunEnterLoop::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSimyunEnterLoop("
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectSimyunEnterLoopLoader::load (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	//Assert(pCreature != NULL);
	if (pCreature == NULL)
	{
		return;
	}

	Statement* pStmt;
	VSDateTime timeLimit = VSDateTime::currentDateTime();
	time_t TimeDateProfile = time(NULL);
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime, EnemyName FROM CanEnterGDRLair"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery( "SELECT LimitDateTime FROM CanSimyun WHERE OwnerID = '%s'",
												pCreature->getName().c_str() );

		while (pResult->next())
		{

			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);
			cout << " 시간 측정 : " << currentTime.tv_sec << endl;
			cout << " 시간 측정2 : " << DayTime << endl;
			cout << " 시간 측정3 : " << DayTime-currentTime.tv_sec << endl;
			EffectSimyunEnterLoop* pEffectSimyunEnterLoop = new EffectSimyunEnterLoop(pCreature);

			EffectManager* pEffectManager = pCreature->getEffectManager();

			if (currentTime.tv_sec < DayTime ) {
				//pEffectSimyunEnterLoop->setDeadline((curSecs2-curSecs) - currentTime.tv_sec);
				pEffectSimyunEnterLoop->setDeadline((DayTime - currentTime.tv_sec) * 10);//user_time * 10);
			} else {
				pEffectSimyunEnterLoop->setDeadline(100);
			}

			pEffectManager->addEffect(pEffectSimyunEnterLoop);
			pCreature->setFlag(pEffectSimyunEnterLoop->getEffectClass());
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectSimyunEnterLoopLoader* g_pEffectSimyunEnterLoopLoader = NULL;
