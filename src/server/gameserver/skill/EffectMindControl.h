//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMindControl.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MIND_CONTROL__
#define __EFFECT_MIND_CONTROL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMindControl
//////////////////////////////////////////////////////////////////////////////

class EffectMindControl : public Effect 
{
public:
	EffectMindControl(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MIND_CONTROL; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() ;

public:
	int getToHitBonus(void) const { return m_ToHitBonus; }
	void setToHitBonus(int bonus) { m_ToHitBonus = bonus; }

	int getDefenseBonus(void) const { return m_DefenseBonus; }
	void setDefenseBonus(int bonus) { m_DefenseBonus = bonus; }

private:
	int m_ToHitBonus;
	int m_DefenseBonus;
};

#endif // __EFFECT_MIND_CONTROL__
