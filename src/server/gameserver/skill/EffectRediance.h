//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRediance.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REDIANCE__
#define __EFFECT_REDIANCE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRediance
//////////////////////////////////////////////////////////////////////////////

class EffectRediance : public Effect 
{
public:
	EffectRediance(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REDIANCE; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getDexBonus()  { return m_DexBonus;}
	void setDexBonus(Attr_t DexBonus)  { m_DexBonus = DexBonus;}

	bool canGiveExp() { return m_GiveExp=!m_GiveExp; }

private :
	Attr_t m_DexBonus;
	bool m_GiveExp;
};

#endif // __EFFECT_REDIANCE__
