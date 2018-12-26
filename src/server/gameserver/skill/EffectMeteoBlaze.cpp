///////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectEnergyDrop.cpp
// Writer      : 장홍창
// Date        : 2002.3.28
// Description :
//               해당 Effect는 Energy Drop이 땅으로 떨어질때의 Effect를 구현하기 
//               위한 Effect이다. 
//             
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    장홍창      source file 작성
//

#include "EffectMeteoBlaze.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "EffectMeteoBlazeToCreature.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

EffectMeteoBlaze::EffectMeteoBlaze(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY)
	
{

	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserObjectID = 0;

	__END_CATCH
}


bool EffectMeteoBlaze::affectCreature(Creature* pTargetCreature, bool bAffectByMove)
	
{
	__BEGIN_TRY

	//cout << "EffectMeteoBlaze " << "affectCreature Begin " << endl;

	Assert(pTargetCreature != NULL);

	// 상대에게 이미 poison 이펙트가 걸려져 있는 경우에는 걸리지 않는다.
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE))
	{
		//cout << "EffectMeteoBlaze " << "affectCreature End(Already Effected) " << endl;
		return false;
	}

	// 안전지대 체크
	// 2003.1.10 by bezz, Sequoia
	if ( !checkZoneLevelToHitTarget(pTargetCreature) )
	{
		return false;
	}
	
	Zone* pZone = pTargetCreature->getZone();

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );

	//cout << "EffectMeteoBlaze(Damage:" << DropDamage << ") Affected" << endl;
	if (m_Damage > 0)
	{
		// 포이즌 이펙트를 생성해서, 타겟 크리쳐에 붙이고, 플래그를 켜준다.

		// 현제는 MeteoBlaze Effect를 지속적으로 운영하지 않는다. 다른 Effeect기술의
		// 경우 시전자의 레벨이 올라갈수록 Duration이 증가하게 되고 이에 대한 Effect를 붙이게
		// 되지만, --Drop, --Storm류의 기술은 일단 성공이 되면 해당 구역의 모든 사람이
		// 기술을 당하게 되고, 각각 시간으로 데미지를 주는 것이 아니라 일정량의 데미지를
		// 3등분해서 주게 된다. 몇번의 데미지를 주는 함수는 아직 개발되지 않은 단계라서
		// Deadline과 tick을 사용해서 임의로 구현을 하였다.
		// 1.6초 동안에 0.5초 간격으로 데미지를 주게 되면, 3번의 데미지를 줄 수 있게 된다.
		// 여기서는 하드코딩이 되어 있는데, 이는 다른 방법으로 교체되어야 할 거 같다.
		// EffectMeteoBlaze Class에 member variable로 
		//   m_Tick
		//   m_Count
		// 를 두어서 이를 바탕으로 deadline을 계산해서 적용한다면 더욱 더 편할 것이다.

		EffectMeteoBlazeToCreature* pEffectMeteoBlazeToCreature = new EffectMeteoBlazeToCreature(pTargetCreature);

        // 우선권 시스템을 위하여 이름과 파티 아이디를 넣는다.
		pEffectMeteoBlazeToCreature->setUserObjectID( m_UserObjectID );

		pEffectMeteoBlazeToCreature->setLevel(m_Level);
		pEffectMeteoBlazeToCreature->setPoint(m_Damage/3);
		pEffectMeteoBlazeToCreature->setDeadline(15); // 이부분 바꿔야 한다.
		pEffectMeteoBlazeToCreature->setTick(5);             // 이부분도 바꿔야 한다.
		pEffectMeteoBlazeToCreature->affect(pTargetCreature);
		pTargetCreature->addEffect(pEffectMeteoBlazeToCreature);
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);

		// 이펙트가 붙었다고 주변에 알려준다.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pTargetCreature->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);
		gcAddEffect.setDuration(m_Duration);
		pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect);
	}

	//cout << "EffectMeteoBlaze " << "affectCreature End " << endl;

	return true;

	__END_CATCH
}


void EffectMeteoBlaze::affect()
	
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectMeteoBlaze::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMeteoBlaze::affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMeteoBlaze::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMeteoBlaze::unaffect()
	
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
    tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

void EffectMeteoBlaze::unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObjbect)
	
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectMeteoBlaze::toString()
	
{
	__BEGIN_TRY

		StringStream msg;

	msg << "EffectMeteoBlaze("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}

EffectMeteoBlazeLoader* g_pEffectMeteoBlazeLoader = NULL;
