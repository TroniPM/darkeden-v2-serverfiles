//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EAGLES_EYE1__
#define __EFFECT_EAGLES_EYE1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectEaglesEye1 : public Effect 
{
public:
	EffectEaglesEye1(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_EAGLES_EYE1; }

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
// class EffectEaglesEye1Loader
//////////////////////////////////////////////////////////////////////////////

class EffectEaglesEye1Loader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_EAGLES_EYE1; }
	virtual string getEffectClassName()  { return "EffectEaglesEye1"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_CONCEALMENT__
