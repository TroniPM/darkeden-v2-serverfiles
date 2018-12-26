//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStormAcid.cpp
// Written by  : ��ȫâ
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectSkullBloody.h"
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
EffectSkullBloody::EffectSkullBloody(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::affect()
	
{
	__BEGIN_TRY

	//cout << "EffectSkullBloody " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectSkullBloody " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectSkullBloody " << "begin" << endl;

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

	// EffectSkullBloody�� AcidStorm, PoisonStorm, BloodyStorm���� �������� �ٴ´�.
	// �̴� 3���� ���� �������� �ְ� �������.

	Damage_t StormDamage = m_Point;
	GCModifyInformation GCAttackerMI;

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
			setDamage( pSlayer, StormDamage, pCastCreature, SKILL_BLOODY_SKULL, &gcMI, &GCAttackerMI );

			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pVampire, StormDamage, pCastCreature, SKILL_BLOODY_SKULL, &gcMI, &GCAttackerMI );

			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pOusters, StormDamage, pCastCreature, SKILL_BLOODY_SKULL, &gcMI, &GCAttackerMI );

			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			setDamage( pMonster, StormDamage, pCastCreature, SKILL_BLOODY_SKULL, NULL, &GCAttackerMI );
		}

		if ( pCastCreature->isVampire() && pCreature->isDead() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCastCreature);
			int exp = computeCreatureExp(pCreature, KILL_EXP);
			shareVampExp(pVampire, exp, GCAttackerMI);
			pVampire->getPlayer()->sendPacket( &GCAttackerMI );
		}

		// m_CasterName�� pCreature�� ���� ����� KillCount ó��
		// by sigi. 2002.9.9
		// setDamage �� �ҷ��� ó���Ѵ�. �ּ�ó��
		// by bezz. 2002.12.31
/*		if (pCreature->isDead())
		{
			Creature* pAttacker = pZone->getCreature( m_UserObjectID );

			if (pAttacker!=NULL)
			{ 
				affectKillCount(pAttacker, pCreature);
			}
		}*/
	}
	
	setNextTime(m_Tick);

	//cout << "EffectSkullBloody " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_SKULL_BLOODY);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SKULL_BLOODY);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSkullBloody::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSkullBloody::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSkullBloody("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

