//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectContinualGroundAttack.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CONTINUAL_GROUND_ATTACK_H__
#define __EFFECT_CONTINUAL_GROUND_ATTACK_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectContinualGroundAttack;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectContinualGroundAttack : public Effect 
{
public:
	EffectContinualGroundAttack(Zone* pZone, EffectClass attackEffect, Turn_t delay) throw(Error);
	virtual ~EffectContinualGroundAttack() throw(Error);

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_CONTINUAL_GROUND_ATTACK; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	
	virtual void unaffect() throw(Error);

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() ;

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay()  { return m_Delay; }

	EffectClass getAttackEffectClass()  { return m_AttackEffect; }

	void setNumber(int minNumber, int maxNumber) { m_MinNumber=minNumber; m_MaxNumber=maxNumber; }
	int getMinNumber() const 	{ return m_MinNumber; }
	int getMaxNumber() const 	{ return m_MaxNumber; }
	
private:
	EffectClass m_AttackEffect;
	Turn_t 		m_Delay;
	int    		m_MinNumber;
	int    		m_MaxNumber;

};

#endif
