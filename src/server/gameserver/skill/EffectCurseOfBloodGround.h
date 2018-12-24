//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CURSE_OF_BLOOD_GROUND__
#define __EFFECT_CURSE_OF_BLOOD_GROUND__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHeavenGround
//////////////////////////////////////////////////////////////////////////////

class EffectCurseOfBloodGround : public Effect 
{
public:
	EffectCurseOfBloodGround(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CURSE_OF_BLOOD_GROUND; }

	void unaffect() throw(Error);

	string toString() const throw();

public:
	Level_t getLevel() const { return m_Level; }
	void setLevel( Level_t level ) { m_Level = level; }
	
private:
	Level_t m_Level;
};

#endif
