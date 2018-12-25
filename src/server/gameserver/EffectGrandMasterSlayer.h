//////////////////////////////////////////////////////////////////////////////
// Filename	: EffectGrandMasterSlayer.h
// Written by  : 
// Description : grand master Ƽ ���°�. - -;	 by sigi. 2002.11.8
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
	EffectGrandMasterSlayer(Creature* pCreature);

public:
	EffectClass getEffectClass()  { return EFFECT_CLASS_GRAND_MASTER_SLAYER; }
	EffectClass getSendEffectClass() ;

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

private:
};

#endif
