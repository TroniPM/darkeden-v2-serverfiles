//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPeace.cpp
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectPeace.h"
#include "Peace.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "DB.h"
#include "DarkLightInfo.h"
#include "MonsterInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPeace::EffectPeace(Creature* pCreature, ObjectID_t PeaceCreatureID)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_PeaceCreatureID = PeaceCreatureID;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(!pCreature->isSlayer()); // �����̾�� �ɸ��� �ʴ´�.
	Assert(!pCreature->isNPC()); // NPC�� �ɸ��� �ʴ´�.

	if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		pMonster->deleteEnemy( pCreature->getObjectID() );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectPeace " << "unaffect BEGIN" << endl;

	pCreature->removeFlag(Effect::EFFECT_CLASS_PEACE);

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PEACE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectPeace " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectPeace " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectPeace " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPeace::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPeace::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectPeace("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

