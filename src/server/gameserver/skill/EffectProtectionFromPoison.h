//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromPoison.h
// Written by  : excel96
// Description : 
// ProtectionFromPoison�� ���ؼ� �����Ǵ� �������� ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_POISON__
#define __EFFECT_PROTECTION_FROM_POISON__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromPoison
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromPoison : public Effect 
{
public:
	EffectProtectionFromPoison(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PROTECTION_FROM_POISON; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
	Resist_t getResist(void)  { return m_Resist; }
	void setResist(Resist_t resist) { m_Resist = resist; }

private :
	Resist_t m_Resist;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromPoisonLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromPoisonLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_PROTECTION_FROM_POISON; }
	virtual string getEffectClassName()  { return "EffectProtectionFromPoison"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectProtectionFromPoisonLoader* g_pEffectProtectionFromPoisonLoader;

#endif // __EFFECT_PROTECTION_FROM_POISON__
