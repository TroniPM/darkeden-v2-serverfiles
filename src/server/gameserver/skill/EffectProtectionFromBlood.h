//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromBlood.h
// Written by  : excel96
// Description : 
// ProtectionFromBlood�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_BLOOD__
#define __EFFECT_PROTECTION_FROM_BLOOD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromBlood
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromBlood : public Effect 
{
public:
	EffectProtectionFromBlood(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PROTECTION_FROM_BLOOD; }

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
// class EffectProtectionFromBloodLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromBloodLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_PROTECTION_FROM_BLOOD; }
	virtual string getEffectClassName()  { return "EffectProtectionFromBlood"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectProtectionFromBloodLoader* g_pEffectProtectionFromBloodLoader;

#endif // __EFFECT_PROTECTION_FROM_BLOOD__
