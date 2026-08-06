//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectItemLoader.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "DB.h"

EffectItemLoader::EffectItemLoader(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

EffectItemLoader::~EffectItemLoader()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectItemLoader::affect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectItemLoader::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

    __END_CATCH
}

void EffectItemLoader::unaffect (Creature* pCreature)
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

void EffectItemLoader::create (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		/*
		StringStream sql;
		sql << "INSERT INTO EffectItemLoader "
			<< "(OwnerID , YearTime, DayTime, EnemyName)"
			<< " VALUES ('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , '" << m_EnemyName
			<< "')";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO EffectItemLoader (OwnerID , YearTime, DayTime) VALUES ('%s', %ld, %ld)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectItemLoader::destroy (const string & ownerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM EffectItemLoader WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectItemLoader::save (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		pStmt->executeQuery("UPDATE EffectItemLoader SET YearTime = %ld, DayTime = %ld WHERE OwnerID = '%s'",
								currentYearTime, m_Deadline.tv_sec, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectItemLoader::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectItemLoader("
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectItemLoaderLoader::load (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	//Assert(pCreature != NULL);
	if (pCreature == NULL)
	{
		return;
	}

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime, EnemyName FROM EffectItemLoader"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery( "SELECT DayTime FROM EffectItemLoader WHERE OwnerID = '%s'",
												pCreature->getName().c_str() );
		cout << "여기서 오류나나?"<<endl;
		while (pResult->next())
		{

			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectItemLoader* pEffectItemLoader = new EffectItemLoader(pCreature);

			EffectManager* pEffectManager = pCreature->getEffectManager();

			if (currentTime.tv_sec < DayTime) {
				pEffectItemLoader->setDeadline((DayTime - currentTime.tv_sec)* 10);
			} else {
				pEffectItemLoader->setDeadline(100);
			}

			pEffectManager->addEffect(pEffectItemLoader);
			pCreature->setFlag(pEffectItemLoader->getEffectClass());
		}

		SAFE_DELETE(pStmt);
		cout << "여기서 오류나나?2"<<endl;
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectItemLoaderLoader* g_pEffectItemLoaderLoader = NULL;
