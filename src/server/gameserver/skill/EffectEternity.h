//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEternity.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ETERNITY__
#define __EFFECT_ETERNITY__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEternity
//////////////////////////////////////////////////////////////////////////////

class EffectEternity : public Effect 
{
public:
	EffectEternity(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ETERNITY; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

	void setHPPenalty( int pen ) { m_HPPenalty = pen; }
	int getHPPenalty() const { return m_HPPenalty; }

public:
	int m_HPPenalty;
	ObjectID_t m_TargetObjectID;
};

#endif // __EFFECT_ETERNITY__
