#ifndef __EFFECT_REGEN_ZONE_H__
#define __EFFECT_REGEN_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Effect.h"
#include "RegenZoneManager.h"

class MonsterCorpse;

class EffectRegenZone : public Effect
{
public:
	EffectRegenZone( MonsterCorpse* pTower );

	EffectClass	getEffectClass()  { return Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE; }
	EffectClass	getSendEffectClass()  { return (EffectClass)(getEffectClass() + m_OwnerRace); }
	void setOwner( RegenZoneInfo::RegenZoneIndex Owner ) { m_OwnerRace = Owner; }

	void unaffect() throw(Error);

	string toString()  { return "EffectRegenZone"; }

private:
	RegenZoneInfo::RegenZoneIndex	m_OwnerRace;
};

#endif
