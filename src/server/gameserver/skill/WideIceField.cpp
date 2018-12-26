//////////////////////////////////////////////////////////////////////////////
// Filename    : WideIceField.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "WideIceField.h"
#include "EffectIceField.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// ���� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void WideIceField::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin(monster) " << endl;

	try
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = SKILL_WIDE_ICE_FIELD;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bHitRoll    = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		Range_t Range = 5;

		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		if (bHitRoll)
		{
			// �������� ���� �ð��� ����Ѵ�.
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			for ( int i=-2; i<=2; ++i )
			{
				for ( int j=-2; j<=2; ++j )
				{
					bool bTileCheck = false;
					VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

					ZoneCoord_t tX = X + i;
					ZoneCoord_t tY = Y + j;
					if (rect.ptInRect(tX, tY))
					{
						Tile& tile = pZone->getTile(tX, tY);
						if (tile.canAddEffect()) bTileCheck = true;
						// �ӽ� �׶��� ���� �߰� ���Ѵ�.
						if ( tile.getEffect(Effect::EFFECT_CLASS_MERCY_GROUND) != NULL ) bTileCheck=false;
					}

					if ( !bTileCheck ) continue;

					Tile&   tile  = pZone->getTile(tX, tY);
					
					// ���� ����Ʈ�� �̹� �����Ѵٸ� �����Ѵ�.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_ICE_FIELD);
					if (pOldEffect != NULL)
					{
						ObjectID_t effectID = pOldEffect->getObjectID();
						pZone->deleteEffect(effectID);
					}
					
					// ����Ʈ ������Ʈ�� �����Ѵ�.
					EffectIceField* pEffect = new EffectIceField(pZone, tX, tY);
					pEffect->setCasterName( pMonster->getName() );
					pEffect->setCasterID( pMonster->getObjectID() );
					pEffect->setDeadline(output.Duration);
					pEffect->setDuration(output.Range);
					pEffect->setNextTime(0);
					pEffect->setTick(output.Tick);
					pEffect->setForce(true);

					// Ÿ�Ͽ� ���� ����Ʈ�� OID�� �޾ƾ� �Ѵ�.
					ObjectRegistry & objectregister = pZone->getObjectRegistry();
					objectregister.registerObject(pEffect);
				
					// �� �� Ÿ�Ͽ��ٰ� ����Ʈ�� �߰��Ѵ�.
					pZone->addEffect(pEffect);	
					tile.addEffect(pEffect);
				}
			}

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			list<Creature*> cList;
			cList.push_back(pMonster);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);
		}
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(monster) " << endl;

	__END_CATCH
}

WideIceField g_WideIceField;
