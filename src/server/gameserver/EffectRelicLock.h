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
	EffectRelicLock(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RELIC_LOCK; }

	void affect()  {}
	void affect(Item* pItem);

	void unaffect(Item* pItem);
	void unaffect(); 

	string toString() ;

public:
	//bool   isLockTime() const;
	//void   setLockTime(const Timeval& tv) throw() { m_LockTime = tv; }

private:
	//Timeval m_LockTime;
	
};

#endif // __EFFECT_DOOM__
