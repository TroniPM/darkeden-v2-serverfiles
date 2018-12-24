//////////////////////////////////////////////////////////////////////////////
// Filename    : SkyFire.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SkyFire.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include "ZoneUtil.h"
#include "Gpackets/GCAddEffectToTile.h"
#include <list>

void SkyFire::execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);
	
	Creature* pTargetCreature = pZone->getCreature(targetObjectID);
	//Assert(pTargetCreature != NULL);

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	if (pTargetCreature==NULL)
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	execute( pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID );

	__END_CATCH
}

void SkyFire::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

//	cout << "(x,y)=" << X << "," << Y << endl;

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = false;

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
							cout << " ¹Ø¿¡ Å©·¯½Ì ½ºÅè ÀÖÀ½"<<endl;
							bTileCheck = true;
						}

					}

				}
			}
	if(bTileCheck){
	cout << " Å©·¯½Ì ½ºÅè Ãß°¡ µ¥¹ÌÁö È¿°ú ³ÖÀ½ "<<endl;
	output.Damage += getPercentValue(output.Damage,15);
	}

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}

SkyFire g_SkyFire;

