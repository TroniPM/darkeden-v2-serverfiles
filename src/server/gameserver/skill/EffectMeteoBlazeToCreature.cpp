//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEnergyDropToCreature.cpp
// Written by  : 장홍창
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
	
{
	__BEGIN_TRY

	//cout << "EffectMeteoBlazeToCreature " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트 사용자를 가져온다.
	// !! 이미 존을 나갔을 수 있으므로 NULL 이 될 수 있다.
	// by bezz. 2003.1.4
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );
	if ( pCastCreature == NULL )
		return;

	// EffectMeteoBlazeToCreature은 AcidStorm, PoisonStorm, BloodyStorm위를 지나갈때 붙는다.
	// 이는 3번의 연속 데미지를 주고 사라진다.

	Damage_t DropDamage = m_Point;

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// 무적상태 체크. by sigi. 2002.9.5
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

		// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
		// by sigi. 2002.9.9
		// set damage를 불러서 처리한다.
		// by bezz. 2002.12.31 다시 주석 처리
	}
	
	setNextTime(m_Tick);

	//cout << "EffectMeteoBlazeToCreature " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
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
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMeteoBlazeToCreature::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMeteoBlazeToCreature::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMeteoBlazeToCreature("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

