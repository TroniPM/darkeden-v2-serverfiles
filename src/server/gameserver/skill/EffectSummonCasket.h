//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonCasket.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_CASKET__
#define __EFFECT_SUMMON_CASKET__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonCasket
//////////////////////////////////////////////////////////////////////////////

class EffectSummonCasket : public Effect 
{
public:
	EffectSummonCasket(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_CASKET; }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem)  {}

	string toString() ;

public :
	int getType()  { return m_Type; }
	void setType(int t) throw() { m_Type = t; }

private :
	int m_Type;		// casket ����
};

#endif // __EFFECT_SUMMON_CASKET__
