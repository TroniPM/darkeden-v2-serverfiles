//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToWolf.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectTransformToWolf.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCAddVampireFromTransformation.h"
#include "Gpackets/GCAddMonsterFromTransformation.h"
#include "ZoneUtil.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTransformToWolf::EffectTransformToWolf(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWolf::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWolf::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWolf::unaffect() 
	
{
	__BEGIN_TRY	

	//cout << "EffectTransfromToWolf " << "unaffect BEGIN" << endl;

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	Assert(pCreature != NULL);

	if (pCreature->isSlayer())
	{
		//cout << "EffectTransfromToWolf::unaffect() : Slayer cannot transfrom to wolf!" << endl;
		throw Error("EffectTransfromToWolf::unaffect() : Slayer cannot transfrom to wolf!");
	}

	unaffect(pCreature);

	//cout << "EffectTransfromToWolf " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWolf::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectTransfromToWolf " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// ���� ������� �ǵ�����, �÷��׸� �����Ѵ�.
	addUntransformCreature(pZone, pCreature, false);
	pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);

	// �ɷ�ġ�� ������� �ǵ�����.
	if (pCreature->isVampire())
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;

		pTargetVampire->getVampireRecord(prev);
		pTargetVampire->initAllStat();
		pTargetVampire->sendRealWearingInfo();
		pTargetVampire->sendModifyInfo(prev);
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		pMonster->initAllStat();
	}
	else
	{
		Assert(false);
	}

	//cout << "EffectTransfromToWolf " << "unaffect END" << endl;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTransformToWolf::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTransformToWolf::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTransformToWolf("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
