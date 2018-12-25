//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ALLYSTER_WIND__
#define __EFFECT_ALLYSTER_WIND__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectAllysterWind : public Effect 
{
public:
	EffectAllysterWind(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ALLYSTER_WIND; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() ;

public:
	void setLevel( int level ) { m_SkillLevel = level; }
	int getLevel() const { return m_SkillLevel; }

private:
	int	m_SkillLevel;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectAllysterWindLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAllysterWindLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_ALLYSTER_WIND; }
	virtual string getEffectClassName()  { return "EffectAllysterWind"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
