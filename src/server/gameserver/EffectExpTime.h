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
	EffectExpTime(Zone* pZone);
	virtual ~EffectExpTime();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_EXP_TIME; }

	virtual void affect();
	
	virtual void unaffect();

	void create(const string & ownerID)  {}
	void save(const string & ownerID)  {}
	void destroy(const string & ownerID)  {}

	virtual string toString() ;
};

#endif
