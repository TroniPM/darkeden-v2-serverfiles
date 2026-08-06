//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIntimateGrail.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INTIMATE_GRAIL2__
#define __EFFECT_INTIMATE_GRAIL2__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIntimateGrail
//////////////////////////////////////////////////////////////////////////////

class EffectIntimateGrail2 : public Effect 
{
public:
	EffectIntimateGrail2(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_INTIMATE_GRAIL2; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();

public:
	int getSkillLevel(void) const { return m_SkillLevel; }
	void setSkillLevel(int level) { m_SkillLevel = level; }


private :
	int m_SkillLevel;
};

#endif // __EFFECT_INTIMATE_GRAIL__
