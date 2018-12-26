//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RAGE_OF_BLOOD__
#define __EFFECT_RAGE_OF_BLOOD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectRageOfBlood : public Effect 
{
public:
	EffectRageOfBlood(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RAGE_OF_BLOOD; }

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
// class EffectRageOfBloodLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRageOfBloodLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_RAGE_OF_BLOOD; }
	virtual string getEffectClassName()  { return "EffectRageOfBlood"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_CONCEALMENT__
