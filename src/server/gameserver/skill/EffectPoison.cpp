//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPoison.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectPoison.h"
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
EffectPoison::EffectPoison(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectPoison " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectPoison " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectPoison " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ��ų ����ڸ� �����´�.
	// !! �̹� ���� ������ �� �����Ƿ� NULL�� �� �� �ִ�.
	// by bezz. 2003.1.4
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );

	// EffectPoison�� ũ���Ŀ��� �ɸ��� �Ǵ� ��쿡�� ����μ��� 
	// GreenPoison�� ���� Ÿ�� ���� ���� 
	// EffectGreenPoison ���� �÷��̾ ������ �� ���̴�.
	// EffectGreenPoison ���ο�??������ ����ؼ� �������� ������ ����
	// EffectPoison�� ���̹Ƿ�, ���ο��� �ѹ� �� ����ϸ� �ȵȴ�.
	//Damage_t PoisonDamage = computeMagicDamage(pCreature, m_Point, MAGIC_DOMAIN_POISON, m_Level);
	Damage_t PoisonDamage = m_Point;
	cout << " ������ ����Ʈ ��� 1 " <<endl;
	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// �������� üũ. by sigi. 2002.9.5
		&& canAttack( pCastCreature, pCreature )
		)
	{
	cout << " ������ ����Ʈ ��� 2 " <<endl;
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	cout << " ������ ����Ʈ ��� 3.1 " <<endl;
			GCModifyInformation gcMI;
			::setDamage( pSlayer, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI );
			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isVampire())
		{
	cout << " ������ ����Ʈ ��� 3.2 " <<endl;
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			::setDamage( pVampire, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI );
			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
	cout << " ������ ����Ʈ ��� 3.3 " <<endl;
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			GCModifyInformation gcMI;
			::setDamage( pOusters, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI );
			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
	cout << " ������ ����Ʈ ��� 3.4 " <<endl;
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			::setDamage( pMonster, PoisonDamage, pCastCreature, SKILL_GREEN_POISON );
		}
	cout << " ������ ����Ʈ ��� 3 " <<endl;
		// m_CasterName�� pCreature�� ���� ����� KillCount ó��
		// by sigi. 2002.9.9
/*		if (pCreature->isDead())
		{
			Creature* pAttacker = pZone->getCreature( m_UserObjectID );

			if (pAttacker!=NULL)
			{ 
				affectKillCount(pAttacker, pCreature);
			}
		}*/
	}
	cout << " ������ ����Ʈ ��� 4 " <<endl;
	setNextTime(m_Tick);

	//cout << "EffectPoison " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_POISON);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_POISON);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPoison::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPoison("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

