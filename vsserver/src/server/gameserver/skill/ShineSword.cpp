//////////////////////////////////////////////////////////////////////////////
// Filename    : ShineSword.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ShineSword.h"
#include "SimpleTileMissileSkill.h"
#include "EffectCurseOfBloodGround.h"
#include "Gpackets/GCAddEffectToTile.h"
//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void ShineSword::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	if (pTargetCreature==NULL)
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

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

	g_SimpleTileMissileSkill.execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, param, result);

	if ( result.bSuccess )
	{
		for ( int i=-2; i<=2; ++i )
		for ( int j=-2; j<=2; ++j )
		{
			ZoneCoord_t tx = pTargetCreature->getX()+i;
			ZoneCoord_t ty = pTargetCreature->getY()+j;

			if ( !isValidZoneCoord(pZone, tx, ty) ) continue;
			Tile& rTile = pZone->getTile(tx, ty);
			if ( !rTile.canAddEffect() ) continue;

			EffectCurseOfBloodGround* pEffect = new EffectCurseOfBloodGround(pZone, tx, ty);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ShineSword g_ShineSword;
