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
	EffectRageOfBlood(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RAGE_OF_BLOOD; }

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
// class EffectRageOfBloodLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRageOfBloodLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_RAGE_OF_BLOOD; }
	virtual string getEffectClassName()  { return "EffectRageOfBlood"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
