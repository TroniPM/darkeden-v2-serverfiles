///////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectEnergyDrop.cpp
// Writer      : ��ȫâ
// Date        : 2002.3.28
// Description :
//               �ش� Effect�� Energy Drop�� ������ ���������� Effect�� �����ϱ� 
//               ���� Effect�̴�. 
//             
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    ��ȫâ      source file �ۼ�
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

	// ��뿡�� �̹� poison ����Ʈ�� �ɷ��� �ִ� ��쿡�� �ɸ��� �ʴ´�.
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE))
	{
		//cout << "EffectMeteoBlaze " << "affectCreature End(Already Effected) " << endl;
		return false;
	}

	// �������� üũ
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
		// ������ ����Ʈ�� �����ؼ�, Ÿ�� ũ���Ŀ� ���̰�, �÷��׸� ���ش�.

		// ������ MeteoBlaze Effect�� ���������� ����� �ʴ´�. �ٸ� Effeect�����
		// ��� �������� ������ �ö󰥼��� Duration�� �����ϰ� �ǰ� �̿� ���� Effect�� ���̰�
		// ������, --Drop, --Storm���� ����� �ϴ� ������ �Ǹ� �ش� ������ ��� �����
		// ����� ���ϰ� �ǰ�, ���� �ð����� �������� �ִ� ���� �ƴ϶� �������� ��������
		// 3����ؼ� �ְ� �ȴ�. ����� �������� �ִ� �Լ��� ���� ���ߵ��� ���� �ܰ��
		// Deadline�� tick�� ����ؼ� ���Ƿ� ������ �Ͽ���.
		// 1.6�� ���ȿ� 0.5�� �������� �������� �ְ� �Ǹ�, 3���� �������� �� �� �ְ� �ȴ�.
		// ���⼭�� �ϵ��ڵ��� �Ǿ� �ִµ�, �̴� �ٸ� ������� ��ü�Ǿ�� �� �� ����.
		// EffectMeteoBlaze Class�� member variable�� 
		//   m_Tick
		//   m_Count
		// �� �ξ �̸� �������� deadline�� ����ؼ� �����Ѵٸ� ���� �� ���� ���̴�.

		EffectMeteoBlazeToCreature* pEffectMeteoBlazeToCreature = new EffectMeteoBlazeToCreature(pTargetCreature);

        // �켱�� �ý����� ���Ͽ� �̸��� ��Ƽ ���̵� �ִ´�.
		pEffectMeteoBlazeToCreature->setUserObjectID( m_UserObjectID );

		pEffectMeteoBlazeToCreature->setLevel(m_Level);
		pEffectMeteoBlazeToCreature->setPoint(m_Damage/3);
		pEffectMeteoBlazeToCreature->setDeadline(15); // �̺κ� �ٲ�� �Ѵ�.
		pEffectMeteoBlazeToCreature->setTick(5);             // �̺κе� �ٲ�� �Ѵ�.
		pEffectMeteoBlazeToCreature->affect(pTargetCreature);
		pTargetCreature->addEffect(pEffectMeteoBlazeToCreature);
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_METEO_BLAZE_TO_CREATURE);

		// ����Ʈ�� �پ��ٰ� �ֺ��� �˷��ش�.
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
