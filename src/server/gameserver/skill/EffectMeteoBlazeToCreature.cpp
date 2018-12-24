//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEnergyDropToCreature.cpp
// Written by  : ��ȫâ
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectMeteoBlazeToCreature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMeteoBlazeToCreature::EffectMeteoBlazeToCreature(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
//	m_CasterName ="";
//	m_PartyID = 0;

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectMeteoBlazeToCreature " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectMeteoBlazeToCreature " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectMeteoBlazeToCreature " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ ����ڸ� �����´�.
	// !! �̹� ���� ������ �� �����Ƿ� NULL �� �� �� �ִ�.
	// by bezz. 2003.1.4
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );
	if ( pCastCreature == NULL )
		return;

	// EffectMeteoBlazeToCreature�� AcidStorm, PoisonStorm, BloodyStorm���� �������� �ٴ´�.
	// �̴� 3���� ���� �������� �ְ� �������.

	Damage_t DropDamage = m_Point;

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// �������� üũ. by sigi. 2002.9.5
        && canAttack( pCastCreature, pCreature )
		&& !pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
		)
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pSlayer, DropDamage, pCastCreature, SKILL_METEO_BLAZE, &gcMI );

			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pVampire, DropDamage, pCastCreature, SKILL_METEO_BLAZE, &gcMI );

			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			setDamage( pMonster, DropDamage, pCastCreature, SKILL_METEO_BLAZE );
		}

		// m_CasterName�� pCreature�� ���� ����� KillCount ó��
		// by sigi. 2002.9.9
		// set damage�� �ҷ��� ó���Ѵ�.
		// by bezz. 2002.12.31 �ٽ� �ּ� ó��
	}
	
	setNextTime(m_Tick);

	//cout << "EffectMeteoBlazeToCreature " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMeteoBlazeToCreature::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMeteoBlazeToCreature("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

