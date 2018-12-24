//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVampirePortal.h
// Written by  : excel96
// Description : 
// �����̾ ��Ż�� �� ���, ��Ż�� �� ���� ��ǥ ������ ���ÿ� �����
// Ÿ�Ͽ� ���� �����̾� ��Ż ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VAMPIRE_PORTAL__
#define __EFFECT_VAMPIRE_PORTAL__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectVampirePortal
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItem;

class EffectVampirePortal : public Effect 
{
public:
	EffectVampirePortal(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_VAMPIRE_PORTAL; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error) {};
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();

public:
	string getOwnerID(void) const { return m_OwnerID; }
	void setOwnerID(string ownerID) { m_OwnerID = ownerID; }

	ZONE_COORD getZoneCoord(void) const { return m_ZoneCoord; }
	void setZoneCoord(ZONE_COORD& rCoord) { m_ZoneCoord = rCoord; }
	void setZoneCoord(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y) { m_ZoneCoord.id = id; m_ZoneCoord.x = x; m_ZoneCoord.y = y; }

	Duration_t getDuration() const { return m_Duration;}
	void setDuration(Duration_t d) { m_Duration = d;}

	int getCount(void) const { return m_Count; }
	void setCount(int count) { m_Count = count; }

private:
	string      m_OwnerID;   // �� ��Ż�� ����
	ZONE_COORD  m_ZoneCoord; // ��Ż�� ��ǥ �� ID �� ��ǥ
	Duration_t  m_Duration;  // ������ ���� �ð�
	int         m_Count;     // �� ��Ż�� ����� �� �ִ� �ִ� Ƚ��
};

#endif // __EFFECT_VAMPIRE_PORTAL__
