//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMPRecovery.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MP_RECOVERY_H__
#define __EFFECT_MP_RECOVERY_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMPRecovery;
//////////////////////////////////////////////////////////////////////////////

class EffectMPRecovery : public Effect 
{
public:
	EffectMPRecovery();
	EffectMPRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay);
	virtual ~EffectMPRecovery();

public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_MP_RECOVERY; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect();
	virtual void affect(Creature* pCreature);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	
	virtual void unaffect();
	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget);
	void unaffect(Item* pItem) throw(Error) {}

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() ;

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay()  { return m_Delay; }

	void setMPQuantity(MP_t Quantity) throw() { m_MPQuantity = Quantity; }
	MP_t getMPQuantity()  { return m_MPQuantity; }

	void setPeriod(Turn_t Period) throw() { m_Period = Period; }
	Turn_t getPeriod()  { return m_Period; }
	
private:
	Turn_t m_Delay;      // �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
	MP_t   m_MPQuantity; // �Ϸ�� ȸ����
	Turn_t m_Period;     // ȸ���� �Ϸ�Ǵµ� �ɸ��� �ð�.

};

#endif
