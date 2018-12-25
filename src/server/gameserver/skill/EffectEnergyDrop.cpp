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

#include "EffectEnergyDrop.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "EffectEnergyDropToCreature.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

EffectEnergyDrop::EffectEnergyDrop(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY)
	throw(Error)
{

	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserObjectID = 0;
//	m_CasterName ="";
//	m_PartyID = 0;

	__END_CATCH
}


bool EffectEnergyDrop::affectCreature(Creature* pTargetCreature, bool bAffectByMove)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectEnergyDrop " << "affectCreature Begin " << endl;

	Assert(pTargetCreature != NULL);

	// ��뿡�� �̹� poison ����Ʈ�� �ɷ��� �ִ� ��쿡�� �ɸ��� �ʴ´�.
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_ENERGY_DROP_TO_CREATURE))
	{
		//cout << "EffectEnergyDrop " << "affectCreature End(Already Effected) " << endl;
		return false;
	}

	// �������� üũ
	// 2003.1.10 by bezz, Sequoia
	if ( !checkZoneLevelToHitTarget(pTargetCreature) )
	{
		return false;
	}
	
	Zone* pZone = pTargetCreature->getZone();

	// ���濡�� ��ĥ �� �������� ����Ѵ�.
	int DropDamage = computeMagicDamage(pTargetCreature, m_Damage, SKILL_ENERGY_DROP);

	//cout << "EffectEnergyDrop(Damage:" << DropDamage << ") Affected" << endl;
	if (DropDamage > 0)
	{
		// ������ ����Ʈ�� �����ؼ�, Ÿ�� ũ���Ŀ� ���̰�, �÷��׸� ���ش�.

		// ������ EnergyDrop Effect�� ���������� ����� �ʴ´�. �ٸ� Effeect�����
		// ��� �������� ������ �ö󰥼��� Duration�� �����ϰ� �ǰ� �̿� ���� Effect�� ���̰�
		// ������, --Drop, --Storm���� ����� �ϴ� ������ �Ǹ� �ش� ������ ��� �����
		// ����� ���ϰ� �ǰ�, ���� �ð����� �������� �ִ� ���� �ƴ϶� �������� ��������
		// 3����ؼ� �ְ� �ȴ�. ����� �������� �ִ� �Լ��� ���� ���ߵ��� ���� �ܰ��
		// Deadline�� tick�� ����ؼ� ���Ƿ� ������ �Ͽ���.
		// 1.6�� ���ȿ� 0.5�� �������� �������� �ְ� �Ǹ�, 3���� �������� �� �� �ְ� �ȴ�.
		// ���⼭�� �ϵ��ڵ��� �Ǿ� �ִµ�, �̴� �ٸ� ������� ��ü�Ǿ�� �� �� ����.
		// EffectEnergyDrop Class�� member variable�� 
		//   m_Tick
		//   m_Count
		// �� �ξ �̸� �������� deadline�� ����ؼ� �����Ѵٸ� ���� �� ���� ���̴�.

		EffectEnergyDropToCreature* pEffectEnergyDropToCreature = new EffectEnergyDropToCreature(pTargetCreature);

        // �켱�� �ý����� ���Ͽ� �̸��� ��Ƽ ���̵� �ִ´�.
//		pEffectEnergyDropToCreature->setCasterName(m_CasterName);
//		pEffectEnergyDropToCreature->setPartyID(m_PartyID);
		pEffectEnergyDropToCreature->setUserObjectID( m_UserObjectID );

		pEffectEnergyDropToCreature->setLevel(m_Level);
		pEffectEnergyDropToCreature->setPoint(DropDamage/3);
		pEffectEnergyDropToCreature->setDeadline(16); // �̺κ� �ٲ�� �Ѵ�.
		pEffectEnergyDropToCreature->setTick(5);             // �̺κе� �ٲ�� �Ѵ�.
		pEffectEnergyDropToCreature->affect(pTargetCreature);
		pTargetCreature->addEffect(pEffectEnergyDropToCreature);
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_ENERGY_DROP_TO_CREATURE);

		// ����Ʈ�� �پ��ٰ� �ֺ��� �˷��ش�.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pTargetCreature->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_ENERGY_DROP_TO_CREATURE);
		gcAddEffect.setDuration(m_Duration);
		pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect);
	}

	//cout << "EffectEnergyDrop " << "affectCreature End " << endl;

	return true;

	__END_CATCH
}


void EffectEnergyDrop::affect()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectEnergyDrop::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEnergyDrop::affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEnergyDrop::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEnergyDrop::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
    tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

void EffectEnergyDrop::unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObjbect)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectEnergyDrop::toString()
	
{
	__BEGIN_TRY

		StringStream msg;

	msg << "EffectEnergyDrop("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}

EffectEnergyDropLoader* g_pEffectEnergyDropLoader = NULL;
