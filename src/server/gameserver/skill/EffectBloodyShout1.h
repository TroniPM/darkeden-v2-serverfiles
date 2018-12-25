//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOODY_SHOUT1__
#define __EFFECT_BLOODY_SHOUT1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyShout1 : public Effect 
{
public:
	EffectBloodyShout1(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_BLOODY_SHOUT1; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() ;

public:
	void setLevel( SkillLevel_t level ) { m_SkillLevel = level; }
	SkillLevel_t getLevel() const { return m_SkillLevel; }

private:
	SkillLevel_t	m_SkillLevel;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyShout1Loader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyShout1Loader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_BLOODY_SHOUT1; }
	virtual string getEffectClassName()  { return "EffectBloodyShout1"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
