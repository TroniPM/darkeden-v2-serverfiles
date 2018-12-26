//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLESS2__
#define __EFFECT_BLESS2__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBless
//////////////////////////////////////////////////////////////////////////////

class EffectBless2 : public Effect 
{
public:
	EffectBless2(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_BLESS2; }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem)  {}

	string toString() ;

public:
	int getSTRBonus(void) const { return m_STRBonus; }
	void setSTRBonus(int bonus) { m_STRBonus = bonus; }

	int getDEXBonus(void) const { return m_DEXBonus; }
	void setDEXBonus(int bonus) { m_DEXBonus = bonus; }

private :
	int m_STRBonus;
	int m_DEXBonus;
};

#endif // __EFFECT_BLESS__
