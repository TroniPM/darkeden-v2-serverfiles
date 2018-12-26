//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromCurse.h
// Written by  : excel96
// Description : 
// ProtectionFromCurse�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROTECTION_FROM_CURSE__
#define __EFFECT_PROTECTION_FROM_CURSE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProtectionFromCurse
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromCurse : public Effect 
{
public:
	EffectProtectionFromCurse(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PROTECTION_FROM_CURSE; }

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
// class EffectProtectionFromCurseLoader
//////////////////////////////////////////////////////////////////////////////

class EffectProtectionFromCurseLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_PROTECTION_FROM_CURSE; }
	virtual string getEffectClassName()  { return "EffectProtectionFromCurse"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectProtectionFromCurseLoader* g_pEffectProtectionFromCurseLoader;

#endif // __EFFECT_PROTECTION_FROM_CURSE__
