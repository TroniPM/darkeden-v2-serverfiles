//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLight.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectFlameSight.h"
#include "Creature.h"
#include "Ousters.h"
#include "Player.h"
#include "DB.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFlameSight member methods
//////////////////////////////////////////////////////////////////////////////

EffectFlameSight::EffectFlameSight(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectFlameSight::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectFlameSight::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectFlameSight::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectFlameSight " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

	if (pOusters != NULL) 
	{
		Zone* pZone = pOusters->getZone();

		Sight_t NewSight = 0;

		if (pOusters->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			NewSight = 3;
		}
		else 
		{
			NewSight = 13;
		}

		pZone->updateScan(pOusters, pOusters->getSight(), NewSight);
		pOusters->setSight(NewSight);
		
		pOusters->removeFlag(Effect::EFFECT_CLASS_FLAME_SIGHT);
	
		Player* pPlayer = pOusters->getPlayer();
	
		GCModifyInformation _GCModifyInformation; 
	
		_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);
	
		pPlayer->sendPacket(&_GCModifyInformation);

		// 이펙트가 사라졌다고 알려준다.
		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pOusters->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_FLAME_SIGHT);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcRemoveEffect);

		destroy(pOusters->getName());
	}

	//cout << "EffectFlameSight " << "unaffect END" << endl;
	
	__END_CATCH
}

void EffectFlameSight::unaffect()
	
{
	__BEGIN_TRY

	Ousters* pOusters = dynamic_cast<Ousters*>(m_pTarget);
	unaffect(pOusters);
	
	__END_CATCH
}

void EffectFlameSight::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectFlameSight::create(const string & ownerID) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	Timeval currentTime;
	getCurrentTime(currentTime);

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "INSERT INTO EffectFlameSight"
			<< "(OwnerID , YearTime, DayTime, OldSight)"
			<< " VALUES('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< "," <<(int)m_OldSight
			<< ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectFlameSight::destroy(const string & ownerID)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;
		sql << "DELETE FROM EffectFlameSight WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectFlameSight::save(const string & ownerID) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "UPDATE EffectFlameSight SET "
			<< "YearTime = " << currentYearTime
			<< ", DayTime = " << m_Deadline.tv_sec
			<< ", OldSight = " <<(int)m_OldSight
			<< " WHERE OwnerID = '" << ownerID 
			<< "'";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectFlameSight::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectFlameSight("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

void EffectFlameSightLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	if (pCreature == NULL)
	{
		//cout << "EffectFlameSightLoader : 크리쳐가 널입니다." << endl;
		return;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT YearTime, DayTime, OldSight FROM EffectFlameSight"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());

		while(pResult->next())
		{
			if (pCreature->isOusters()) 
			{
				uint i = 0;

				Turn_t YearTime = pResult->getDWORD(++i);
				int DayTime = pResult->getDWORD(++i);

				Turn_t currentYearTime;

				Timeval currentTime;

				getCurrentYearTime(currentYearTime);

				getCurrentTime(currentTime);

				int leftTime =((YearTime-currentYearTime)*24*60*60 +(DayTime-currentTime.tv_sec))*10;
				EffectFlameSight* pEffect = new EffectFlameSight(pCreature);
				if (leftTime > 0)
				{
					pEffect->setDeadline(leftTime);
					pCreature->setFlag(Effect::EFFECT_CLASS_LIGHT);
					pCreature->addEffect(pEffect);
				}
				else
				{
					pEffect->destroy(pCreature->getName());
					SAFE_DELETE(pEffect);
				}
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectFlameSightLoader* g_pEffectFlameSightLoader = NULL;
