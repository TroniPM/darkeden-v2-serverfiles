//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromAcid.h
// Written by  : excel96
// Description : 
// ProtectionFromAcid�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_ACID__
#define __EFFECT_PROTECTION_FROM_ACID__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromAcid
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromAcid : public Effect 
{
public:
	EffectProtectionFromAcid(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PROTECTION_FROM_ACID; }

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
// class EffectProtectionFromAcidLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromAcidLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_PROTECTION_FROM_ACID; }
	virtual string getEffectClassName()  { return "EffectProtectionFromAcid"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectProtectionFromAcidLoader* g_pEffectProtectionFromAcidLoader;

#endif // __EFFECT_PROTECTION_FROM_ACID__
