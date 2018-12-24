//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHPRecovery.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HP_RECOVERY_H__
#define __EFFECT_HP_RECOVERY_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHPRecovery;
//////////////////////////////////////////////////////////////////////////////

class EffectHPRecovery : public Effect 
{
public:
	EffectHPRecovery() throw(Error);
	EffectHPRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay) throw(Error);
	virtual ~EffectHPRecovery() throw(Error);
	
public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HP_RECOVERY; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	virtual void affect(Creature* pCreature) throw(Error);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}
	
	virtual string toString() const throw();

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay() const throw() { return m_Delay; }

	void setHPQuantity(HP_t Quantity) throw() { m_HPQuantity = Quantity; }
	HP_t getHPQuantity() const throw() { return m_HPQuantity; }

	void setPeriod(Turn_t Period) throw() { m_Period = Period; }
	Turn_t getPeriod() const throw() { return m_Period; }

private:
	Turn_t m_Delay;      // �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
	HP_t   m_HPQuantity; // �Ϸ�� ȸ����
	Turn_t m_Period;     // ȸ���� �Ϸ�Ǵµ� �ɸ��� �ð�.

};

#endif
