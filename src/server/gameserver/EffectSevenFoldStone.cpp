//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodDrain.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectSevenFoldStone.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "EventMorph.h"
#include "PlayerCreature.h"
#include "PCManager.h"
#include "GamePlayer.h"
#include "Gpackets/GCMorph1.h"
#include "Gpackets/GCMorphVampire2.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "PCFinder.h"
#include "EventRegeneration.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSevenFoldStone::EffectSevenFoldStone(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::unaffect(Creature* pFromCreature)
	throw(Error)
{
	__BEGIN_TRY 
	Assert(pFromCreature != NULL);
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pFromCreature);
	pFromCreature->removeFlag(getEffectClass());

	Zone* pZone = pFromCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pFromCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());

	pZone->broadcastPacket(pFromCreature->getX(), pFromCreature->getY(), &gcRemoveEffect);

	pPC->initAllStatAndSend();

	destroy( pFromCreature->getName() );
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);
						
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::create(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();


		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		/*
		StringStream sql;

		sql << "INSERT INTO EffectSevenFoldStone "
			<< "(OwnerID , YearTime, DayTime, Level)"
			<< " VALUES('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , " <<(int)m_Level
			<< ")";

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "INSERT INTO EffectItemLoader (OwnerID , DayTime, Level, Bonus) VALUES('%s', '%s', %d, %d)",
								ownerID.c_str(), getLastFeedTime().toDateTime().c_str(), (int)m_EffectLevel, (int)m_Silver);


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM EffectItemLoader WHERE OwnerID = '%s' and Level = %d", 
								ownerID.c_str(),(int)m_EffectLevel);
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStone::save(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		pStmt->executeQuery( "UPDATE EffectItemLoader SET DayTime='%s', Level=%d, Bonus=%d WHERE OwnerID='%s' and Level=%d", 
								getLastFeedTime().toDateTime().c_str(), (int)m_EffectLevel, (int)m_Silver, ownerID.c_str(),(int)m_EffectLevel );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSevenFoldStone::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectSevenFoldStone("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSevenFoldStoneLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	//Assert(pCreature != NULL);
	//if ( !pCreature->isSlayer() && !pCreature->isOusters() ) return;
	if (pCreature == NULL)
	{
		return;
	}
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pCountResult = pStmt->executeQuery( "SELECT COUNT(*) FROM EffectItemLoader WHERE OwnerID='%s'", 
												pCreature->getName().c_str());

		pCountResult->next();
		int count = pCountResult->getDWORD(1);
		SAFE_DELETE(pStmt);

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery( "SELECT DayTime, Level,Bonus FROM EffectItemLoader WHERE OwnerID='%s'", 
												pCreature->getName().c_str());

		while(pResult->next())
		{
			uint i = 0;
			int s = 0;

				VSDateTime MagiccurrentTime = VSDateTime::currentDateTime();
				VSDateTime MagiccurrentTimeWait = VSDateTime(pResult->getString(++i));
				DWORD diffSecs = MagiccurrentTime.secsTo( MagiccurrentTimeWait );

			int EffectClassi = pResult->getInt(++i);
			int Silver= pResult->getInt(++i);
			EffectSevenFoldStone* pEffectSevenFoldStone[count];
			EffectManager* pEffectManager = pCreature->getEffectManager();
			cout << "시간 : " << diffSecs << endl;
				if (MagiccurrentTime <= MagiccurrentTimeWait) 
				{
				cout << " 작동 1 " << endl;
				pEffectSevenFoldStone[s] = new EffectSevenFoldStone(pCreature);
				pEffectSevenFoldStone[s]->setDeadline(diffSecs*10);
				pEffectSevenFoldStone[s]->setLevel(EffectClassi);
				pEffectSevenFoldStone[s]->setEffectType(EffectClassi);
				pEffectSevenFoldStone[s]->setFeedTime(MagiccurrentTimeWait);
				pEffectSevenFoldStone[s]->setHeroOption(Silver);
				pEffectManager->addEffect(pEffectSevenFoldStone[s]);
				pCreature->setFlag((Effect::EffectClass)EffectClassi);
				}else{
				cout << " 작동 2 " << endl;
				pEffectSevenFoldStone[s] = new EffectSevenFoldStone(pCreature);
				pEffectSevenFoldStone[s]->setDeadline(100);
				pEffectSevenFoldStone[s]->setLevel(EffectClassi);
				pEffectSevenFoldStone[s]->setEffectType(EffectClassi);
				pEffectSevenFoldStone[s]->setHeroOption(Silver);
				pEffectManager->addEffect(pEffectSevenFoldStone[s]);
				pCreature->setFlag((Effect::EffectClass)EffectClassi);
				}
				s++;
			cout << "오류의 원인 끝" << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectSevenFoldStoneLoader* g_pEffectSevenFoldStoneLoader = NULL;
