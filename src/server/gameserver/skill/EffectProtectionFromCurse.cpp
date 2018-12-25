//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromCurse.cpp
// Written by  : excel96
// Description : ProtectionFromCurse�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "EffectProtectionFromCurse.h"
#include "Creature.h"
#include "Slayer.h"
#include "DB.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectProtectionFromCurse::EffectProtectionFromCurse(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurse::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_CURSE);
	resist = min(MAX_RESIST,(int)(resist + m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_CURSE, resist);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurse::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurse::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurse::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	pCreature->removeFlag(Effect::EFFECT_CLASS_PROTECTION_FROM_CURSE);

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_CURSE);
	resist = max(0,(int)(resist - m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_CURSE, resist);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PROTECTION_FROM_CURSE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurse::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectProtectionFromCurse::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectProtectionFromCurse("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromCurseLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

EffectProtectionFromCurseLoader* g_pEffectProtectionFromCurseLoader = NULL;
