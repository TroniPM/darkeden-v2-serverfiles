//////////////////////////////////////////////////////////////////////////////
// Filename	: EffectGrandMasterSlayer.h
// Written by  : 
// Description : grand master 티 내는거. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MONSTER_MASTER_EFFECT1__
#define __EFFECT_MONSTER_MASTER_EFFECT1__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrandMasterSlayer
//////////////////////////////////////////////////////////////////////////////

class EffectMonsterMasterEffect1 : public Effect 
{
public:
	EffectMonsterMasterEffect1(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass()  { return EFFECT_CLASS_MONSTER_MASTER_EFFECT1; }
	EffectClass getSendEffectClass() ;

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

private:
};

#endif
