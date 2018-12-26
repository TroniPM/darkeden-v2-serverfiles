//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectOnBridge.h
// Written by  : 
// Description : OnBridge�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ON_BRIDGE__
#define __EFFECT_ON_BRIDGE__

#include "Effect.h"
#include "EffectLoader.h"

class Zone;

//////////////////////////////////////////////////////////////////////////////
// class EffectOnBridge
//////////////////////////////////////////////////////////////////////////////

class EffectOnBridge : public Effect 
{
public:
	EffectOnBridge(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ON_BRIDGE; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

};

class EffectOnBridgeLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_ON_BRIDGE; }
	virtual string getEffectClassName()  { return "EffectOnLoader"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone);
};

extern EffectOnBridgeLoader* g_pEffectOnBridgeLoader;

#endif // __EFFECT_ON_BRIDGE__
