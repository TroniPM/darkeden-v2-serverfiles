//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDarknessForbidden.h
// Written by  : elca@ewestsoft.com
// Description : �������� DarknessForbidden�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DARKNESS_FORBIDDEN__
#define __EFFECT_DARKNESS_FORBIDDEN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDarknessForbidden
//////////////////////////////////////////////////////////////////////////////

class EffectDarknessForbidden : public Effect 
{
public:
	EffectDarknessForbidden(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DARKNESS_FORBIDDEN; }

	void unaffect() throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_DARKNESS_FORBIDDEN__
