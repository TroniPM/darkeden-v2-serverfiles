//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSwordOfThor.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SWORD_OF_THOR__
#define __EFFECT_SWORD_OF_THOR__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSwordOfThor
//////////////////////////////////////////////////////////////////////////////

class EffectSwordOfThor : public Effect 
{
public:
	EffectSwordOfThor(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SWORD_OF_THOR; }

	void unaffect();

	string toString() ;

public:
	Level_t getLevel() const { return m_Level; }
	void setLevel( Level_t level ) { m_Level = level; }
	
private:
	Level_t m_Level;
};

#endif
