//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGhost.h
// Written by  : 
// Description : ZoneID ������ ���� ������
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GHOST__
#define __EFFECT_GHOST__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGhost
//////////////////////////////////////////////////////////////////////////////

class EffectGhost : public Effect 
{
public:
	EffectGhost(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GHOST; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

private:
};

#endif
