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
	EffectSimyunEnterLoop(Creature* pCreature);
	~EffectSimyunEnterLoop();

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

    EffectClass getEffectClass()  { return EFFECT_CLASS_SIMYUN_ENTER_LOOP; }

    virtual void create(const string & ownerID);
    virtual void save(const string & ownerID);
    virtual void destroy(const string & ownerID);

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
	virtual void load(Creature* pCreature);
};

extern EffectSimyunEnterLoopLoader* g_pEffectSimyunEnterLoopLoader;

#endif // __EFFECT_CAN_ENTER_GDR_LAIR__
