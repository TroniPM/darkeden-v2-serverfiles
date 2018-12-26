//////////////////////////////////////////////////////////////////////////////
// Filename    : MoleShot.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MoleShot.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include "ItemUtil.h"

void MoleShot::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pWeapon == NULL || isArmsWeapon(pWeapon) == false )
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

	// �Ѿ� ���ڴ� ������ ����߸���.
	Bullet_t RemainBullet = 0;
	if (bBulletCheck)
	{
		// �Ѿ� ���ڸ� ����߸���, �����ϰ�, ���� �Ѿ� ���ڸ� �޾ƿ´�.
		decreaseBullet(pWeapon);
		RemainBullet = getRemainBullet(pWeapon);
	}
	else
	{
		executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		return;
	}

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	pSlayer->setFlag( Effect::EFFECT_CLASS_MOLE_SHOT );

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 8;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
//	param.bExpForTotalDamage = true;

	SIMPLE_SKILL_OUTPUT result;

	// ��ǥ��ġ+4����
	param.addMask( 0,  0, 100);
	param.addMask(-1, -1, 100);
	param.addMask( 0, -1, 100);
	param.addMask( 1, -1, 100);
	param.addMask(-1,  0, 100);
	param.addMask( 1,  0, 100);
	param.addMask(-1,  1, 100);
	param.addMask( 0,  1, 100);
	param.addMask( 1,  1, 100);

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void MoleShot::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature!=NULL)
	{
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	}
	else
	{
		executeSkillFailException(pSlayer, getSkillType());
	}


	__END_CATCH
}

MoleShot g_MoleShot;
