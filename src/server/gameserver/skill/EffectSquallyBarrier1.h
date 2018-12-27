//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SQUALLY_BARRIER1__
#define __EFFECT_SQUALLY_BARRIER1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectSquallyBarrier1 : public Effect 
{
public:
	EffectSquallyBarrier1(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SQUALLY_BARRIER1; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) ;

	EffectClass getClientEffectClass()  { return m_ClientEffectClass; }
	void setClientEffectClass(EffectClass effectClass)  { m_ClientEffectClass = effectClass; }

private:
	Level_t 		m_Level;				// ��ų ����
	EffectClass 	m_ClientEffectClass;	// Ŭ���̾�Ʈ�� �����ٶ� ���� ����Ʈ Ŭ���� ���̵�

};

//////////////////////////////////////////////////////////////////////////////
// class EffectSquallyBarrier1Loader
//////////////////////////////////////////////////////////////////////////////

class EffectSquallyBarrier1Loader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_SQUALLY_BARRIER1; }
	virtual string getEffectClassName()  { return "EffectSquallyBarrier1"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_CONCEALMENT__
