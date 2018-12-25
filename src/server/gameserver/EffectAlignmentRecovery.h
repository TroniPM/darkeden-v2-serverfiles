//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAlignmentRecovery.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ALIGNMENT_RECOVERY_H__
#define __EFFECT_ALIGNMENT_RECOVERY_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAlignmentRecovery;
//////////////////////////////////////////////////////////////////////////////

class EffectAlignmentRecovery : public Effect 
{
public:
	EffectAlignmentRecovery();
	EffectAlignmentRecovery(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature* pCreature, Turn_t delay);
	virtual ~EffectAlignmentRecovery();
			
public:
	virtual EffectClass getEffectClass()  { return EFFECT_CLASS_ALIGNMENT_RECOVERY; }

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

	void setQuantity(Alignment_t Quantity) throw() { m_AlignmentQuantity = Quantity; }
	Alignment_t getQuantity()  { return m_AlignmentQuantity; }

	void setPeriod(Turn_t Period) throw() { m_Period = Period; }
	Turn_t getPeriod()  { return m_Period; }
	
private:
	// �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
	Turn_t m_Delay;

	// �Ϸ�� ȸ����
	Alignment_t m_AlignmentQuantity;

	// ȸ���� �Ϸ�Ǵµ� �ɸ��� �ð�.
	Turn_t m_Period;
};

#endif
