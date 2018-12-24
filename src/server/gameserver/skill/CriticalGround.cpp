//////////////////////////////////////////////////////////////////////////////
// Filename    : CriticalGround.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CriticalGround.h"
//#include "Gpackets/GCSkillToSelfOK1.h"
//#include "Gpackets/GCSkillToSelfOK2.h"
#include "SimpleTileMeleeSkill.h"


//////////////////////////////////////////////////////////////////////////////
// ������
// ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
CriticalGround::CriticalGround()
	    throw()
{
	__BEGIN_TRY

	// ���� 8Ÿ��
	m_pCriticalGroundMask[0].set(1,  1);
	m_pCriticalGroundMask[1].set(-1, -1);
	m_pCriticalGroundMask[2].set(0, -1);
	m_pCriticalGroundMask[3].set(1, -1);
	m_pCriticalGroundMask[4].set(-1,  0);
	m_pCriticalGroundMask[5].set(1,  0);
	m_pCriticalGroundMask[6].set(-1,  1);
	m_pCriticalGroundMask[7].set(0,  1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
/*
void CriticalGround::execute(Vampire* pVampire, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot);
		bool bTileCheck     = canBurrow(pZone, x, y);
		bool bMoveModeCheck = pVampire->isWalking();
		bool bEffected      = pVampire->isFlag(Effect::EFFECT_CLASS_HIDE);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck && bMoveModeCheck && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);
			
			// �����̾ �� ������ �����ϱ� ������ ��� ��Ŷ���� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setXY(x, y);
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pVampire);

			// �� ���� �����ִ� �����̾� �����϶�� �˸���.
			GCDeleteObject gcDO;
			gcDO.setObjectID(pVampire->getObjectID());
			pZone->broadcastPacket(x, y, &gcDO, pVampire);

			// �� �ӿ��ٰ� �����̾ �߰��Ѵ�.
			addBurrowingCreature(pZone, pVampire, x, y);
			
			pSkillSlot->setRunTime();
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}
*/

//////////////////////////////////////////////////////////////////////////////
// ���� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void CriticalGround::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		//GCSkillToSelfOK2 _GCSkillToSelfOK2;

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		bool bMoveModeCheck = pMonster->isWalking();

		if (bRangeCheck && bMoveModeCheck)
		{
			//--------------------------------------------------------
			// Critical Ground ����� ���̰� �Ѵ�.
			//--------------------------------------------------------
			//_GCSkillToSelfOK2.setObjectID(pMonster->getObjectID());
			//_GCSkillToSelfOK2.setDuration(0);
			//_GCSkillToSelfOK2.setSkillType(getSkillType());
			//pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2);


			//--------------------------------------------------------
			// ������ knockback�Ǵ¸´� �ֵ��� üũ���ش�.
			//--------------------------------------------------------
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			SIMPLE_SKILL_INPUT param;
			param.SkillType     = getSkillType();
			param.SkillDamage   = output.Damage;
			param.Delay         = output.Delay;
			param.ItemClass     = Item::ITEM_CLASS_MAX;
			param.STRMultiplier = 0;
			param.DEXMultiplier = 0;
			param.INTMultiplier = 0;
			param.bMagicHitRoll = true;
			param.bMagicDamage  = true;
			param.bAdd          = false;

			SIMPLE_SKILL_OUTPUT result;

			for (int i=0; i<8; i++)
			{
				param.addMask(m_pCriticalGroundMask[i].x, m_pCriticalGroundMask[i].y, 100);
			}

			// ������ �´� �ֵ��� knockback ��Ų��.
			bool bForceKnockback = true;
			g_SimpleTileMeleeSkill.execute(pMonster, x, y,param, result,0,bForceKnockback);
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

CriticalGround g_CriticalGround;
