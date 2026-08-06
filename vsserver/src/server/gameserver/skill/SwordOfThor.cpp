//////////////////////////////////////////////////////////////////////////////
// Filename    : SwordOfThor.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SwordOfThor.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include "EffectSwordOfThor.h"
#include "ZoneUtil.h"
#include "Gpackets/GCAddEffectToTile.h"
#include <list>

void SwordOfThor::execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error)
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

void SwordOfThor::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
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
	param.ItemClass     = Item::ITEM_CLASS_SWORD;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = false;
	param.bExpForTotalDamage = false;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
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
							bTileCheck = true;
						}

					}

				}
			}
	if(bTileCheck){
	output.Damage += getPercentValue(output.Damage,15);
	}

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	if ( result.bSuccess )
	{
		for ( int i=-2; i<=2; ++i )
		for ( int j=-2; j<=2; ++j )
		{
			ZoneCoord_t tx = X+i;
			ZoneCoord_t ty = Y+j;

			if ( !isValidZoneCoord(pZone, tx, ty) ) continue;
			Tile& rTile = pZone->getTile(tx, ty);
			if ( !rTile.canAddEffect() ) continue;

			EffectSwordOfThor* pEffect = new EffectSwordOfThor(pZone, tx, ty);
			pEffect->setLevel( input.SkillLevel );
			pEffect->setDeadline( output.Duration );
			pZone->registerObject( pEffect );

			if ( i != 0 || j != 0 ) pEffect->setBroadcastingEffect(false);
			else
			{
				GCAddEffectToTile gcAE;
				gcAE.setEffectID( pEffect->getSendEffectClass() );
				gcAE.setXY( tx, ty );
				gcAE.setObjectID( pEffect->getObjectID() );
				gcAE.setDuration( output.Duration );
				pZone->broadcastPacket( tx, ty, &gcAE );

//				cout << tx << ", " << ty << " Effect broadcast" << endl;
			}

			pZone->addEffect( pEffect );
			rTile.addEffect( pEffect );
//			cout << tx << ", " << ty << " add Effect" << endl;
		}
	}

	__END_CATCH
}

SwordOfThor g_SwordOfThor;

