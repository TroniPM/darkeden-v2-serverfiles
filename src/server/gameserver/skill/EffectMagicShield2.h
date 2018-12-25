//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MAGIC_SHIELD2__
#define __EFFECT_MAGIC_SHIELD2__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectMagicShield2 : public Effect 
{
public:
	EffectMagicShield2(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MAGIC_SHIELD2; }

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
// class EffectMagicShield2Loader
//////////////////////////////////////////////////////////////////////////////

class EffectMagicShield2Loader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_MAGIC_SHIELD2; }
	virtual string getEffectClassName()  { return "EffectMagicShield2"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
