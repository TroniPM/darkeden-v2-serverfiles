//////////////////////////////////////////////////////////////////////////////
// Filename    : DragonTornado.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "DragonHurricane.h"
#include "SimpleMeleeSkill.h"
#include "EffectDragonHurricane.h"

#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void DragonHurricane::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_BLADE;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	//cout << "DragonHurricane damage = " << output.Damage << endl;

	g_SimpleMeleeSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	if (result.bSuccess)
	{
		//cout << "DragonHurricane Success" << endl;
		Zone* pZone = pSlayer->getZone();
		Assert(pZone!=NULL);

		Creature* pCreature = pZone->getCreature( TargetObjectID );

		if (pCreature!=NULL)
		{
			// ������ ��츸 delay�� �߰��Ѵ�.
			// player���� client���� ó���ϰ� �Ǿ��ִ�.
			if (pCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				// delay���� ( + 1�� )
				if (!pMonster->isMaster())
				{
					Timeval delay;
					delay.tv_sec  = 1;
					delay.tv_usec = 0;//500000;
					pMonster->addAccuDelay(delay);
				}
			}

			Tile& tile = pZone->getTile( pCreature->getX(), pCreature->getY() );

			if ( tile.canAddEffect() )
			{
				EffectDragonHurricane* pEffect = new EffectDragonHurricane( pZone, pCreature->getX(), pCreature->getY() );
				pEffect->setUserOID( pSlayer->getObjectID() );
				pEffect->setDamage( output.Range );
				pEffect->setChildDamage( output.Tick );
				pEffect->setDeadline( output.Duration );
				pEffect->setNextTime(10);
				pZone->registerObject( pEffect );
				tile.addEffect( pEffect );
				pZone->addEffect( pEffect );

				GCAddEffectToTile gcAE;
				gcAE.setEffectID( pEffect->getSendEffectClass() );
				gcAE.setObjectID( pEffect->getObjectID() );
				gcAE.setDuration( output.Duration );
				gcAE.setXY( pCreature->getX(), pCreature->getY() );
				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAE );
			}
		}
	}
	
	// ��뿡�� �������� �� ���� ����Ʈ�� �ٿ��ش�.

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

DragonHurricane g_DragonHurricane;
