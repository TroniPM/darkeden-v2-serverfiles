//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTranslation.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSLATION__
#define __EFFECT_TRANSLATION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTranslation
//////////////////////////////////////////////////////////////////////////////

class EffectTranslation : public Effect 
{
public:
	EffectTranslation(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TRANSLATION; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;
};

#endif // __EFFECT_DOOM__
