//////////////////////////////////////////////////////////////////////////////
// Filename    : Untransform.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Untransform.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK3.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCRemoveEffect.h"
#include "ZoneUtil.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Untransform::execute(Slayer * pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);

	try 
	{
		if ( pSlayer->isFlag(Effect::EFFECT_CLASS_INSTALL_TURRET) )
		{
			Zone* pZone = pSlayer->getZone();
			Assert(pZone != NULL);

			Effect* pEffect = pSlayer->findEffect(Effect::EFFECT_CLASS_INSTALL_TURRET);
			if ( pEffect != NULL ) pEffect->setDeadline(0);

			GCSkillToSelfOK1 gcOK1;

			gcOK1.setSkillType( SKILL_UN_TRANSFORM );
			pSlayer->getPlayer()->sendPacket(&gcOK1);

			// EffectSummonSylph�� unaffect���� �� ���ش�.

			// ���� ����Ʈ ���ݴٰ� �����ְ�
//			GCRemoveEffect removeEffect;
//			removeEffect.setObjectID(pSlayer->getObjectID());
//			removeEffect.addEffectList(Effect::EFFECT_CLASS_SUMMON_SYLPH);
//			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &removeEffect);
//			pSlayer->getPlayer()->sendPacket(&removeEffect);
//
//			GCModifyInformation gcMI;
//
//			// ���� ���� �ٽ� ����ؼ� �����ְ�
//			OUSTERS_RECORD prev;
//			pSlayer->getSlayerRecord(prev);
//			pSlayer->initAllStat();
//			pSlayer->addModifyInfo(prev, gcMI);

//			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else
		{
			GCSkillFailed1 gcFail;
			gcFail.setSkillType( SKILL_UN_TRANSFORM );
			pSlayer->getPlayer()->sendPacket(&gcFail);
		}
	} 
	catch(Throwable & t) 
	{
//		Ŭ���̾�Ʈ���� -_- �̷� �� ������ ������ �� �Ф�
//		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Untransform::execute(Vampire * pVampire)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);

	try 
	{
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);
		addUntransformCreature(pZone, pVampire, true);
	} 
	catch(Throwable & t) 
	{
		cout << " ������� ����Ǿ��� 5" << endl;
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Untransform::execute(Ousters * pOusters)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);

	try 
	{
		if ( pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) )
		{
			Zone* pZone = pOusters->getZone();
			Assert(pZone != NULL);

		pOusters->setWingSylphType(0);
		pOusters->setWingItemType(0);
		pOusters->setWingColor(0);
		pOusters->setWingEffectColor(0);

			Effect* pEffect = pOusters->findEffect(Effect::EFFECT_CLASS_SUMMON_SYLPH);
			if ( pEffect != NULL ) pEffect->setDeadline(0);

			GCSkillToSelfOK1 gcOK1;

			gcOK1.setSkillType( SKILL_UN_TRANSFORM );
			pOusters->getPlayer()->sendPacket(&gcOK1);

			// EffectSummonSylph�� unaffect���� �� ���ش�.

			// ���� ����Ʈ ���ݴٰ� �����ְ�
//			GCRemoveEffect removeEffect;
//			removeEffect.setObjectID(pOusters->getObjectID());
//			removeEffect.addEffectList(Effect::EFFECT_CLASS_SUMMON_SYLPH);
//			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &removeEffect);
//			pOusters->getPlayer()->sendPacket(&removeEffect);
//
//			GCModifyInformation gcMI;
//
//			// ���� ���� �ٽ� ����ؼ� �����ְ�
//			OUSTERS_RECORD prev;
//			pOusters->getOustersRecord(prev);
//			pOusters->initAllStat();
//			pOusters->addModifyInfo(prev, gcMI);

//			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else
		{
			GCSkillFailed1 gcFail;
			gcFail.setSkillType( SKILL_UN_TRANSFORM );
			pOusters->getPlayer()->sendPacket(&gcFail);
		}
	} 
	catch(Throwable & t) 
	{
//		Ŭ���̾�Ʈ���� -_- �̷� �� ������ ������ �� �Ф�
//		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Untransform::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);
		addUntransformCreature(pZone, pMonster, true);
	} 
	catch(Throwable & t) 
	{
		//cout << t.toString() << endl;
	}
	
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

Untransform g_Untransform;
