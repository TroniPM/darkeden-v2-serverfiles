//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodDrain.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SEVEN_FOLD_STONE__
#define __EFFECT_SEVEN_FOLD_STONE__

#include "Effect.h"
#include "EffectLoader.h"
#include "VSDateTime.h"
//////////////////////////////////////////////////////////////////////////////
// class EffectBloodDrain
//////////////////////////////////////////////////////////////////////////////

class EffectSevenFoldStone : public Effect 
{
public:
	EffectSevenFoldStone(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return (Effect::EffectClass)m_EffectLevel; }

	void affect() throw(Error) { }
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);
	virtual void save(const string & ownerID);

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

	EnchantLevel_t getHeroOption()  { return m_Silver; }
	void setHeroOption(EnchantLevel_t Silver) throw() { m_Silver = Silver; }

	int getEffectType()  { return m_EffectLevel; }
	void setEffectType(int Level) throw() { m_EffectLevel = Level; }

	VSDateTime&	getLastFeedTime() { return m_LastFeedTime; }
	void		setFeedTime(const VSDateTime& time) { m_LastFeedTime = time; }

private:
	Level_t m_Level;
	EnchantLevel_t	m_Silver;
	int	m_EffectLevel;
	VSDateTime m_LastFeedTime;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectSevenFoldStoneLoader
//////////////////////////////////////////////////////////////////////////////

class EffectSevenFoldStoneLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return (Effect::EffectClass)getEffectClass(); }
	virtual string getEffectClassName()  { return "EffectSevenFoldStone"; }

public:
	virtual void load(Creature* pCreature);

};

extern EffectSevenFoldStoneLoader* g_pEffectSevenFoldStoneLoader;

#endif // __EFFECT_BLOOD_DRAIN__
