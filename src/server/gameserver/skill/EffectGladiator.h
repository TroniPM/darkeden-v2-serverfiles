//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GLADIATOR__
#define __EFFECT_GLADIATOR__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBless
//////////////////////////////////////////////////////////////////////////////

class EffectGladiator : public Effect 
{
public:
	EffectGladiator(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GLADIATOR; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() ;

public:
	int getProtectionBonus(void) const { return m_ProtectionBonus; }
	void setProtectionBonus(int bonus) { m_ProtectionBonus = bonus; }

	int getDamageBonus(void) const { return m_DamageBonus; }
	void setDamageBonus(int bonus) { m_DamageBonus = bonus; }

	int getINTBonus(void) const { return m_INTBonus; }
	void setINTBonus(int bonus) { m_INTBonus = bonus; }


private :
	int m_ProtectionBonus;
	int m_DamageBonus;
	int m_INTBonus;
};

#endif // __EFFECT_BLESS__
