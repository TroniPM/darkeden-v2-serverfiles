///////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectEnergyDrop.h
// Writer      : ��ȫâ
// Date        : 2002.3.28
// Description :
//               �ش� Effect�� Energy Drop�� ������ ���������� Effect�� �����ϱ� 
//               ���� Effect�̴�. 
//             
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    ��ȫâ      header file �ۼ�
//
//

#ifndef __EFFECT_ENERGY_DROP__
#define __EFFECT_ENERGY_DROP__

#include "Effect.h"
#include "EffectLoader.h"

class EffectEnergyDrop : public Effect
{
public:
	EffectEnergyDrop(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

	EffectClass getEffectClass()  { return EFFECT_CLASS_ENERGY_DROP; }

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
	int 	 	m_Damage;  	    // EffectEnergyDrop Damage;
	Turn_t 		m_Tick;			// EffectEnergyDrop turn;	
	int 		m_Level;		// EffectEnergyDrop level;
	Duration_t 	m_Duration;		// EffectEnergyDrop Duration;
	Duration_t  m_StormDuration; // EnergyDrop Effect ���� �ð� 
};

class EffectEnergyDropLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_ENERGY_DROP; }
	virtual string getEffectClassName()  { return "EffectEnergyDrop"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectEnergyDropLoader* g_pEffectEnergyDropLoader;

#endif
