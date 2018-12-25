//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProtectionFromAcid.cpp
// Written by  : excel96
// Description : ProtectionFromAcid�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "EffectProtectionFromAcid.h"
#include "Creature.h"
#include "Slayer.h"
#include "DB.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectProtectionFromAcid::EffectProtectionFromAcid(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcid::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_ACID);
	resist = min(MAX_RESIST,(int)(resist + m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_ACID, resist);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcid::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcid::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcid::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	pCreature->removeFlag(Effect::EFFECT_CLASS_PROTECTION_FROM_ACID);

	Resist_t resist = pCreature->getResist(MAGIC_DOMAIN_ACID);
	resist = max(0,(int)(resist - m_Resist));
	pCreature->setResist(MAGIC_DOMAIN_ACID, resist);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PROTECTION_FROM_ACID);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcid::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectProtectionFromAcid::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectProtectionFromAcid("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectProtectionFromAcidLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

EffectProtectionFromAcidLoader* g_pEffectProtectionFromAcidLoader = NULL;
