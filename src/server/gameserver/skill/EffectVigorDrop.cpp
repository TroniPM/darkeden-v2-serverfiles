///////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectVigorDrop.cpp
// Writer      : ��ȫâ
// Date        : 2002.3.28
// Description :
//               �ش� Effect�� Vigor Drop�� ������ ���������� Effect�� �����ϱ� 
//               ���� Effect�̴�. 
//             
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    ��ȫâ      source file �ۼ�
//

#include "EffectVigorDrop.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "EffectVigorDropToCreature.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

EffectVigorDrop::EffectVigorDrop(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY)
	throw(Error)
{

	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
//	m_CasterName ="";
//	m_PartyID = 0;
	m_UserObjectID = 0;

	__END_CATCH
}


bool EffectVigorDrop::affectCreature(Creature* pTargetCreature, bool bAffectByMove)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectVigorDrop " << "affectCreature Begin " << endl;

	Assert(pTargetCreature != NULL);

	// ��뿡�� �̹� poison ����Ʈ�� �ɷ��� �ִ� ��쿡�� �ɸ��� �ʴ´�.
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_VIGOR_DROP_TO_CREATURE))
	{
		//cout << "EffectVigorDrop " << "affectCreature End(Already Effected) " << endl;
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
	int DropDamage = computeMagicDamage(pTargetCreature, m_Damage, SKILL_VIGOR_DROP);

	if (DropDamage > 0)
	{
		//cout << "EffectVigorDrop(Damage:" << DropDamage << ") Affected" << endl;
		// ������ ����Ʈ�� �����ؼ�, Ÿ�� ũ���Ŀ� ���̰�, �÷��׸� ���ش�.

		// ������ VigorDrop Effect�� ���������� ����� �ʴ´�. �ٸ� Effeect�����
		// ��� �������� ������ �ö󰥼��� Duration�� �����ϰ� �ǰ� �̿� ���� Effect�� ���̰�
		// ������, --Drop, --Storm���� ����� �ϴ� ������ �Ǹ� �ش� ������ ��� �����
		// ����� ���ϰ� �ǰ�, ���� �ð����� �������� �ִ� ���� �ƴ϶� �������� ��������
		// 3����ؼ� �ְ� �ȴ�. ����� �������� �ִ� �Լ��� ���� ���ߵ��� ���� �ܰ��
		// Deadline�� tick�� ����ؼ� ���Ƿ� ������ �Ͽ���.
		// 1.6�� ���ȿ� 0.5�� �������� �������� �ְ� �Ǹ�, 3���� �������� �� �� �ְ� �ȴ�.
		// ���⼭�� �ϵ��ڵ��� �Ǿ� �ִµ�, �̴� �ٸ� ������� ��ü�Ǿ�� �� �� ����.
		// EffectVigorDrop Class�� member variable�� 
		//   m_Tick
		//   m_Count
		// �� �ξ �̸� �������� deadline�� ����ؼ� �����Ѵٸ� ���� �� ���� ���̴�.

		EffectVigorDropToCreature* pEffectVigorDropToCreature = new EffectVigorDropToCreature(pTargetCreature);

		// �켱�� �ý����� ���Ͽ� �̸��� ��Ƽ ���̵� �ִ´�.
		//pEffectVigorDropToCreature->setCasterName(m_CasterName);
		//pEffectVigorDropToCreature->setPartyID(m_PartyID);
		pEffectVigorDropToCreature->setUserObjectID( m_UserObjectID );

		pEffectVigorDropToCreature->setLevel(m_Level);
		pEffectVigorDropToCreature->setPoint(DropDamage/3);
		pEffectVigorDropToCreature->setDeadline(16); // �̺κ� �ٲ�� �Ѵ�.
		pEffectVigorDropToCreature->setTick(5);             // �̺κе� �ٲ�� �Ѵ�.
		pEffectVigorDropToCreature->affect(pTargetCreature);
		pTargetCreature->addEffect(pEffectVigorDropToCreature);
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_VIGOR_DROP_TO_CREATURE);

		// ����Ʈ�� �پ��ٰ� �ֺ��� �˷��ش�.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pTargetCreature->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_VIGOR_DROP_TO_CREATURE);
		gcAddEffect.setDuration(m_Duration);
		pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect);
	}

	//cout << "EffectVigorDrop " << "affectCreature End " << endl;

	return true;

	__END_CATCH
}


void EffectVigorDrop::affect()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectVigorDrop::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectVigorDrop::affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectVigorDrop::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectVigorDrop::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
    tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

void EffectVigorDrop::unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObjbect)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectVigorDrop::toString()
	const throw()
{
	__BEGIN_TRY

		StringStream msg;

	msg << "EffectVigorDrop("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}

EffectVigorDropLoader* g_pEffectVigorDropLoader = NULL;
