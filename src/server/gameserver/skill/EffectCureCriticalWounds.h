//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCureCriticalWounds.h
// Written by  : elca@ewestsoft.com
// Description : �������� CureCriticalWounds�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CURE_CRITICAL_WOUNDS__
#define __EFFECT_CURE_CRITICAL_WOUNDS__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCureCriticalWounds
//////////////////////////////////////////////////////////////////////////////

class EffectCureCriticalWounds : public Effect 
{
public:
	EffectCureCriticalWounds(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_CURE_CRITICAL_WOUNDS; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	// unaffect method
	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
	Range_t getRange()  { return m_Range; }
	void setRange(HP_t Range) throw() { m_Range = Range; }

	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setDelay(Turn_t Delay) throw() { m_Delay = Delay; }
	Turn_t getDelay()  { return m_Delay; }

private:

	Range_t m_Range;
	HP_t    m_Point;
	Turn_t  m_Delay;

};

#endif // __EFFECT_CURE_CRITICAL_WOUNDS__
