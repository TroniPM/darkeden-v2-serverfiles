//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRideMotorcycle.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RIDE_MOTORCYCLE_H__
#define __EFFECT_RIDE_MOTORCYCLE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRideMotorcycle;
// ���� �ð��� ������ �ٴ��� �������� �������
// �ٸ� ������ �Ű����� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class Slayer;
class Item;

class EffectRideMotorcycle : public Effect 
{
public:
	EffectRideMotorcycle(Slayer* pOwner, Item* pMotorcycle, ZoneCoord_t motorX, ZoneCoord_t motorY) throw(Error);
	virtual ~EffectRideMotorcycle() throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	void unaffect() throw(Error);

	// get debug string
	string toString() const throw();

private:
	ZoneCoord_t m_MotorX; 
	ZoneCoord_t m_MotorY;
	ObjectID_t	m_OwnerObjectID;
	Item*		m_pMotorcycle;
};

#endif
