//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRecallMotorcycle.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RECALL_MOTORCYCLE_H__
#define __EFFECT_RECALL_MOTORCYCLE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRecallMotorcycle;
// ���� �ð��� ������ �ٴ��� �������� �������
// �ٸ� ������ �Ű����� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class Item;

class EffectRecallMotorcycle : public Effect 
{
public:
	EffectRecallMotorcycle(Zone* pZone, ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x, ZoneCoord_t y, Item* pItem, ObjectID_t ownerOID, Turn_t delay) throw(Error);
	virtual ~EffectRecallMotorcycle() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_ITEM; }

	// OBJECT_PRIORITY_NONE ��� ����, Ÿ�Ͽ� ������ �ȵȴٴ� ���̴�.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	void unaffect() throw(Error);

	// get debug string
	virtual string toString() const throw();

private:
	ZoneCoord_t m_StartX; 
	ZoneCoord_t m_StartY;
	Zone*		m_pTargetZone;
	ObjectID_t  m_ObjectID;
	ObjectID_t	m_OwnerOID;
};

#endif
