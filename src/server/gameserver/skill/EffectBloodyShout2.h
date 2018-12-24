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
	EffectBloodyShout2(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOODY_SHOUT2; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

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
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOODY_SHOUT2; }
	virtual string getEffectClassName() const throw() { return "EffectBloodyShout2"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
