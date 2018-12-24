//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicLock.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC_LOCK__
#define __EFFECT_RELIC_LOCK__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelicLock
//////////////////////////////////////////////////////////////////////////////
// ���� �����뿡 �ٴ� ����Ʈ�̴�.

class EffectRelicLock : public Effect 
{
public:
	EffectRelicLock(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RELIC_LOCK; }

	void affect() throw(Error) {}
	void affect(Item* pItem) throw(Error);

	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	//bool   isLockTime() const;
	//void   setLockTime(const Timeval& tv) throw() { m_LockTime = tv; }

private:
	//Timeval m_LockTime;
	
};

#endif // __EFFECT_DOOM__
