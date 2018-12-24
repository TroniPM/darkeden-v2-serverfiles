//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStormCrushing.cpp
// Written by  : ��ȫâ
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectStormCrushing.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectStormCrushing::EffectStormCrushing(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectStormCrushing " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectStormCrushing " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectStormCrushing " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����ڸ� �����´�.
	// !! �̹� ���� ������ �� �����Ƿ� NULL�� �� �� �ִ�.
	// by bezz. 2003.3.13
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );
	// ĳ���Ͱ� ������ �����Ѵ�.
	if ( pCastCreature == NULL )
		return;

	// EffectStormCrushing�� CrushingStorm, PoisonStorm, BloodyStorm���� �������� �ٴ´�.
	// �̴� 3���� ���� �������� �ְ� �������.

	Damage_t StormDamage = m_Point;
	GCModifyInformation GCAttackerMI;

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// �������� üũ. by sigi. 2002.9.5
		&& canAttack( pCastCreature, pCreature )
		&& !pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
	)
	{
		if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pVampire, StormDamage, pCastCreature, SKILL_CRUSHING_STORM, &gcMI, &GCAttackerMI );

			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pOusters, StormDamage, pCastCreature, SKILL_CRUSHING_STORM, &gcMI, &GCAttackerMI );

			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			setDamage( pMonster, StormDamage, pCastCreature, SKILL_CRUSHING_STORM, NULL, &GCAttackerMI );
		}

		if ( pCastCreature->isSlayer() && pCreature->isDead() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);
			shareAttrExp(pSlayer, StormDamage, 8, 1, 1, GCAttackerMI );
			pSlayer->getPlayer()->sendPacket( &GCAttackerMI );
		}
	}
	
	setNextTime(m_Tick);

	//cout << "EffectStormCrushing " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_STORM_CRUSHING);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_STORM_CRUSHING);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormCrushing::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectStormCrushing::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectStormCrushing("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

