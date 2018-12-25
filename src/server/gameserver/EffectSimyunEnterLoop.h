//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SIMYUN_ENTER_LOOP__
#define __EFFECT_SIMYUN_ENTER_LOOP__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEffectCanEnterGDRLair
//////////////////////////////////////////////////////////////////////////////

class EffectSimyunEnterLoop : public Effect 
{
public:
	EffectSimyunEnterLoop(Creature* pCreature) throw(Error);
	~EffectSimyunEnterLoop() throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass()  { return EFFECT_CLASS_SIMYUN_ENTER_LOOP; }

    virtual void create(const string & ownerID) throw(Error);
    virtual void save(const string & ownerID) throw(Error);
    virtual void destroy(const string & ownerID) throw(Error);

	string toString() ;

public:
	void setTimeDate(int TimeDate) throw() { m_TimeDate = TimeDate; }
	int getTimeDate()  { return m_TimeDate; }


private:
	int m_TimeDate;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectSimyunEnterLoopLoader
//////////////////////////////////////////////////////////////////////////////

class EffectSimyunEnterLoopLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_SIMYUN_ENTER_LOOP; }
	virtual string getEffectClassName()  { return "EffectSimyunEnterLoop"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectSimyunEnterLoopLoader* g_pEffectSimyunEnterLoopLoader;

#endif // __EFFECT_CAN_ENTER_GDR_LAIR__
