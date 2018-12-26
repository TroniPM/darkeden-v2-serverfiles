//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIntimateGrail.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INTIMATE_GRAIL__
#define __EFFECT_INTIMATE_GRAIL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIntimateGrail
//////////////////////////////////////////////////////////////////////////////

class EffectIntimateGrail : public Effect 
{
public:
	EffectIntimateGrail(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_INTIMATE_GRAIL; }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem)  {}

	string toString() ;

public:
	int getSkillLevel(void) const { return m_SkillLevel; }
	void setSkillLevel(int level) { m_SkillLevel = level; }


private :
	int m_SkillLevel;
};

#endif // __EFFECT_INTIMATE_GRAIL__
