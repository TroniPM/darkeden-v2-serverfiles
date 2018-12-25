//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAirShield.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AIR_SHIELD__
#define __EFFECT_AIR_SHIELD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAirShield
//////////////////////////////////////////////////////////////////////////////

class EffectAirShield : public Effect 
{
public:
	EffectAirShield(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_AIR_SHIELD_1; }
	EffectClass getSendEffectClass()  { return m_ClientEffectClass; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect() throw(Error);

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) throw();

	EffectClass getClientEffectClass()  { return m_ClientEffectClass; }
	void setClientEffectClass(EffectClass effectClass) throw() { m_ClientEffectClass = effectClass; }

	Damage_t getDamage()  { return m_Damage; }
	void setDamage(Damage_t Damage) throw() { m_Damage = Damage; }

private:
	Level_t 		m_Level;				// ��ų ����
	EffectClass 	m_ClientEffectClass;	// Ŭ���̾�Ʈ�� �����ٶ� ���� ����Ʈ Ŭ���� ���̵�
	Damage_t 		m_Damage;				// ���������� �ִ� ������
};

//////////////////////////////////////////////////////////////////////////////
// class EffectAirShieldLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAirShieldLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_AIR_SHIELD_1; }
	virtual string getEffectClassName()  { return "EffectAirShield"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_AIR_SHIELD__
