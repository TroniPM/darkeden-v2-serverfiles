//////////////////////////////////////////////////////////////////////////////
// Filename    : EventReloadInfo.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTRESURRECT_H__
#define __EVENTRESURRECT_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventReloadInfo;
//////////////////////////////////////////////////////////////////////////////

class EventReloadInfo : public Event 
{
public :
	enum InfoType
	{
		MASTER_LAIR_INFO,
		MONSTER_INFO,
		MONSTER_AI,
		ZONE_INFO,
		ZONE,
		ITEM_INFO,
		LOG_USER_INFO,
		RANK_BONUS_INFO,
		OPTION_INFO,
		STRING_POOL,
		WAR_SCHEDULE_INFO,
		BLOOD_BIBLE_OWNER,
		RACE_WAR_PC_LIMIT,
		QUEST_INFO,
		GOODS_LIST_INFO,
		SWEEPER_OWNER,
		INSTANT_DUNGEON,
		ITEM_DROP_INFO,
		MAX_INFO
	};

public:
	EventReloadInfo(GamePlayer* pGamePlayer, InfoType infoType, int infoValue=0) ;
	~EventReloadInfo() ;			

public:
	virtual EventClass getEventClass()  { return EVENT_CLASS_RELOAD_INFO; }

	virtual void activate();
	
	virtual string toString() ;

public:
	InfoType getInfoType() const { return m_InfoType; }
	int 	 getInfoValue() const { return m_InfoValue; }


private:
	InfoType 	m_InfoType;
	int			m_InfoValue;
};

#endif
