//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectContinualGroundAttack.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EXP_TIME_H__
#define __EFFECT_EXP_TIME_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectContinualGroundAttack;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectExpTime : public Effect 
{
public:
	EffectExpTime(Zone* pZone) throw(Error);
	virtual ~EffectExpTime() throw(Error);

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_EXP_TIME; }

	virtual void affect() throw(Error);
	
	virtual void unaffect() throw(Error);

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() ;
};

#endif
