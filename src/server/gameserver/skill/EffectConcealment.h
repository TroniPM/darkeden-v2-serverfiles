//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CONCEALMENT__
#define __EFFECT_CONCEALMENT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectConcealment : public Effect 
{
public:
	EffectConcealment(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_CONCEALMENT; }

	void affect() throw(Error){}

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
// class EffectConcealmentLoader
//////////////////////////////////////////////////////////////////////////////

class EffectConcealmentLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_CONCEALMENT; }
	virtual string getEffectClassName()  { return "EffectConcealment"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
