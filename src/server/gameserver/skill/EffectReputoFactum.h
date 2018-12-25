
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReputoFactum.h
// Written by  : 
// Description : ReputoFactum�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REPUTO_FACTUM__
#define __EFFECT_REPUTO_FACTUM__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReputoFactum
//////////////////////////////////////////////////////////////////////////////

class EffectReputoFactum : public Effect 
{
public:
	EffectReputoFactum(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REPUTO_FACTUM_LAST; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

};

#endif // __EFFECT_REPUTO_FACTUM__
