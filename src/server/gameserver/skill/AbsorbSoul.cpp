//////////////////////////////////////////////////////////////////////////////
// Filename    : AbsorbSoul.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "AbsorbSoul.h"

#include "item/Larva.h"
#include "item/Pupa.h"
#include "Corpse.h"
#include "OustersCorpse.h"
#include "PCOustersInfo3.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"
#include "Properties.h"
#include "GQuestManager.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillFailed1.h"

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺�ͽ� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
// ��ų�� ����� 2�� ������� �ȴ�.
// ��� ����⿡ ���� �� �ϳ� �ϰ�
// ���� ���� �� �ϳ�.
// �׷��� ó���� ���� üũ�ϴٰ� ������ ��쿡
// SkillFail ��Ŷ�� 2�� �����ش�.
// ///////////////////////////////////////////////////////////////////////////
void AbsorbSoul::execute(Ousters* pOusters, ObjectID_t TargetObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY )
	
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	// Ŭ���̾�Ʈ�� ���� �ɷ������� ���� ��Ŷ�� 2�� ������� �ȴ�.
	bool bClientLocked = InvenX != 255;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// ���� ��ü�� Creature �� ���� �ְ� Item �� ���� �ִ�.. 
		Item* pTargetItem = pZone->getItem(TargetObjectID);
		Creature* pTargetCreature = NULL;

		if ( pTargetItem == NULL )
		{
			pTargetCreature = pZone->getCreature(TargetObjectID);
		}

		if (pTargetCreature == NULL && pTargetItem == NULL)
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
			return;
		}
		// NPC�� ������ ���� ����.
		// �������� üũ. by sigi.2002.9.5
		// �� ���� �ִ� �� �� �� ����. by Sequoia.2003. 3. 20
		if ( pTargetCreature != NULL )
		{
			if ( pTargetCreature->isNPC()
				|| !canAttack( pOusters, pTargetCreature )
				|| !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)
			)
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}
			if ( pTargetCreature->isFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL) )
			{
				//
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
				return;
			}
		}
		else if ( pTargetItem != NULL )
		{
			if ( pTargetItem->getItemClass() != Item::ITEM_CLASS_CORPSE )
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}
			if ( pTargetItem->isFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL) )
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
				return;
			}
		}
		else 
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		//bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, 2);

		// Ÿ ������ ��ü�� ���� �� ��� (���� ��ü�� Creature �� ���)
		if ( pTargetCreature != NULL ) //&& bRangeCheck)
		{
			int targetLevel = 0;
			if (pTargetCreature->isSlayer())
			{
				Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pTargetCreature);
				targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
			}
			else if (pTargetCreature->isVampire()) 
			{
				Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pTargetCreature);
				targetLevel = pTargetVampire->getLevel();
			}
			else if (pTargetCreature->isOusters()) 
			{
				Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pTargetCreature);
				targetLevel = pTargetOusters->getLevel();
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				targetLevel = pMonster->getLevel();
			}
			
			// Ǫ�� ����⿡ ���� ó���� ���� �Ǿ�� �Ѵ�.
			// ��ٸ� Ǫ�ķ� �������� �Ѵ�
			// ���� �Լ��� ���� �ؿ��� ���� �� ����
			// SkillOK�� ������ ���� �����ۿ� ���� ó�� ��Ŷ�� ���� ������ �Ѵ�. ��!��!��!
			if ( InvenX != 255 ) makeLarvaToPupa( pOusters, targetLevel, ItemObjectID, InvenX, InvenY, TargetInvenX, TargetInvenY );

			// ���� ���� ����ġ��?? - ���߿� ���� ??
//			Exp_t Exp = computeCreatureExp(pTargetCreature, BLOODDRAIN_EXP);

			// ���� �ϰ� �Ǹ� ���� ����� EP�� �ö󰣴�.
			// �ö󰡴� ���� Creature Exp�� ����Ѵ�.
			MP_t CurrentMP = pOusters->getMP();
			MP_t MaxMP	   = pOusters->getMP(ATTR_MAX);
			MP_t HealPoint = 0;

			if ( CurrentMP < MaxMP )
			{
				HealPoint = computeCreatureExp(pTargetCreature, 60);
			}
			else
			{
				//MP_t ExtraMP = CurrentMP - MaxMP;
				float ExtraMP = (float)(CurrentMP - MaxMP) / (float)(MaxMP*2) * 100;
				float ftemp = 1.1 - ( (float)ExtraMP / ((float)ExtraMP+10.0) );
				int ratio = (int)(ftemp * 100);
//				cout << "AbsorbSoul : " << ratio << endl;
				HealPoint = computeCreatureExp(pTargetCreature, ratio);
			}

			MP_t NewMP     = min((int)MaxMP*3 , (int)CurrentMP + (int)HealPoint);

//			cout << NewMP << endl;
			// �ƿ콺������ MP�� �����Ѵ�.
			pOusters->setMP(NewMP);
//			cout << pOusters->getMP(ATTR_CURRENT) << endl;

            GCModifyInformation gcMI;
            gcMI.addShortData( MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT) );

//			cout << gcMI.toString() << endl;

			pOusters->getPlayer()->sendPacket( &gcMI );

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.addCListElement(TargetObjectID);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setX(TargetZoneX);
			_GCSkillToTileOK1.setY(TargetZoneY);
			_GCSkillToTileOK1.setRange(0);

			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.addCListElement(TargetObjectID);
			_GCSkillToTileOK5.setX(TargetZoneX);
			_GCSkillToTileOK5.setY(TargetZoneY);
			_GCSkillToTileOK5.setRange(0);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			if (pTargetCreature != NULL && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();

				if (pTargetPlayer != NULL) 
				{ 
					_GCSkillToTileOK2.setSkillType(getSkillType());
					_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
					_GCSkillToTileOK2.addCListElement(TargetObjectID);
					_GCSkillToTileOK2.setX(TargetZoneX);
					_GCSkillToTileOK2.setY(TargetZoneY);
					_GCSkillToTileOK2.setRange(0);
					_GCSkillToTileOK2.setDuration(0);

					pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToTileOK5 , cList);

			// ���� -_- �� ���� �Ŀ� �� �� ���ϰ� ���ƾ� �ǰ�
			// �� ���� �Ŀ� ��Ȱ �� �ǵ��� ���ƾ���
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL);

			pOusters->getGQuestManager()->blooddrain();
		}
		else if ( pTargetItem != NULL ) //&& bRangeCheck)
		{
			Corpse* pTargetCorpse = dynamic_cast<Corpse*>(pTargetItem);

			int targetLevel = 0;
			Exp_t Exp = 0;

			if ( pTargetCorpse->getItemType() == OUSTERS_CORPSE )
			{
				OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pTargetCorpse);
				Assert( pOustersCorpse != NULL );

				if ( pOustersCorpse->getOustersInfo().getName() == pOusters->getName() )
				{
					executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
					return;
				}
			}

			if ( pTargetCorpse->getItemType() == MONSTER_CORPSE 
				|| pTargetCorpse->getItemType() == SLAYER_CORPSE
				|| pTargetCorpse->getItemType() == VAMPIRE_CORPSE
				|| pTargetCorpse->getItemType() == OUSTERS_CORPSE
			)
			{
				targetLevel = (int)(pTargetCorpse->getLevel());
				Exp = (Exp_t)(pTargetCorpse->getExp());
			}
			else 
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}

			// Ǫ�� ����⿡ ���� ó���� ���� �Ǿ�� �Ѵ�.
			// ��ٸ� Ǫ�ķ� �������� �Ѵ�
			// ���� �Լ��� ���� �ؿ��� ���� �� ����
			// SkillOK�� ������ ���� �����ۿ� ���� ó�� ��Ŷ�� ���� ������ �Ѵ�. ��!��!��!
			if ( bClientLocked ) makeLarvaToPupa( pOusters, targetLevel, ItemObjectID, InvenX, InvenY, TargetInvenX, TargetInvenY );

			// ���� �ϰ� �Ǹ� ���� ����� SP�� �ö󰣴�.
			// �̰� ��� ���� ���߿� �� ���ߵɵ�
			// HealPoint == Exp �� -_-
//			MP_t HealPoint = Exp;
			MP_t CurrentMP = pOusters->getMP();
			MP_t MaxMP	   = pOusters->getMP(ATTR_MAX);
			MP_t HealPoint = 0;

			if ( CurrentMP < MaxMP )
			{
//				HealPoint = computeCreatureExp(pTargetCreature, 60);
				HealPoint = getPercentValue(Exp, 60);
			}
			else
			{
//				MP_t ExtraMP = CurrentMP - MaxMP;
				float ExtraMP = (float)(CurrentMP - MaxMP) / (float)(MaxMP*2) * 100;
				float ftemp = 1.1 - ( (float)ExtraMP / ((float)ExtraMP+10.0) );
				int ratio = (int)(ftemp * 100);
//				cout << "AbsorbSoul : " << ratio << endl;
//				HealPoint = computeCreatureExp(pTargetCreature, ratio);
				HealPoint = getPercentValue(Exp, ratio);
			}

			MP_t NewMP     = min((int)MaxMP*3 , (int)CurrentMP + (int)HealPoint);
//			cout << NewMP << endl;

			// �ƿ콺������ MP�� �����Ѵ�.
			pOusters->setMP(NewMP);
//			cout << pOusters->getMP(ATTR_CURRENT) << endl;

            GCModifyInformation gcMI;
            gcMI.addShortData( MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT) );

//			cout << gcMI.toString() << endl;

			pOusters->getPlayer()->sendPacket( &gcMI );

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.addCListElement(TargetObjectID);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setX(TargetZoneX);
			_GCSkillToTileOK1.setY(TargetZoneY);
			_GCSkillToTileOK1.setRange(0);

			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.addCListElement(TargetObjectID);
			_GCSkillToTileOK5.setX(TargetZoneX);
			_GCSkillToTileOK5.setY(TargetZoneY);
			_GCSkillToTileOK5.setRange(0);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			list<Creature *> cList;
			cList.push_back(pOusters);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToTileOK5 , cList);

			// ���� -_- �� ���� �Ŀ� �� �� ���ϰ� ���ƾ� ��
			pTargetItem->setFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL);

			pOusters->getGQuestManager()->blooddrain();
		}
		else 
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
		}
	} 
	catch (Throwable & t) 
	{
		executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH

}

void AbsorbSoul::makeLarvaToPupa(Ousters* pOusters, int TargetLevel, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY )
	throw()
{
	__BEGIN_TRY

	Inventory* pInventory = pOusters->getInventory();
	Assert(pInventory != NULL);
	Zone* pZone = pOusters->getZone();
	Assert(pZone != NULL );

	if ( InvenX >= pInventory->getWidth()
		|| InvenY >= pInventory->getHeight()
		|| TargetInvenX >= pInventory->getWidth()
		|| TargetInvenY >= pInventory->getHeight()
	   )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	Item* pLarva = pInventory->getItem( InvenX, InvenY );
	if ( pLarva == NULL
		|| pLarva->getItemClass() != Item::ITEM_CLASS_LARVA 
		|| pLarva->getObjectID() != ItemObjectID
	)
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	ItemType_t LarvaType = pLarva->getItemType();
	
//	int ratio = ( 100 * TargetLevel ) / ( (pOusters->getLevel() * 2) * ( pLarva->getItemType() + 1 ) );
//  Ȯ�� 4��� ���� 
	int ratio = ( 200 * TargetLevel ) / ( pOusters->getLevel() * ( pLarva->getItemType() + 1 ) );

	// Ǫ�� ����� ����
	if ( (rand()%100) > ratio )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	// Ȯ���� �Ѿ����� -_- Ǫ�ĸ� ������
	list<OptionType_t> optionNULL;
	Item* pPupa = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PUPA, pLarva->getItemType(), optionNULL );
			
	// ����� ������ �ٿ��ش�.
	// �� �Լ� �ȿ��� ����� ������ �ڵ������� �ϳ� �پ���, 
	// ���� 1���� ��ٿ��ٸ� �κ��丮 �� DB���� �����ǰ� �ȴ�.
	decreaseItemNum(pLarva, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

	// ������ Ǫ�ĸ� �����´�.
	Item* pPrevPupa = pInventory->getItem( TargetInvenX, TargetInvenY );

	GCSkillToInventoryOK1 gcSkillToInventoryOK1;

	if ( pPrevPupa != NULL )
	{
		// ������ ���� Ǫ�İ� �ִٸ�

		if ( !canStack( pPrevPupa, pPupa ) || pPrevPupa->getNum() >= ItemMaxStack[ (int)pPrevPupa->getItemClass() ] )
		{
			executeSkillFailException( pOusters, getSkillType() );
			return;
		}

		// ������ �ϳ� ������Ű�� �����Ѵ�.
		pPrevPupa->setNum( pPrevPupa->getNum() + 1 );
		pPrevPupa->save( pOusters->getName(), STORAGE_INVENTORY, 0, TargetInvenX, TargetInvenY );

		// ���κ��� decreaseItemNum() �Լ� �κп��� ������ ���ڸ� ���ҽ�Ű�Ƿ�,
		// ���⼭ �ٽ� �κ��丮�� ������ ���ڸ� ������Ų��.
		pInventory->increaseNum();

		// ������� Ǫ�Ĵ� ������ Ǫ�Ŀ� ���������Ƿ� �����Ѵ�.
		SAFE_DELETE( pPupa );

		gcSkillToInventoryOK1.setObjectID( pPrevPupa->getObjectID() );
	}
	else
	{
		ObjectRegistry& OR = pZone->getObjectRegistry();
		OR.registerObject( pPupa );

		// Ǫ�ĸ� Inventory �� ����ְ� DB���ٰ� �����Ѵ�.
		pInventory->addItem( TargetInvenX, TargetInvenY, pPupa );
		pPupa->create( pOusters->getName(), STORAGE_INVENTORY, 0, TargetInvenX, TargetInvenY );

		gcSkillToInventoryOK1.setObjectID( pPupa->getObjectID() );
	}

	gcSkillToInventoryOK1.setSkillType( getSkillType() );
	gcSkillToInventoryOK1.setItemType( LarvaType );
	gcSkillToInventoryOK1.setCEffectID( 0 );
	gcSkillToInventoryOK1.setX( TargetInvenX );
	gcSkillToInventoryOK1.setY( TargetInvenY );

	pOusters->getPlayer()->sendPacket( &gcSkillToInventoryOK1 );

	__END_CATCH
}

AbsorbSoul g_AbsorbSoul;
