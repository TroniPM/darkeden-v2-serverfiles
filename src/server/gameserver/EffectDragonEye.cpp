//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDragonEye.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDragonEye.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDragonEye::EffectDragonEye(Creature* pCreature)
	throw(Error)
: EffectHasRelic( pCreature )
{
	__BEGIN_TRY


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDragonEye::EffectDragonEye(Item* pItem)
	throw(Error)
: EffectHasRelic( pItem )
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonEye::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// HP �� �ι�~
	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord(prev);
		pSlayer->initAllStat();
		pSlayer->sendModifyInfo(prev);
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;
		pVampire->getVampireRecord(prev);
		pVampire->initAllStat();
		pVampire->sendModifyInfo(prev);
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->sendModifyInfo(prev);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonEye::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// HP �������
	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord(prev);
		pSlayer->initAllStat();
		pSlayer->sendModifyInfo(prev);
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		VAMPIRE_RECORD prev;
		pVampire->getVampireRecord(prev);
		pVampire->initAllStat();
		pVampire->sendModifyInfo(prev);
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->sendModifyInfo(prev);
	}

	EffectHasRelic::unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDragonEye::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDragonEye::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDragonEye("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

