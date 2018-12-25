//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ITEM_LOADER__
#define __EFFECT_ITEM_LOADER__

#include "Effect.h"
#include "EffectLoader.h"
#include "Exception.h"
#include "VSDateTime.h"
#include <string>
#include <hash_map>
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class EffectEffectItemLoader
//////////////////////////////////////////////////////////////////////////////

class EffectItemLoader : public Effect 
{
public:
	EffectItemLoader(Creature* pCreature) throw(Error);
	~EffectItemLoader() throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass()  { return EFFECT_CLASS_SEVEN_FOLD_STONE; }

    virtual void create(const string & ownerID) throw(Error);
    virtual void save(const string & ownerID) throw(Error);
    virtual void destroy(const string & ownerID) throw(Error);

	string toString() ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectItemLoaderLoader
//////////////////////////////////////////////////////////////////////////////

class EffectItemLoaderLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_SEVEN_FOLD_STONE; }
	virtual string getEffectClassName()  { return "EffectItemLoader"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectItemLoaderLoader* g_pEffectItemLoaderLoader;

#endif // __EFFECT_CAN_ENTER_GDR_LAIR__
