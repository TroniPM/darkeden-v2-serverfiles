//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRevealer.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRevealer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRevealer::EffectRevealer(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// ����Ʈ ������ �����̾�� �� �� �ִ�.
	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectRevealer " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// �÷��׸� �����Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_REVEALER);

	// ������ ������ ���� �ִ� ũ���ĵ��� �����Ѵ�.
	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);
	pZone->updateMineScan(pCreature);
	// ���� hidden�� ����.
	pZone->updateHiddenScan(pCreature);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_REVEALER);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectRevealer " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRevealer::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRevealer("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

bool EffectRevealer::canSeeHide( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_HIDE ) )
		return true;

	Level_t level;
	
	if ( pTarget->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pTarget);
		Assert( pVampire != NULL );

		level = pVampire->getLevel();
	}
	else if ( pTarget->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTarget);
		Assert( pMonster != NULL );

		level = pMonster->getLevel();
	}
	else
	{
		throw Error( "�����̾ ���Ͱ� �ƴѵ� ���̵��ϰ� �ִ�" );
	}

	if ( m_SkillLevel >= 25 && m_SkillLevel > level )
		return true;
	else
		return false;
}

bool EffectRevealer::canSeeSniping( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_SNIPING_MODE ) )
		return true;

	Assert( pTarget->isSlayer() );
	Slayer* pSlayer = dynamic_cast<Slayer*>(pTarget);

	ExpLevel_t level;

	SkillSlot* pSkillSlot = pSlayer->getSkill( SKILL_SNIPING );
	Assert( pSkillSlot != NULL );

	level = pSkillSlot->getExpLevel();

	if ( m_SkillLevel >= 45 && m_SkillLevel > level )
		return true;
	else
		return false;
}

bool EffectRevealer::canSeeInvisibility( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_INVISIBILITY ) )
		return true;

	Level_t level;

	if ( pTarget->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pTarget);
		Assert( pVampire != NULL );

		level = pVampire->getLevel();
	}
	else if ( pTarget->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTarget);
		Assert( pMonster != NULL );

		level = pMonster->getLevel();
	}
	else
	{
		throw Error( "�����̾ ���Ͱ� �ƴѵ� �κ�������Ƽ�� ���� �ִ�." );
	}

	if ( m_SkillLevel >=65 && (m_SkillLevel-20) >= level )
		return true;
	else
		return false;
}

