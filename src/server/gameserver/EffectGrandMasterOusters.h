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
	EffectGrandMasterOusters(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GRAND_MASTER_OUSTERS; }
	EffectClass getSendEffectClass() const throw();

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

private:
};

#endif
