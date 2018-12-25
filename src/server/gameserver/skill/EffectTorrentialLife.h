//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWhitsuntide.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TORRENTIALLIFE__
#define __EFFECT_TORRENTIALLIFE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectWhitsuntide
//////////////////////////////////////////////////////////////////////////////

class EffectTorrentialLife : public Effect 
{
public:
	EffectTorrentialLife(Creature* pCreature);

public:
	EffectClass getEffectClass()  { return EFFECT_CLASS_TORRENTIALLIFE; }

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

	int getBonus() const { return m_Bonus; }
	void setBonus(int bonus) { m_Bonus = bonus; }

private :
	int m_Bonus;
};

#endif // __EFFECT_TorrentialLife__
