//////////////////////////////////////////////////////////////////////////////
// Filename	: EffectGrandMasterSlayer.h
// Written by  : 
// Description : grand master 티 내는거. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GRAND_MASTER_SLAYER__
#define __EFFECT_GRAND_MASTER_SLAYER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrandMasterSlayer
//////////////////////////////////////////////////////////////////////////////

class EffectGrandMasterSlayer : public Effect 
{
public:
	EffectGrandMasterSlayer(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass()  { return EFFECT_CLASS_GRAND_MASTER_SLAYER; }
	EffectClass getSendEffectClass() ;

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

private:
};

#endif
