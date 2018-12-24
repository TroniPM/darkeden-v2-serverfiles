//////////////////////////////////////////////////////////////////////////////
// Filename    : FireMeteor.cpp
// Written by  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FireMeteor.h"
#include "RankBonus.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void FireMeteor::execute(Ousters* pOusters, ObjectID_t targetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pOusters->getZone();
	Assert(pZone != NULL);
	
	Creature* pTargetCreature = pZone->getCreature(targetObjectID);
	//Assert(pTargetCreature != NULL);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetCreature==NULL)
	{
		executeSkillFailException(pOusters, getSkillType());
		return;
	}

	execute( pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID );

	__END_CATCH
}
	
void FireMeteor::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{

	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;
	try {
		
	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}


	SIMPLE_SKILL_OUTPUT result;

	// Holy Smashing 이 있다면 데미지 10% 증가
	/*if ( pOusters->hasRankBonus( RankBonus::RANK_BONUS_HOLY_SMASHING ) )
	{
		RankBonus* pRankBonus = pOusters->getRankBonus( RankBonus::RANK_BONUS_HOLY_SMASHING );
		Assert( pRankBonus != NULL );

		param.SkillDamage += pRankBonus->getPoint();
	}*/

	g_SimpleTileMissileSkill.execute(pOusters, X, Y, pOustersSkillSlot, param, result);

	} catch ( Throwable & t ) {
		executeSkillFailException(pOusters, getSkillType());
	}

	__END_CATCH
}

FireMeteor g_FireMeteor;
