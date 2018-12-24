//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRelicToObjectHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRelicToObject.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Corpse.h"
	#include "Relic.h"
	#include "Monster.h"
	#include "MonsterCorpse.h"
	#include "EffectPrecedence.h"
	#include "EffectIncreaseAttr.h"
	#include "EffectRelicTable.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectSlayerRelic.h"
	#include "EffectVampireRelic.h"
	#include "EffectKillTimer.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "ZoneUtil.h"
	#include "VariableManager.h"
	#include "SkillUtil.h"
	#include "RelicUtil.h"
	#include "ShrineInfoManager.h"
	#include "CastleShrineInfoManager.h"
	#include "StringPool.h"
	#include "LevelWarManager.h"
	#include "SiegeManager.h"
	#include "EffectCauseCriticalWounds.h"
	#include "Sweeper.h"

	#include "ctf/FlagManager.h"

	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCSay.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCDeleteInventoryItem.h"

	#include <stdio.h>

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRelicToObjectHandler::execute (CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

//	cout << "CGRelicToObject start" << endl;
//	cout << "���� ��Ŷ(������ ������Ʈ)" << pPacket->getItemObjectID()
//		 << "���� ��Ŷ(���� ������)"  << pPacket->getObjectID() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ������ �ش� ���������Կ� ������.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// ���� �����뿡 �̹� �� �� �ִ� ���
	// ���� �����뿡 Slayer������ �ְ� pItem�� Slayer������ ���
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
	if ( pPlayerCreature == NULL )
	{
		throw DisconnectException("CGRelicToObject : �̻��ؿ�");
		return;
	}

	// ���� ��� �ִ� ������ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 31 )
	{
		static hash_map<string, string> scripts;
		if ( scripts.empty() )
		{
			cout << "��ũ��Ʈ �ʱ�ȭ" << endl;
			scripts["Լ��ѷ"] = "лл��,����Զ��������������ҵĶ���.";
			scripts["����"] = "�Ͻ�ȥ�Ⱦ������˰�,��������.";
			scripts["����"] = "����...���ڵþ���.";
			scripts["��˹��̹"] = "������һ����.";
			scripts["·��˹"] = "����...ʵ����̫ʹ����.лл��!";
			scripts["ղķ˹"] = "���ڵþ���.����ׯ����.";
			scripts["��ɪ"] = "�Ͻ�ȥ�Ⱦ������˰�.";
			scripts["����"] = "����... ����û����!";
			scripts["����¬˹"] = "��~�þ���.";
			scripts["¬"] = "��~�þ���.";
			scripts["��˹��"] = "лл��!������һ����.";
			scripts["Ф"] = "�Ͻ�ȥ�Ⱦ������˰�.��������.";
			scripts["��¬˹"] = "����...̫������.���ڵþ���!";
			scripts["ղ��"] = "������һ����.";
			scripts["��Ŭ"] = "��������һ�����������ǵ�.";
		}

		Zone* pZone = pPlayerCreature->getZone();
		Monster* pMonster = dynamic_cast<Monster*>(pZone->getCreature(pPacket->getObjectID()));
		if ( pMonster == NULL )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			cout << "���Ͱ� �����ϴ�." << endl;

			return;
		}

		if (
			( pPlayerCreature->isSlayer() && pMonster->getMonsterType() != 793 ) ||
			( pPlayerCreature->isVampire() && pMonster->getMonsterType() != 794 ) ||
			( pPlayerCreature->isOusters() && pMonster->getMonsterType() != 795 ) ||
			scripts.find(pMonster->getName()) == scripts.end()
		   )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);

			cout << "�̻��� �����̰ų� ���� �̸��� Ʋ���ϴ�. : " << (int)pMonster->getMonsterType() << "," << pMonster->getName() << endl;

			return;
		}

		GCSay gcSay;
		gcSay.setObjectID( pMonster->getObjectID() );
		gcSay.setColor(255);
		gcSay.setMessage( scripts[pMonster->getName()] );

		pZone->broadcastPacket( pMonster->getX(), pMonster->getY(), &gcSay );
		EffectKillTimer* pEffect = new EffectKillTimer( pMonster, true );
		pMonster->setFlag( pEffect->getEffectClass() );
		pEffect->setDeadline(50);
		pMonster->addEffect( pEffect );

		pPlayerCreature->deleteItemFromExtraInventorySlot();
		
		GCDeleteInventoryItem gcDI;
		gcDI.setObjectID( pPacket->getItemObjectID() );
		pGamePlayer->sendPacket( &gcDI );

		pItem->destroy();
		SAFE_DELETE( pItem );

		return;
	}

	if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_COMMON_ITEM && pItem->getItemType() == 1 )
	{
		Zone* pZone = pPlayerCreature->getZone();
		Monster* pMonster = dynamic_cast<Monster*>(pZone->getCreature(pPacket->getObjectID()));
		if ( pMonster == NULL )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			cout << "���Ͱ� �����ϴ�." << endl;

			return;
		}

		if (pMonster->getMonsterType() != 74 && pMonster->getMonsterType() != 221)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);

			cout << "�̻��� �����̰ų� ���� �̸��� Ʋ���ϴ�. : " << (int)pMonster->getMonsterType() << "," << pMonster->getName() << endl;

			return;
		}

		GCSay gcSay;
		gcSay.setObjectID( pMonster->getObjectID() );
		gcSay.setColor(255);
		gcSay.setMessage( "���� �� ����ξ��� ������ �����Ǿ���.." );

		pZone->broadcastPacket( pMonster->getX(), pMonster->getY(), &gcSay );
		/*EffectCauseCriticalWounds* pEffect = dynamic_cast<EffectCauseCriticalWounds*>(pMonster);
		pEffect->setDeadline(0);*/
		pMonster->removeFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );
		pMonster->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
		pPlayerCreature->deleteItemFromExtraInventorySlot();
		
		GCDeleteInventoryItem gcDI;
		gcDI.setObjectID( pPacket->getItemObjectID() );
		pGamePlayer->sendPacket( &gcDI );

		pItem->destroy();
		SAFE_DELETE( pItem );

		return;
	}


	if (pItem==NULL
		|| (!isRelicItem( pItem )&&!pItem->isFlagItem() && !pItem->isSweeper()))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	if (pItem->getItemClass()==Item::ITEM_CLASS_RELIC)
	{
		executeRelic( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		executeBloodBible( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		executeCastleSymbol( pPacket, pPlayer );
	}
	else if ( pItem->isFlagItem() )
	{
		//cout << "��� �ű�!" << endl;
		executeFlag( pPacket, pPlayer );
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{
		executeSweeper( pPacket, pPlayer );
	}
	else
	{
		throw DisconnectException("�����Ѱ� ��� RelicToObject��������");
	}

#endif

	__END_DEBUG_EX __END_CATCH

}

void CGRelicToObjectHandler::executeRelic(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// ������ �ش� ���������Կ� ������.. 
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();

	// ���� �����뿡 �̹� �� �� �ִ� ���
	// ���� �����뿡 Slayer������ �ְ� pItem�� Slayer������ ���
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ���� ��� �ִ� ������ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	bool        Success   = false;

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// �׷� item�� ���ų�
	// ��ü�� �ƴϰų�
	// Monster��ü�� �ƴϸ� ���������밡 �ƴϴ�.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not RelicTable" << endl;
		return;
	}

	// ���� ������
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Ÿ�� �ȿ� �־�� �ȴ�.
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile" << endl;
		return;
	}

	// Relic ���� ���θ� üũ�Ѵ�.
	bool bPlayerHasSlayerRelic 	= pCreature->isFlag(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);
	bool bPlayerHasVampireRelic = pCreature->isFlag(Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC);
	bool bTableHasSlayerRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
	bool bTableHasVampireRelic 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
	bool bSlayerRelicTable 		= pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);
	bool bVampireRelicTable 	= pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

	// �̹� �� ������ �� �ְų�
	// Player�� �� ������ �� ���ų�
	// item�� ���� ���?
	// ������ �ƴϰų�
	if (bTableHasSlayerRelic && bTableHasVampireRelic
		|| !bPlayerHasSlayerRelic && !bPlayerHasVampireRelic
		|| pItem==NULL
		|| pItem->getItemClass() != Item::ITEM_CLASS_RELIC)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: Cannot add" << endl;
		return;
	}

	ItemType_t 		relicIndex 			= pItem->getItemType();

	// RelicInfo�� ��´�.
	const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));

	if ( pRelicInfo == NULL )
	{
		filelog( "relic.log", "no such relic index(%d)", relicIndex );

		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		return;
	}

	bool bSlayer = pCreature->isSlayer();
	bool bVampire = pCreature->isVampire();

	// itemObjectID�� �߸��Ǿ��ų�
	// ��� �ִ� �������� ���ų�
	// ���� �������̰ų�
	// �̹� ���� ������ ������ �ִٸ� ���� �� ����.
	if (pItem->getObjectID() != pPacket->getItemObjectID()
		|| bSlayer && bVampireRelicTable
		|| bVampire && bSlayerRelicTable
		|| bTableHasSlayerRelic && pRelicInfo->relicType==RELIC_TYPE_SLAYER
		|| bTableHasVampireRelic && pRelicInfo->relicType==RELIC_TYPE_VAMPIRE)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: Cannot Add2" << endl;
		return;
	}

	// �����̾��� ���� �������, �������λ��� �̸� �ȵǰ�
	// �����̾��� ���� ���Ż���, ��������̸� �ȵȴ�.
	if (bSlayer)
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		// ������̸� Ÿ�� ������ �Ұ����ϴ�.
		if (!pSlayer->hasRideMotorcycle()
			&& !pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
		{
			// Effect�� ���δ�.
			Success = true;
		}
	}
	else if (bVampire)
	{
		if (!pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
			&& !pCreature->isFlag(Effect::EFFECT_CLASS_FADE_OUT))
		{
			Success = true;
		}
	}

	// ���������뿡 ������ ���� �� �ִ� ���
	if (Success)
	{
		// Mouse���� �������� �����
		pPlayerCreature->deleteItemFromExtraInventorySlot();

		// ������ ���� �����뿡 �߰��Ѵ�.
		pCorpse->addTreasure( pItem );

/*		StringStream msg;
		msg << pPlayerCreature->getName() << " ���� ���� �����뿡 "
			<< "����(" << pRelicInfo->getName() << ")�� �־����ϴ�."; */

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_PUT_RELIC_TO_RELIC_TABLE ),
                        pPlayerCreature->getName().c_str(),
                        pRelicInfo->getName().c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg );
		g_pZoneGroupManager->broadcast( &gcSystemMessage );

		Effect::EffectClass effectClass;
		Effect::EffectClass effectClassTable;

		// Creature���� Effect�� �����ϰ�
		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			effectClass 		= Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			effectClassTable 	= Effect::EFFECT_CLASS_SLAYER_RELIC;
		}
		else
		{
			effectClass 		= Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			effectClassTable 	= Effect::EFFECT_CLASS_VAMPIRE_RELIC;
		}

		Effect* pEffect = pCreature->findEffect( effectClass );
		Assert(pEffect!=NULL);

		// Creature�� flag�� ����
		// GCRemoveEffect�� ������ �ȴ�.
		pEffect->unaffect();	
		pCreature->deleteEffect( effectClass );

		// ���� �����밡 Relic�� �����ٴ� Effect�� �ٿ��ش�.
		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			EffectSlayerRelic* pEffect = new EffectSlayerRelic(pCorpse);

			pCorpse->getEffectManager().addEffect( pEffect );
			pCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
			pEffect->affect(pCorpse);
		}
		else
		{
			EffectVampireRelic* pEffect = new EffectVampireRelic(pCorpse);

			pCorpse->getEffectManager().addEffect( pEffect );
			pCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
			pEffect->affect(pCorpse);
		}

		// ���������뿡 Effect�� ���ΰ� client�� �˸���.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pCorpse->getObjectID());
		gcAddEffect.setEffectID(effectClassTable);
		gcAddEffect.setDuration(65000);
		pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);

		// ���� ���Ҵٰ� �����ش�.
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID( pItem->getObjectID() );
		pPlayer->sendPacket(&gcDeleteObject);

		// RelicTable
		EffectRelicTable* pTableEffect = NULL;
		if (bSlayer)
		{
			// ������ ������ �����Ѵ�.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);

			// ����Ʈ�� ã�´�.
			Effect* pEffect = pCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE );
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectSlayerRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}
		else
		{
			// ������ ������ �����Ѵ�.
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);

			// ����Ʈ�� ã�´�.
			Effect* pEffect = pCorpse->getEffectManager().findEffect( Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE );
			Assert(pEffect!=NULL);

			pTableEffect = dynamic_cast<EffectVampireRelicTable*>(pEffect);
			Assert(pTableEffect!=NULL);
		}

		// ������ �ϳ� ����
		// �� ����(10��)�� ������ ���� �� ����.
		Timeval lockTime;
		getCurrentTime(lockTime);
		lockTime.tv_sec += 10;
		pTableEffect->setLockTime( lockTime );


		// �� ������ ��� ���� �Ǵ� ���
		if (bTableHasSlayerRelic && pRelicInfo->relicType==RELIC_TYPE_VAMPIRE
			|| bTableHasVampireRelic && pRelicInfo->relicType==RELIC_TYPE_SLAYER)

		{
			// ���� �����밡 ������ �ð� ����
			Timeval safeTime;
			getCurrentTime( safeTime );
			safeTime.tv_sec += g_pVariableManager->getCombatBonusTime()*60;

			// �¸� message �� �����ش�.
			GCSystemMessage gcSystemMessage;

			pTableEffect->setSafeTime( safeTime );

			if (bSlayer)
			{
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_SLAYER_WIN ) );
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
			}
			else
			{
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_VAMPIRE_WIN ) );
				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
			}

			// ������ ����Ǿ���.
			g_pCombatInfoManager->setCombat( false );

			// ��ü ����ڿ��� message�� ������.
			g_pZoneGroupManager->broadcast( &gcSystemMessage );

			g_pCombatInfoManager->computeModify();
		}
	}
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__
		
	__END_CATCH
}

void CGRelicToObjectHandler::executeBloodBible(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);


	// ���� �����뿡 �̹� �� �� �ִ� ���
	// ���� �����뿡 Slayer������ �ְ� pItem�� Slayer������ ���
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ���� ��� �ִ� ������ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// �׷� item�� ���ų�
	// ��ü�� �ƴϰų�
	// Monster��ü�� �ƴϰų�
	// ShrineGuard�� ShrineHoly�� �ƴϸ�.. ������ �ƴ���.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pTableItem->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD) &&
			!pTableItem->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ����
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Ÿ�� �ȿ� ���� �ʰų�
	// shrine���� ������ �ȵǾ� ������
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pShrineInfoManager->putBloodBible( pPlayerCreature, pItem, pCorpse ))
	{
		// putBloodBible �ȿ��� ó���Ѵ�.
	}	

#endif

	__END_CATCH
}

void CGRelicToObjectHandler::executeCastleSymbol(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// ���� �����뿡 �̹� �� �� �ִ� ���
	// ���� �����뿡 Slayer������ �ְ� pItem�� Slayer������ ���
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ���� ��� �ִ� ������ == Relic ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();


	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

//	cout << "executeCastleSymbol" << endl;

	// �׷� item�� ���ų�
	// ��ü�� �ƴϰų�
	// Monster��ü�� �ƴϰų�
	// ShrineGuard�� ShrineHoly�� �ƴϸ�.. ������ �ƴ���.
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pTableItem->isFlag(Effect::EFFECT_CLASS_CASTLE_SHRINE_GUARD) &&
			!pTableItem->isFlag(Effect::EFFECT_CLASS_CASTLE_SHRINE_HOLY))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ����
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Ÿ�� �ȿ� ���� �ʰų�
	// shrine���� ������ �ȵǾ� ������
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#ifndef __OLD_GUILD_WAR__
//	if ( pZone->getZoneID() == 1500 )
//	{
		cout << "siegeManager Call" << endl;
		SiegeManager::Instance().putItem( pPlayerCreature, pCorpse, pItem );
		return;
//	}
#else
	if (g_pCastleShrineInfoManager->putCastleSymbol( pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol �ȿ��� ó���Ѵ�.
	}
#endif

#endif

	__END_CATCH
}
	
void CGRelicToObjectHandler::executeFlag(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	if ( !g_pFlagManager->hasFlagWar() ) return;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	// ���� �����뿡 �̹� �� �� �ִ� ���
	// ���� �����뿡 Slayer������ �ְ� pItem�� Slayer������ ���
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	// ���� ��� �ִ� ������ == Flag ?
	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	// �׷� item�� ��?ų?
	// ��ü�� �ƴϰų�
	// Monster��ü�� �ƴϰų�
	// ��밡 �ƴϸ�
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !g_pFlagManager->isFlagPole( dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ����
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Ÿ�� �ȿ� ���� �ʰų�
	// shrine���� ������ �ȵǾ� ������
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2)
		|| !pCorpse->isShrine())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (g_pFlagManager->putFlag( pPlayerCreature, pItem, pCorpse ))
	{
		// putCastleSymbol �ȿ��� ó���Ѵ�.
		//cout << "��� �Ⱦ�����~" << endl;
	}	
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#endif

	__END_CATCH
}

void CGRelicToObjectHandler::executeSweeper(CGRelicToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature 	= pGamePlayer->getCreature();
	Zone*	 	pZone		= pCreature->getZone();
	Assert(pZone!=NULL);

	LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();
	Assert(pLevelWarManager!=NULL);

	if ( !pLevelWarManager->hasWar() ) return;

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

	InventorySlot* 	pExtraInventorySlot = pPlayerCreature->getExtraInventorySlot();
	Item*   		pItem   			= pExtraInventorySlot->getItem();

	Item* pTableItem = pZone->getItem( pPacket->getObjectID() );

	const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

	// �׷� item�� ���ų�
	// ��ü�� �ƴϰų�
	// Monster��ü�� �ƴϰų�
	// ��밡 �ƴϸ�
	if (pTableItem==NULL 
		|| pTableItem->getItemClass()!=Item::ITEM_CLASS_CORPSE
		|| pTableItem->getItemType()!=MONSTER_CORPSE
		|| !pLevelWarManager->isSafe( dynamic_cast<MonsterCorpse*>(pTableItem) ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not Shrine" << endl;
		return;
	}

	// ����
	MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pTableItem);
	Assert(pCorpse!=NULL);

	// 2Ÿ�� �ȿ� ���� �ʰų�
	// shrine���� ������ �ȵǾ� ������
	if (!verifyDistance(pCreature, pCorpse->getX(), pCorpse->getY(), 2))
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

	if (pLevelWarManager->putSweeper( pPlayerCreature, pItem, pCorpse ))
	{
		// Sweeper �� �Ⱦ����� ������ �ִ� �� �����ش�
		pPlayerCreature->deleteItemFromExtraInventorySlot();
		GCDeleteInventoryItem gcDeleteInventoryItem;
		gcDeleteInventoryItem.setObjectID( pPacket->getItemObjectID() );
		pPlayerCreature->getPlayer()->sendPacket( &gcDeleteInventoryItem );
		Effect* pEffect = pPlayerCreature->findEffect( Effect::EFFECT_CLASS_HAS_SWEEPER );

		if (pEffect != NULL)
		{
			pEffect->setDeadline(0);
		}

		// �Ⱦ��� �� ���� �ý��� �޼����� �ѷ��ش�
		char race[15];
		if ( pCreature->isSlayer() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
		}
		else if ( pCreature->isVampire() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
		}
		else if ( pCreature->isOusters() )
		{
			sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
		}
		else
		{
			Assert(false);
		}

		char msg[100];

		sprintf( msg , g_pStringPool->c_str( STRID_PUT_SWEEPER ) ,
							pCreature->getName().c_str(),
							race,
							pSweeperInfo->getName().c_str()
							);
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg );
		pZone->broadcastPacket( &gcSystemMessage );
	}	
	else
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);

		//cout << "return: not in 2 tile or not shrine" << endl;
		return;
	}

#endif

	__END_CATCH
}
