///////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectEnergyDrop.h
// Writer      : 장홍창
// Date        : 2002.3.28
// Description :
//               해당 Effect는 Energy Drop이 땅으로 떨어질때의 Effect를 구현하기 
//               위한 Effect이다. 
//             
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    장홍창      header file 작성
//
//

#ifndef __EFFECT_METEO_BLAZE__
#define __EFFECT_METEO_BLAZE__

#include "Effect.h"
#include "EffectLoader.h"

class EffectMeteoBlaze : public Effect
{
public:
	EffectMeteoBlaze(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

	EffectClass getEffectClass()  { return EFFECT_CLASS_METEO_BLAZE; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

//	int getPartyID(void) const { return m_PartyID; }
//	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove); 
private:
//	string  m_CasterName;
//	int     m_PartyID;
	ObjectID_t	m_UserObjectID;
	int 	 	m_Damage;  	    // EffectMeteoBlaze Damage;
	Turn_t 		m_Tick;			// EffectMeteoBlaze turn;	
	int 		m_Level;		// EffectMeteoBlaze level;
	Duration_t 	m_Duration;		// EffectMeteoBlaze Duration;
	Duration_t  m_StormDuration; // MeteoBlaze Effect 지속 시간 
};

class EffectMeteoBlazeLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_METEO_BLAZE; }
	virtual string getEffectClassName()  { return "EffectMeteoBlaze"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectMeteoBlazeLoader* g_pEffectMeteoBlazeLoader;

#endif
