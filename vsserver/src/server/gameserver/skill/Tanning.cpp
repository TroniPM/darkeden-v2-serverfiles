//////////////////////////////////////////////////////////////////////////////
// Filename    : SnakeCombo.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Tanning.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "PCManager.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert.h"
#include "PlayerCreature.h"
#include "Timeval.h"
#include "Player.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "ZoneUtil.h"
#include "InstantDungeonMonster.h"
#include "VariableManager.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemGradeManager.h"
#include "ItemFactoryManager.h"
#include "PacketUtil.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCCreateItem.h"

#include "SimpleMeleeSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Tanning::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Player* pPlayer = pSlayer->getPlayer();
	Zone* pZone = pSlayer->getZone();
	Assert(pPlayer != NULL);
	Assert(pZone != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pSlayer);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();

	try 
	{
	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC()
			|| pTargetCreature->isDead()
			|| !pTargetCreature->isMonster()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA))
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Item* pMasterItem = pInventory->findItem(Item::ITEM_CLASS_COMMON_ITEM, 16);

		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bMaster	 = false;

		if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			Assert( pTargetMonster != NULL );
			if(pTargetMonster->getMonsterType() == 908){
			bMaster = true;
			}
		}

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pSlayer->getX();
		ZoneCoord_t myY     = pSlayer->getY();

		if (bRangeCheck && bMaster && pMasterItem != NULL)
		{

				EffectKillTimer* pEffect = new EffectKillTimer( pTargetCreature, true );
				pTargetCreature->setFlag( pEffect->getEffectClass() );
				pEffect->setDeadline(50);
				pTargetCreature->addEffect( pEffect );

				if(pMasterItem->getNum() > 1){ 

				pMasterItem->setNum(pMasterItem->getNum() - 1); // 아이?邦?갯수를 하나 줄인다.

				char pField[80];
				sprintf(pField, "Num=%d", pMasterItem->getNum());
				pMasterItem->tinysave(pField);

				// 클라이언트에 아이템을 삭제시켜줘야 한다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);

				CoordInven_t X = -1, Y;
				pPC->getInventory()->findItemOID( pMasterItem->getObjectID(), X, Y );
				Assert( X != -1 );

				GCCreateItem gcCreateItem;
				makeGCCreateItem( &gcCreateItem, pMasterItem, X, Y );
				pPlayer->sendPacket(&gcCreateItem);

				}else{

				// 서버 자체에서도 없애준다. 
				pInventory->deleteItem(pMasterItem->getObjectID());
	
				// 안전하게 아예 없앤다.
				pMasterItem->destroy();

				// 클라이언트에 아이템을 삭제시킨다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);
				}

				Item* pItem1 = NULL;
				TreasureList* pTreasureList = NULL;

				MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(66);

			if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
			{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getSlayerTreasureList();
			}

		if ( pTreasureList != NULL )
		{
			const list<Treasure*>& treasures = pTreasureList->getTreasures();

			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;
			for (; itr != treasures.end(); itr++)
			{
				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
					if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000){
					pItem1->setOptionType2( it.OptionType2 );
					}
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
					pItem1->setNum(1);
					if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
					int HeroOptionSetting = rand()%13;
					int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
					int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
					if(HeroOptionAttrSetting != 0 ){
					pItem1->setHeroOption( HeroOption+1 );
					pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
					}
				}

					Assert(pItem1 != NULL);
				}
			}
		}

		if(pItem1 != NULL)
		{
				(pZone->getObjectRegistry()).registerObject(pItem1);

				TPOINT p = pZone->addItem(pItem1, pTargetCreature->getX(), pTargetCreature->getY());

				if (p.x != -1)
				{
					pItem1->create("", STORAGE_ZONE, pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
					if ( pItem1 != NULL && pItem1->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName , "%4d%3d%3d", pZone->getZoneID(), p.x, p.y);
						remainTraceLog( pItem1, "LairMaster", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem1, zoneName, ITL_GET , ITLD_EVENTNPC, pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem1);
				}


		}

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
		
			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
		
			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			
			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pSlayer);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

	}
	else 
	{
		executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
	}

	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Tanning::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot * pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Player* pPlayer = pVampire->getPlayer();
	Zone* pZone = pVampire->getZone();
	Assert(pPlayer != NULL);
	Assert(pZone != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pVampire);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();

	try 
	{
	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC()
			|| pTargetCreature->isDead()
			|| !pTargetCreature->isMonster()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA))
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Item* pMasterItem = pInventory->findItem(Item::ITEM_CLASS_COMMON_ITEM, 16);

		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bMaster	 = false;

		if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			Assert( pTargetMonster != NULL );
			if(pTargetMonster->getMonsterType() == 908){
			bMaster = true;
			}
		}

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pVampire->getX();
		ZoneCoord_t myY     = pVampire->getY();

		if (bRangeCheck && bMaster && pMasterItem != NULL)
		{

				EffectKillTimer* pEffect = new EffectKillTimer( pTargetCreature, true );
				pTargetCreature->setFlag( pEffect->getEffectClass() );
				pEffect->setDeadline(50);
				pTargetCreature->addEffect( pEffect );

				if(pMasterItem->getNum() > 1){ 

				pMasterItem->setNum(pMasterItem->getNum() - 1); // 아이?邦?갯수를 하나 줄인다.

				char pField[80];
				sprintf(pField, "Num=%d", pMasterItem->getNum());
				pMasterItem->tinysave(pField);

				// 클라이언트에 아이템을 삭제시켜줘야 한다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);

				CoordInven_t X = -1, Y;
				pPC->getInventory()->findItemOID( pMasterItem->getObjectID(), X, Y );
				Assert( X != -1 );

				GCCreateItem gcCreateItem;
				makeGCCreateItem( &gcCreateItem, pMasterItem, X, Y );
				pPlayer->sendPacket(&gcCreateItem);

				}else{

				// 서버 자체에서도 없애준다. 
				pInventory->deleteItem(pMasterItem->getObjectID());
	
				// 안전하게 아예 없앤다.
				pMasterItem->destroy();

				// 클라이언트에 아이템을 삭제시킨다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);
				}

				Item* pItem1 = NULL;
				TreasureList* pTreasureList = NULL;

				MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(66);

			if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
			{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getVampireTreasureList();
			}

		if ( pTreasureList != NULL )
		{
			const list<Treasure*>& treasures = pTreasureList->getTreasures();

			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;
			for (; itr != treasures.end(); itr++)
			{
				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
					if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000){
					pItem1->setOptionType2( it.OptionType2 );
					}
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
					pItem1->setNum(1);
					if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
					int HeroOptionSetting = rand()%13;
					int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
					int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
					if(HeroOptionAttrSetting != 0 ){
					pItem1->setHeroOption( HeroOption+1 );
					pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
					}
				}

					Assert(pItem1 != NULL);
				}
			}
		}

		if(pItem1 != NULL)
		{
				(pZone->getObjectRegistry()).registerObject(pItem1);

				TPOINT p = pZone->addItem(pItem1, pTargetCreature->getX(), pTargetCreature->getY());

				if (p.x != -1)
				{
					pItem1->create("", STORAGE_ZONE, pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
					if ( pItem1 != NULL && pItem1->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName , "%4d%3d%3d", pZone->getZoneID(), p.x, p.y);
						remainTraceLog( pItem1, "LairMaster", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem1, zoneName, ITL_GET , ITLD_EVENTNPC, pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem1);
				}


		}

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
		
			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
		
			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			
			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

	}
	else 
	{
		executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
	}

	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Tanning::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Player* pPlayer = pOusters->getPlayer();
	Zone* pZone = pOusters->getZone();
	Assert(pPlayer != NULL);
	Assert(pZone != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pOusters);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();

	try 
	{
	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC()
			|| pTargetCreature->isDead()
			|| !pTargetCreature->isMonster()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA))
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Item* pMasterItem = pInventory->findItem(Item::ITEM_CLASS_COMMON_ITEM, 16);

		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bMaster	 = false;

		if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			Assert( pTargetMonster != NULL );
			if(pTargetMonster->getMonsterType() == 908){
			bMaster = true;
			}
		}

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pOusters->getX();
		ZoneCoord_t myY     = pOusters->getY();

		if (bRangeCheck && bMaster && pMasterItem != NULL)
		{

				EffectKillTimer* pEffect = new EffectKillTimer( pTargetCreature, true );
				pTargetCreature->setFlag( pEffect->getEffectClass() );
				pEffect->setDeadline(50);
				pTargetCreature->addEffect( pEffect );

				if(pMasterItem->getNum() > 1){ 

				pMasterItem->setNum(pMasterItem->getNum() - 1); // 아이?邦?갯수를 하나 줄인다.

				char pField[80];
				sprintf(pField, "Num=%d", pMasterItem->getNum());
				pMasterItem->tinysave(pField);

				// 클라이언트에 아이템을 삭제시켜줘야 한다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);

				CoordInven_t X = -1, Y;
				pPC->getInventory()->findItemOID( pMasterItem->getObjectID(), X, Y );
				Assert( X != -1 );

				GCCreateItem gcCreateItem;
				makeGCCreateItem( &gcCreateItem, pMasterItem, X, Y );
				pPlayer->sendPacket(&gcCreateItem);

				}else{

				// 서버 자체에서도 없애준다. 
				pInventory->deleteItem(pMasterItem->getObjectID());
	
				// 안전하게 아예 없앤다.
				pMasterItem->destroy();

				// 클라이언트에 아이템을 삭제시킨다.
				GCDeleteInventoryItem gcDeleteInventoryItem;
				gcDeleteInventoryItem.setObjectID(pMasterItem->getObjectID());
				pPlayer->sendPacket(&gcDeleteInventoryItem);
				}

				Item* pItem1 = NULL;
				TreasureList* pTreasureList = NULL;

				MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(66);

			if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
			{
					pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOustersTreasureList();
			}

		if ( pTreasureList != NULL )
		{
			const list<Treasure*>& treasures = pTreasureList->getTreasures();

			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;
			for (; itr != treasures.end(); itr++)
			{
				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
					if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000){
					pItem1->setOptionType2( it.OptionType2 );
					}
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
					pItem1->setNum(1);
					if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
					int HeroOptionSetting = rand()%13;
					int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
					int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
					if(HeroOptionAttrSetting != 0 ){
					pItem1->setHeroOption( HeroOption+1 );
					pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
					}
				}

					Assert(pItem1 != NULL);
				}
			}
		}

		if(pItem1 != NULL)
		{
				(pZone->getObjectRegistry()).registerObject(pItem1);

				TPOINT p = pZone->addItem(pItem1, pTargetCreature->getX(), pTargetCreature->getY());

				if (p.x != -1)
				{
					pItem1->create("", STORAGE_ZONE, pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
					if ( pItem1 != NULL && pItem1->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName , "%4d%3d%3d", pZone->getZoneID(), p.x, p.y);
						remainTraceLog( pItem1, "LairMaster", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem1, zoneName, ITL_GET , ITLD_EVENTNPC, pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem1);
				}


		}

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
		
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
		
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			
			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

	}
	else 
	{
		executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
	}

	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}
	__END_CATCH
}

Tanning g_Tanning;
