//////////////////////////////////////////////////////////////////////////////
// Filename    : HitConvert.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HitConvert.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"
#include "SkillUtil.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HitConvert::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	Item* pWeapon = pSlayer->getWearItem( Slayer::WEAR_RIGHTHAND );
	if ( pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_SWORD )
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = max(1,Random( pWeapon->getMinDamage(), pWeapon->getMaxDamage() )) * ( 1.0f + ( (float)pSkillSlot->getExpLevel() * 4.0f / 100.f ) );
		//(float)pSlayer->getDamage() * ( 1.0f + ( (float)pSkillSlot->getExpLevel() * 4.0f / 100.f ) );
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_SWORD;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	for ( int i=-1; i<=1; ++i )
	for ( int j=-1; j<=1; ++j )
	{
		param.addMask(i, j, 100);
	}

	SIMPLE_SKILL_OUTPUT result;

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (rect.ptInRect(pSlayer->getX(), pSlayer->getY())) bTileCheck = false;
			int edge = 1;
			int oX, oY;

			//////////////////////////////////////////////////////////////////////////
			// check
			for(oY = -edge; oY <= edge; oY++)
			for(oX = -edge; oX <= edge; oX++)
			{
				int tileX = pSlayer->getX()+oX;
				int tileY = pSlayer->getY()+oY;
				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);
					if (tile.canAddEffect())
					{
						if ( tile.getEffect(Effect::EFFECT_CLASS_CRUSHING_STORM) != NULL )
						{
							cout << " 밑에 크러싱 스톰 있음"<<endl;
							bTileCheck = true;
						}

					}

				}
			}
	if(bTileCheck){
	cout << " 크러싱 스톰 추가 데미지 효과 넣음 "<<endl;
	output.Damage += getPercentValue(output.Damage,15);
	}

//    cout << pSlayer->getDamage() << ", " << pSkillSlot->getExpLevel() << ", " << param.SkillDamage << endl;

	Creature* pTargetCreature = pSlayer->getZone()->getCreature( TargetObjectID );
	bool bRangeCheck = pTargetCreature != NULL && verifyDistance(pSlayer, pTargetCreature, output.Range );

	// 저 안에서는 Max Range 만 체크한다. -_-;
	if ( !bRangeCheck )
	{
		executeSkillFailNormal(pSlayer, param.SkillType, pTargetCreature);
		return;
	}

	Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
	{
		executeSkillFailException(pSlayer, param.SkillType);
		return;
	}

	g_SimpleTileMissileSkill.execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, param, result);


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	// knockback 시킨다.
	if ( result.bSuccess )
	{
		int dist = 1 + pSkillSlot->getExpLevel() / 100;
		for ( int i=0; i<dist; ++i )
		{
			knockbackCreature(pSlayer->getZone(), pTargetCreature, pSlayer->getX(), pSlayer->getY() );
		}
	}

	__END_CATCH
}

HitConvert g_HitConvert;


