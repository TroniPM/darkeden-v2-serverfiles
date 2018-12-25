//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrandMasterOusters.h
// Written by  : 
// Description : grand master Ƽ ���°�. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GRAND_MASTER_OUSTERS__
#define __EFFECT_GRAND_MASTER_OUSTERS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrandMasterOusters
//////////////////////////////////////////////////////////////////////////////

class EffectGrandMasterOusters : public Effect 
{
public:
	EffectGrandMasterOusters(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GRAND_MASTER_OUSTERS; }
	EffectClass getSendEffectClass() ;

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

private:
};

#endif
