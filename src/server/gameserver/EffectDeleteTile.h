//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDeleteTile.h
// Description : ������ �Ա��� �ٴ��� ����� ����Ʈ
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DELETE_TILE__
#define __EFFECT_DELETE_TILE__

#include "Effect.h"
#include "EffectLoader.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDeleteTile
//////////////////////////////////////////////////////////////////////////////

class EffectDeleteTile : public Effect 
{
public:
	EffectDeleteTile(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DELETE_TILE; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectDeleteTileLoader
//////////////////////////////////////////////////////////////////////////////

class EffectDeleteTileLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_DELETE_TILE; }
	virtual string getEffectClassName()  { return "EffectDeleteTile"; }

public:
	virtual void load(Creature* pCreature)  {}
};

extern EffectDeleteTileLoader* g_pEffectDeleteTileLoader;

#endif // __EFFECT_DELETE_TILE__

