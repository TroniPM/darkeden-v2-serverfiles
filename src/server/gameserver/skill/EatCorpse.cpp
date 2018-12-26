//////////////////////////////////////////////////////////////////////////////
// Filename    : EatCorpse.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EatCorpse.h"
#include "Effect.h"
#include "VampireCorpse.h"
#include "AlignmentManager.h"
#include "PCVampireInfo3.h"
#include "MonsterCorpse.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCRemoveCorpseHead.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� Ÿ�� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void EatCorpse::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	//Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		Item* pItem = NULL;
		//MonsterCorpse* pCorpse = NULL;

		bool bRangeCheck = verifyDistance(pVampire, X, Y, 1);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.hasItem()) pItem = tile.getItem();
		}

		bool bEatableCorpse = false;

		if ( pItem != NULL
		  && pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
		  && pItem->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			Assert( pCorpse != NULL );

			// ������������ �ƴϾ�� �Ѵ�.
			// ũ�������� Ʈ���� �ƴϾ�� �Ѵ�.
			// ������ �ƴϾ�� �Ѵ�.
			if ( !pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE)
			  && !pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE) 
			  && pCorpse->getMonsterType() != 482
			  && pCorpse->getMonsterType() != 650
			  && pCorpse->getTreasureCount() < 200 
			  && !pCorpse->isShrine() )
			{
				bEatableCorpse = true;
			}
		}

		if (bRangeCheck && bEatableCorpse )
		{
			Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
			Assert(pCorpse != NULL);

			// �����̾� ��ü�̰�, ������ Evil �̶�� ��ü�� �Դ� ���� �ƴ϶�, �������� ���� �Ѵ�.
			if (pCorpse->getItemType() == VAMPIRE_CORPSE) 
			{
				PCVampireInfo3 & rPCVampireInfo3 = dynamic_cast<VampireCorpse*>(pCorpse)->getVampireInfo();

				if (g_pAlignmentManager->getAlignmentType(rPCVampireInfo3.getAlignment()) < NEUTRAL) 
				{
					ItemNum_t ItemCount = pCorpse->getTreasureCount();

					// ��ü �ȿ� ����ִ� �������� ������ �� ����.
					for(int i = 0; i < ItemCount ; i++) 
					{
						Item* pTreasure = pCorpse->getTreasure();
						if (pTreasure != NULL) 
						{
							(pZone->getObjectRegistry()).registerObject(pTreasure);
							TPOINT pt = pZone->addItem(pTreasure, X, Y);

							if (pt.x != -1)
							{
								if (pTreasure->getItemClass() == Item::ITEM_CLASS_SKULL && pItem->getItemType() == MONSTER_CORPSE) 
								{
									GCRemoveCorpseHead _GCRemoveCorpseHead;
									_GCRemoveCorpseHead.setObjectID(pItem->getObjectID());
									pZone->broadcastPacket(pt.x, pt.y, &_GCRemoveCorpseHead);
								}
								//cout << "Begin Create" << endl;
								pTreasure->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
								//cout << "End Create" << endl;
							} 
							else 
							{
								SAFE_DELETE(pTreasure);
							}
						}
					}
				}
			}

			int RemainMP = max((int)pVampire->getHP(ATTR_MAX), (int)pVampire->getHP(ATTR_CURRENT) + 10);
			pVampire->setHP(RemainMP , ATTR_CURRENT);

			Range_t Range = 1;	// �׻� 1�̴�.

			ZoneCoord_t myX = pVampire->getX();
			ZoneCoord_t myY = pVampire->getY();

			_GCSkillToTileOK1.addShortData(MODIFY_CURRENT_HP , RemainMP);

			_GCSkillToTileOK1.setSkillType(SKILL_EAT_CORPSE);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setRange(Range);

			_GCSkillToTileOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK3.setSkillType(SKILL_EAT_CORPSE);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SKILL_EAT_CORPSE);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(Range);
			
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(SKILL_EAT_CORPSE);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(0);
			_GCSkillToTileOK5.setRange(Range);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			list<Creature*> cList;
			cList.push_back(pVampire);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// ��� �����۾��� ���� ������ ��ü�� �����Ѵ�.
			// ������� ��Ŷ�� ������.
			GCDeleteObject gcDO;
			gcDO.setObjectID(pCorpse->getObjectID());
			pZone->broadcastPacket(X, Y,  &gcDO);
			// ������ �����.
			pZone->deleteItem(pCorpse , X , Y);
			// ���ȿ��� ���������� �����͸� �������� �����Ƿ� �����͸� ���� ���� ��� �Ѵ�.
			SAFE_DELETE(pCorpse);
		}
		else
		{
			executeSkillFailException(pVampire, getSkillType());
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

EatCorpse g_EatCorpse;
