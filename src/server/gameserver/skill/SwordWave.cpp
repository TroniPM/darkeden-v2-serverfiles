//////////////////////////////////////////////////////////////////////////////
// Filename    : SwordWave.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SwordWave.h"
#include "SimpleTileMeleeSkill.h"

//////////////////////////////////////////////////////////////////////////////
// ������.. Ÿ�� ����ũ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
SwordWave::SwordWave()
	throw()
{
	__BEGIN_TRY

	// ����ũ�� �ʱ�ȭ��Ų��.
	// �� ������ 3�� Ÿ�� ������ Ŭ���̾�Ʈ ����Ʈ ��� ������ �����.
	//
	// (-1,-1)(0,-1)(1,-1)
	// (-1, 0)(0, 0)(1, 0)
	// (-1, 1)(0, 1)(1, 1)
	//
	// �� ���⿡ ���� ��� Ÿ���� ���� ����̳ĸ�
	// �����ϸ� ����ũ�� �����ϱ� ����.

	m_pSwordWaveMask[LEFT][0].set(-1,  1);
	m_pSwordWaveMask[LEFT][1].set(-1, -1);
	m_pSwordWaveMask[LEFT][2].set(-1,  0);

	m_pSwordWaveMask[RIGHT][0].set(1, -1);
	m_pSwordWaveMask[RIGHT][1].set(1,  1);
	m_pSwordWaveMask[RIGHT][2].set(1,  0);

	m_pSwordWaveMask[UP][0].set(-1, -1);
	m_pSwordWaveMask[UP][1].set(1, -1);
	m_pSwordWaveMask[UP][2].set(0, -1);

	m_pSwordWaveMask[DOWN][0].set(1,  1);
	m_pSwordWaveMask[DOWN][1].set(-1,  1);
	m_pSwordWaveMask[DOWN][2].set(0,  1);

	m_pSwordWaveMask[LEFTUP][0].set(-1,  0);
	m_pSwordWaveMask[LEFTUP][1].set(0, -1);
	m_pSwordWaveMask[LEFTUP][2].set(-1, -1);

	m_pSwordWaveMask[RIGHTDOWN][0].set(1,  0);
	m_pSwordWaveMask[RIGHTDOWN][1].set(0,  1);
	m_pSwordWaveMask[RIGHTDOWN][2].set(1,  1);

	m_pSwordWaveMask[LEFTDOWN][0].set(0,  1);
	m_pSwordWaveMask[LEFTDOWN][1].set(-1,  0);
	m_pSwordWaveMask[LEFTDOWN][2].set(-1,  1);

	m_pSwordWaveMask[RIGHTUP][0].set(0, -1);
	m_pSwordWaveMask[RIGHTUP][1].set(1,  0);
	m_pSwordWaveMask[RIGHTUP][2].set(1, -1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SwordWave::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin(slayerobject)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(slayerobject)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// SwordWave::execute()
//
//////////////////////////////////////////////////////////////////////
void SwordWave::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_SWORD;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	ZoneCoord_t myX = pSlayer->getX();
	ZoneCoord_t myY = pSlayer->getY();	
	Dir_t       dir = calcDirection(myX, myY, X, Y);

	for (int i=0; i<3; i++)
	{
		param.addMask(m_pSwordWaveMask[dir][i].x, m_pSwordWaveMask[dir][i].y, 60);
	}

	g_SimpleTileMeleeSkill.execute(pSlayer, myX, myY, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end" << endl;

	__END_CATCH
}

SwordWave g_SwordWave;
