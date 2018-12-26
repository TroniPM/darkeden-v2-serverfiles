//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOODY_SHOUT2__
#define __EFFECT_BLOODY_SHOUT2__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyShout2 : public Effect 
{
public:
	EffectBloodyShout2(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_BLOODY_SHOUT2; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setLevel( SkillLevel_t level ) { m_SkillLevel = level; }
	SkillLevel_t getLevel() const { return m_SkillLevel; }

private:
	SkillLevel_t	m_SkillLevel;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyShout2Loader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyShout2Loader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_BLOODY_SHOUT2; }
	virtual string getEffectClassName()  { return "EffectBloodyShout2"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_CONCEALMENT__
