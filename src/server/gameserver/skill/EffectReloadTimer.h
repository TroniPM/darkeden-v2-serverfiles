//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReloadTimer.h
// Written by  : crazydog
// Description : źâ reload dealy�� ���� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELOAD_TIMER__
#define __EFFECT_RELOAD_TIMER__

#include "Effect.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReloadTimer
//////////////////////////////////////////////////////////////////////////////

class EffectReloadTimer : public Effect 
{
public:
	EffectReloadTimer(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RELOAD_TIMER; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(Item* pItem)  {}
	void unaffect();

	string toString() ;

public:
	void setFromInventory(bool b)  { m_bFromInventory = b; }
	void setSlotID(SlotID_t id)  { m_SlotID = id; }
	void setObjectID(ObjectID_t id)  { m_ObjectID = id; }
	void setInventoryXY(CoordInven_t x, CoordInven_t y)  { m_invenX = x; m_invenY = y; }

private:
	CoordInven_t m_invenX;         // �κ��丮���� ���ε��� ���� ��ǥ
	CoordInven_t m_invenY;         // �κ��丮���� ���ε��� ���� ��ǥ
	ObjectID_t   m_ObjectID;       // źâ object id
	SlotID_t     m_SlotID;         // ��Ʈ���� ���ε��� ���� ��Ʈ slot id
	bool         m_bFromInventory; // �κ��丮���� ���� ���ε��ϴ°�?

};


#endif // __EFFECT_RELOAD_TIMER__
