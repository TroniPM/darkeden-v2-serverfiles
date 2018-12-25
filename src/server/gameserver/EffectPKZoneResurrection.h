//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPKZoneResurrection.h
// Written by  : 
// Description : PKZoneResurrection�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PK_ZONE_RESURRECTION__
#define __EFFECT_PK_ZONE_RESURRECTION__

#include "Effect.h"

class Creature;

//////////////////////////////////////////////////////////////////////////////
// class EffectPKZoneResurrection
//////////////////////////////////////////////////////////////////////////////

class EffectPKZoneResurrection : public Effect 
{
public:
	EffectPKZoneResurrection( Creature* pCreature );

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PK_ZONE_RESURRECTION; }

	void affect() throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

public:

private:
};

#endif // __EFFECT_PK_ZONE_RESURRECTION__
