#include "RelicUtil.h"
#include "Zone.h"
#include "Creature.h"
#include "Corpse.h"
#include "Effect.h"
#include "BloodBible.h"
#include "CastleSymbol.h"
#include "Inventory.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "CombatInfoManager.h"
#include "CastleInfoManager.h"
#include "HolyLandManager.h"
#include "war/DragonEyeManager.h"
#include "StringPool.h"

#include "EffectHasVampireRelic.h"
#include "EffectHasSlayerRelic.h"
#include "EffectHasBloodBible.h"
#include "EffectHasCastleSymbol.h"
#include "EffectRelicPosition.h"
#include "EffectRelicLock.h"
#include "EffectDragonEye.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteInventoryItem.h"

#include <stdio.h>

void
sendBloodBibleEffect( Object* pObject, Effect::EffectClass EClass )
	
{
	__BEGIN_TRY

	Assert(pObject!=NULL);

	switch (pObject->getObjectClass())
	{
		case Object::OBJECT_CLASS_CREATURE :
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature!=NULL);

			GCAddEffect gcAddEffect;
			gcAddEffect.setEffectID( EClass );
			gcAddEffect.setObjectID( pCreature->getObjectID() );

			pCreature->getZone()->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
		}
		break;

		case Object::OBJECT_CLASS_ITEM :
		{
			Item* pItem = dynamic_cast<Item*>(pObject);
			Assert(pItem!=NULL);

			if ( pItem->getItemClass() == Item::ITEM_CLASS_CORPSE )
			{
				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
				Assert(pCorpse!=NULL);

				GCAddEffect gcAddEffect;
				gcAddEffect.setEffectID( EClass );
				gcAddEffect.setObjectID( pCorpse->getObjectID() );

				pCorpse->getZone()->broadcastPacket( pCorpse->getX(), pCorpse->getY(), &gcAddEffect );
			}
		}
		break;

		default :
			return;
	}

	__END_CATCH
}


// 	Ƽ�𸣳��� 
// 			�����̾� ( 37, 163 ) 
//			�����̾� ( 193, 46 ) 
//
//	�ƴ��� ���� ��<�����̾�> ( 239, 134) 
//	�ƴ��� ���� ��<�����̾�> ( 27, 133 ) 
void
sendHolyLandWarpEffect( Creature* pCreature ) 
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);

	bool bSend = false;
	Distance_t limitDist = 15;
	Effect::EffectClass EClass;

	ZoneID_t zoneID = pCreature->getZoneID();

	ZoneCoord_t x, y;

	if (pCreature->isSlayer()) 
	{
		const int maxHolyLandWarpSlayer = 1;
		static ZONE_COORD HolyLandWarpSlayer[ maxHolyLandWarpSlayer ] = 
		{
			ZONE_COORD( 53, 37, 163 ), 	// Ƽ�� ����
//			ZONE_COORD( 73, 27, 133 )	// �ƴ��� ���� ����
		};

		for (int i=0; i<maxHolyLandWarpSlayer; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpSlayer[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_SLAYER;
	} 
	else if (pCreature->isVampire())
	{
		const int maxHolyLandWarpVampire = 1;
		static ZONE_COORD HolyLandWarpVampire[ maxHolyLandWarpVampire ] = 
		{
			ZONE_COORD( 53, 193, 46 ),	// Ƽ�� ����
//			ZONE_COORD( 71, 239, 134 )	// �ƴ��� ���� ����
		};

		for (int i=0; i<maxHolyLandWarpVampire; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpVampire[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_VAMPIRE;
	}
	else if (pCreature->isOusters())
	{
		// ���� ������ ����� �� ~_~
		// �ƿ콺����� �ƴ��� ���� ��� ������ ��.,��
		const int maxHolyLandWarpOusters = 1;
		static ZONE_COORD HolyLandWarpOusters[ maxHolyLandWarpOusters ] = 
		{
			ZONE_COORD( 53, 160, 170 ),	// Ƽ�� ����
//			ZONE_COORD( 72, 129, 112 )	// �ƴ��� ���� �߾�
		};

		for (int i=0; i<maxHolyLandWarpOusters; i++)
		{
			const ZONE_COORD& zoneCoord = HolyLandWarpOusters[i];
			x = zoneCoord.x;
			y = zoneCoord.y;

			if (zoneID == zoneCoord.id
				&& pCreature->getDistance(x, y) < limitDist)
			{
				bSend = true;
				break;
			}
		}

		EClass = Effect::EFFECT_CLASS_WARP_HOLY_LAND_OUSTERS;
	}

	if (bSend) 
	{
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setEffectID( EClass );
		gcAddEffectToTile.setObjectID( pCreature->getObjectID() );
		gcAddEffectToTile.setXY( x, y );
		gcAddEffectToTile.setDuration( 21 );

		pCreature->getZone()->broadcastPacket( x, y, &gcAddEffectToTile );
	}

	__END_CATCH
}

bool addEffectRelicPosition( Item* pItem, ZoneID_t zoneID, TPOINT pt )
	
{
	__BEGIN_TRY

	if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
	{
		EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
		//pPosition->setNextTime(10);     // 1�� �� �޼��� �Ѹ���.
		pPosition->setTick( 1*60*10 );  // 1�и��� �ѹ��� �˸���.
		pPosition->setZoneID( zoneID );
		pPosition->setX( pt.x );
		pPosition->setY( pt.y );
		pPosition->setPart( pItem->getItemType() );
		pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
		pItem->getEffectManager().addEffect( pPosition );
		pPosition->affect();

		return true;
	}

	return false;

	__END_CATCH
}

bool
deleteEffectRelicPosition( Item* pItem )
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);

	// EffectRelicPosition �����Ѵ�.
	// ���� �����뿡 �پ��ִ� Effect�� �����Ѵ�.
	if (pItem->isFlag(Effect::EFFECT_CLASS_RELIC_POSITION))
	{
		Effect* pPositionEffect = pItem->getEffectManager().findEffect(Effect::EFFECT_CLASS_RELIC_POSITION);
		Assert(pPositionEffect != NULL);

		pPositionEffect->unaffect();
		pItem->removeFlag(Effect::EFFECT_CLASS_RELIC_POSITION);
		pItem->getEffectManager().deleteEffect(Effect::EFFECT_CLASS_RELIC_POSITION);

		return true;
	}

	return false;

	__END_CATCH
}

// Corpse���� pItem�� ���õ� Effect�� �����ش�.
bool
deleteRelicEffect(Corpse* pCorpse, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pCorpse!=NULL);
	Assert(pItem!=NULL);

	Effect::EffectClass EClass;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_RELIC :
		{
			const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );
			Assert( pRelicInfo != NULL );

			if ( pRelicInfo->relicType == RELIC_TYPE_SLAYER )
				EClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			else if ( pRelicInfo->relicType == RELIC_TYPE_VAMPIRE )
				EClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			else
				throw Error("�߸��� Relic Item Type �Դϴ�.");
		}
		break;

		case Item::ITEM_CLASS_BLOOD_BIBLE :
			EClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
			break;

		case Item::ITEM_CLASS_CASTLE_SYMBOL :
			EClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
			break;

		case Item::ITEM_CLASS_WAR_ITEM :
			EClass = Effect::EFFECT_CLASS_DRAGON_EYE;

		default :
			return false;
	}

	pCorpse->removeFlag( EClass );

	EffectManager& effectManager = pCorpse->getEffectManager();
	Effect* pEffect = effectManager.findEffect( EClass );
	if (pEffect!=NULL)
	{
		pEffect->unaffect();
		effectManager.deleteEffect( EClass );
	}

	return true;

	__END_CATCH
}

void
saveItemInCorpse(Item* pItem, Corpse* pCorpse)
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pCorpse!=NULL);

	if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE
		|| pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL
		|| pItem->isFlagItem() 
		|| pItem->getItemClass()==Item::ITEM_CLASS_SWEEPER)
	{
		Zone* pZone = pCorpse->getZone();
		Assert(pZone!=NULL);

		char pField[80];

		pZone->registerObject( pItem );

		sprintf(pField, "ObjectID = %lu, OwnerID='%d', Storage=%d, StorageID=%lu", 
						pItem->getObjectID(), (int)pZone->getZoneID(), (int)STORAGE_CORPSE, pCorpse->getObjectID());

		pItem->tinysave( pField );
	}

	__END_CATCH
}

bool isRelicItem(const Item* pItem)
{
	if (pItem!=NULL)
	{
		Item::ItemClass IClass = pItem->getItemClass();

		return isRelicItem( IClass );
	}

	return false;
}

bool isRelicItem(Item::ItemClass IClass)
{
	if (IClass==Item::ITEM_CLASS_RELIC
		|| IClass==Item::ITEM_CLASS_BLOOD_BIBLE
		|| IClass==Item::ITEM_CLASS_CASTLE_SYMBOL
		|| IClass==Item::ITEM_CLASS_WAR_ITEM
		)
	{
		return true;
	}

	return false;
}

// Zone�� �ִ� pCorpse�� pItem�� ������ �ִ�.
bool
addHasRelicEffect(Zone* pZone, Corpse* pCorpse, Item* pItem)
	
{
	__BEGIN_TRY
		
	if (pZone==NULL) return false;
	
	Assert(pCorpse!=NULL);
	Assert(pItem!=NULL);

	EffectHasRelic* pRelicEffect = NULL;

	// ������ ������ ������ �ִٴ� ǥ��
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLOOD_BIBLE :
		{
			pRelicEffect = new EffectHasBloodBible( pCorpse );
		}
		break;

		case Item::ITEM_CLASS_CASTLE_SYMBOL :
		{
			pRelicEffect = new EffectHasCastleSymbol( pCorpse );
		}
		break;

		default :
			return false;
	}

	pRelicEffect->setZone( pZone );
	pRelicEffect->setXY( pCorpse->getX(), pCorpse->getY() );
	//pRelicEffect->setNextTime( 1*10 );   // 1�� ��
	pRelicEffect->setTick( 1*60*10 );    // 1�и��� �޼��� ���
	pRelicEffect->setPart( pItem->getItemType() );

	pRelicEffect->affect();

	EffectManager& effectManager = pCorpse->getEffectManager();
	pCorpse->setFlag( pRelicEffect->getEffectClass() );
	effectManager.addEffect( pRelicEffect );

	// ����Ʈ�� �ٿ��ֶ�� �Ѵ�.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCorpse->getObjectID() );
	gcAddEffect.setEffectID( pRelicEffect->getSendEffectClass() );
	gcAddEffect.setDuration( 65000 );
	pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);

	return true;

	__END_CATCH
}


bool deleteRelicEffect(Creature* pCreature, Item* pItem) 
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pCreature!=NULL);

	Effect::EffectClass effectClass;

	if (pItem->getItemClass()==Item::ITEM_CLASS_RELIC)
	{
		const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );
		Assert( pRelicInfo != NULL );

		if ( pRelicInfo->relicType == RELIC_TYPE_SLAYER )
			effectClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
		else if ( pRelicInfo->relicType == RELIC_TYPE_VAMPIRE )
			effectClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
		else
			throw Error("�߸��� Relic Item Type �Դϴ�.");
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
	}
	else if (pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
	}
	else if ( pItem->getItemClass() == Item::ITEM_CLASS_WAR_ITEM )
	{
		effectClass = Effect::EFFECT_CLASS_DRAGON_EYE;
	}
	else
	{
		return false;
	}

	// has relic ����Ʈ�� ã�Ƽ� ����Ʈ�� �����ش�.
	Effect* pEffect = pCreature->findEffect( effectClass );
	if ( pEffect != NULL )
	{
		pCreature->removeFlag( effectClass );
		pEffect->unaffect();
		pCreature->deleteEffect( effectClass );

		return true;
	}

	return false;

	__END_CATCH
}

bool
addRelicEffect(Creature* pCreature, Item* pItem)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(pItem!=NULL);

	// ������ �����ٴ� ����Ʈ�� ���δ�.
	Effect::EffectClass effectClass;
	Effect::EffectClass effectClassSend;

	Item::ItemClass itemclass 	= pItem->getItemClass();
	ItemType_t		itemtype	= pItem->getItemType();

	if (itemclass == Item::ITEM_CLASS_RELIC)
	{
		const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(itemtype));

		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			effectClassSend = effectClass = Effect::EFFECT_CLASS_HAS_SLAYER_RELIC;
			EffectHasRelic* pEffect = new EffectHasSlayerRelic(pCreature);
			//pEffect->setNextTime( 1*10 );	// 10�� ��
			pEffect->setTick( 1*60*10 );	// 1�и��� �޼��� ���
			pCreature->addEffect( pEffect );
			pEffect->affect();
		}
		else
		{
			effectClassSend = effectClass = Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC;
			EffectHasRelic* pEffect = new EffectHasVampireRelic(pCreature);
			//pEffect->setNextTime( 1*10 );	// 10�� ��
			pEffect->setTick( 1*60*10 );	// 1�и��� �޼��� ���
			pCreature->addEffect( pEffect );
			pEffect->affect();
		}
	}
	else if (itemclass == Item::ITEM_CLASS_BLOOD_BIBLE)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
		effectClassSend = (Effect::EffectClass)((int)Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE + itemtype);
		EffectHasRelic* pEffect = new EffectHasBloodBible(pCreature);
		//pEffect->setNextTime( 1*10 );	// 10�� ��
		pEffect->setTick( 1*60*10 );	// 1�и��� �޼��� ���
		pEffect->setPart( itemtype );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else if (itemclass == Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		effectClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
		effectClassSend = (Effect::EffectClass)((int)Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL + itemtype);
		EffectHasRelic* pEffect = new EffectHasCastleSymbol(pCreature);
		//pEffect->setNextTime( 1*10 );	// 10�� ��
		pEffect->setTick( 1*60*10 );	// 1�и��� �޼��� ���
		pEffect->setPart( itemtype );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else if ( itemclass == Item::ITEM_CLASS_WAR_ITEM )
	{
		effectClass = Effect::EFFECT_CLASS_DRAGON_EYE;
		effectClassSend = effectClass;
		EffectHasRelic* pEffect = new EffectDragonEye(pCreature);
		EffectDragonEye* pDragonEyeEffect = dynamic_cast<EffectDragonEye*>(pEffect);
		pDragonEyeEffect->setItemID( pItem->getItemID() );
		pEffect->setTick( 999999 );
		pEffect->setPart( 0 );
		pCreature->setFlag( effectClass );
		pCreature->addEffect( pEffect );
		pEffect->affect();
	}
	else
	{
		return false;
	}

	pCreature->setFlag( effectClass );

	// Effect�ٿ��ٰ� �˷��ش�.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCreature->getObjectID() );
	gcAddEffect.setEffectID( effectClassSend );
	gcAddEffect.setDuration( 65000 );
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	return true;

	__END_CATCH
}


bool dropRelicToZone(PlayerCreature* pPC, Item* pItem)
	
{
	Zone* pZone = pPC->getZone();
	Assert(pZone!=NULL);

	// �ϴ� �������� �ٴڿ� ����߸���.
	// ��ü�� ��ĥ ���� �����Ƿ�.. ĳ���Ͱ� ���� ���� ����߸���.
	TPOINT pt = pZone->addItem( pItem, pPC->getX(), pPC->getY(), false );

	if ( pt.x != -1 )           // ����߸��µ� �����ߴٸ�
	{
		char pField[80];
		sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
		pItem->tinysave(pField);

		// �κ��丮���� ����.
		//pInventory->deleteItem( pItem->getObjectID() );
		deleteRelicEffect( pPC, pItem );

		// Relic�� ������ ���� ������ ƴƴ�� �˷��ֵ��� �Ѵ�.
/*		if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
		{
			EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
			//pPosition->setNextTime(10);     // 1�� �� �޼��� �Ѹ���.
			pPosition->setTick( 1*60*10 );  // 1�и��� �ѹ��� �˸���.
			pPosition->setZoneID( pZone->getZoneID() );
			pPosition->setX( pt.x );
			pPosition->setY( pt.y );
			pPosition->setPart( pItem->getItemType() );
			pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
			pItem->getEffectManager().addEffect( pPosition );
			pPosition->affect();
		}*/


		// ��ü ����ڿ��� Relic �� �������ٴ� �޽����� ������.
		/*
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		StringStream msg;
		msg << pRelicInfo->getName() << " ������ " << pZoneInfo->getFullName() << " ( " << pt.x << " , " << pt.y << " ) �� ���������ϴ�.";

		GCSystemMessage message;
		message.setMessage( msg.toString() );
		g_pZoneGroupManager->broadcast( &message );
		*/
		if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_LOCK ))
		{
			EffectRelicLock* pLock = new EffectRelicLock(pItem);
			pLock->setDeadline( 10*10 ); // 10��
			pItem->setFlag( Effect::EFFECT_CLASS_RELIC_LOCK );
			pItem->getEffectManager().addEffect( pLock );
		}
	}
	else
	{
		throw Error("Logout�ϴµ� ���� ����߸� �ڸ��� ����");
		//return false;
	}

	return true;
}


bool dropRelicToZone(Creature* pCreature, bool bSendPacket)
	
{
	__BEGIN_TRY

	bool bDrop = false;

	///////////////////////////////////////////////////////////////////
	// ���� �� DragonEye �� ������ �ִٸ� ���� ��ġ�� ��~
	///////////////////////////////////////////////////////////////////
	if ( pCreature->isFlag(Effect::EFFECT_CLASS_DRAGON_EYE) )
	{
		g_pDragonEyeManager->warpToDefaultPosition( pCreature );

		Effect* pEffect = pCreature->findEffect( Effect::EFFECT_CLASS_DRAGON_EYE );
		if ( pEffect != NULL )
		{
			pCreature->removeFlag( Effect::EFFECT_CLASS_DRAGON_EYE );
			pEffect->unaffect();
			pCreature->deleteEffect( Effect::EFFECT_CLASS_DRAGON_EYE );
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////
	// ���� �� Relic Item�� ������ �ִٸ� �ٴڿ� ����߸���.
	///////////////////////////////////////////////////////////////////
	if ( pCreature->hasRelicItem())
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert( pPC != NULL );

		// mouse�� relic�� �ִ��� üũ
		Item* pSlotItem = pPC->getExtraInventorySlotItem();

		if (pSlotItem!=NULL 
			&& isRelicItem( pSlotItem ))
		{
			if (dropRelicToZone( pPC, pSlotItem ))
			{
				pPC->deleteItemFromExtraInventorySlot();

				// player�� mouse���� �����Ѵ�.
				// client���� �� ��Ŷ�� ������
				// mouse������ �� üũ���ְ� �ߴ�.

				if (bSendPacket)
				{
					GCDeleteInventoryItem gcDeleteInventoryItem;
					gcDeleteInventoryItem.setObjectID( pSlotItem->getObjectID() );

					pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );
				}

				bDrop = true;
			}
		}

		Zone* pZone = pPC->getZone();
		Assert( pZone != NULL );

		Inventory* pInventory = pPC->getInventory();
		Assert( pInventory != NULL );
		
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		// �κ��丮���� Relic Item�� ã�ƺ���.
		for ( CoordInven_t y = 0; y < pInventory->getHeight(); y++ )
		{
			for ( CoordInven_t x = 0; x < pInventory->getWidth(); x++ )
			{
				Item* pItem = pInventory->getItem( x, y );
				if ( pItem != NULL 
					&& isRelicItem( pItem ))
				{
					// �ϴ� �������� �ٴڿ� ����߸���.
					if (dropRelicToZone(pPC, pItem))
					{
						// �κ��丮���� ����.
						pInventory->deleteItem( pItem->getObjectID() );

						// player�� inventory���� �����Ѵ�.
						if (bSendPacket)
						{
							GCDeleteInventoryItem gcDeleteInventoryItem;
							gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

							pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );
						}

						bDrop = true;
					}
				}
			}
		}
	}

	return bDrop;

	__END_CATCH
}


// ��ü���� RelicItem�� �����°� ó��
bool
dissectionRelicItem( Corpse* pCorpse, Item* pItem, const TPOINT& pt )
	
{
	__BEGIN_TRY

	if (!isRelicItem( pItem ))
		return false;

	switch (pItem->getItemClass())
	{
		//----------------------------------------------------------------------		
		//
		// 							Relic
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_RELIC :
		{
			// ���� �������� �ϳ��� ���� �ʾҴٸ�(������ �������̾��ٸ�, EffectRelic�� ������ �ش�)
			try {
				int relicIndex = pItem->getItemType();
				const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo( pItem->getItemType() ) );

				deleteRelicEffect( pCorpse, pItem );

				g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_NULL);

                char msg[50];
                sprintf( msg, g_pStringPool->c_str( STRID_RELIC_FROM_RELIC_TABLE ),
                                pRelicInfo->getName().c_str() );

//				StringStream msg;
//				msg << "���� �����뿡�� "
//					<< "����(" << pRelicInfo->getName() << ")�� ���Խ��ϴ�.";

				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				g_pZoneGroupManager->broadcast( &gcSystemMessage );


				// relic�� ���������뿡�� �������Ա� ������
				// ���ʽ�/�г�Ƽ�� �ٽ� �������ش�.
				g_pCombatInfoManager->computeModify();
			} catch (Throwable& t) {
				cout << t.toString().c_str() << endl;
				throw;
			}
		}
		return true;

		//----------------------------------------------------------------------		
		//
		// 							BloodBible
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_BLOOD_BIBLE :
		{
			//deleteRelicEffect( pCorpse, pItem );

			const BloodBibleInfo* pBloodBibleInfo = dynamic_cast<BloodBibleInfo*>(g_pBloodBibleInfoManager->getItemInfo( pItem->getItemType() ) );

//			StringStream msg;
//			msg << "���� ���� ����(" << pBloodBibleInfo->getName() << ")�� ���Խ��ϴ�.";

			char msg[200];
			sprintf( msg, g_pStringPool->c_str( STRID_BLOOD_BIBLE_FROM_SHRINE ),
							pBloodBibleInfo->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			//g_pZoneGroupManager->broadcast( &gcSystemMessage );
			g_pHolyLandManager->broadcast( &gcSystemMessage );

			// ���� ���� ������ ��ġ ����
			if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
			{
				EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
				//pPosition->setNextTime(10);     // 1�� �� �޼��� �Ѹ���.
				pPosition->setTick( 1*60*10 );  // 1�и��� �ѹ��� �˸���.
				pPosition->setZoneID( pCorpse->getZone()->getZoneID() );
				pPosition->setX( pt.x );
				pPosition->setY( pt.y );
				pPosition->setPart( pItem->getItemType() );
				pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
				pItem->getEffectManager().addEffect( pPosition );
				pPosition->affect();
			}

		}
		return true;

		//----------------------------------------------------------------------		
		//
		// 							CastleSymbol
		//
		//----------------------------------------------------------------------		
		case Item::ITEM_CLASS_CASTLE_SYMBOL :
		{
			//deleteRelicEffect( pCorpse, pItem );

			const CastleSymbolInfo* pCastleSymbolInfo = dynamic_cast<const CastleSymbolInfo*>(g_pCastleSymbolInfoManager->getItemInfo( pItem->getItemType() ) );

			if ( pCastleSymbolInfo != NULL )
			{
//				StringStream msg;
//				msg << "�� ��¡��(" << pCastleSymbolInfo->getName() << ")�� ���Խ��ϴ�.";

				char msg[200];
				sprintf( msg, g_pStringPool->c_str( STRID_CASTLE_SYMBOL_FROM_SHRINE ),
								pCastleSymbolInfo->getName().c_str() );
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				//g_pZoneGroupManager->broadcast( &gcSystemMessage );
				g_pCastleInfoManager->broadcastShrinePacket( pItem->getItemType(), &gcSystemMessage );


				// ���� ���� ������ ��ġ ����
				if (!pItem->isFlag( Effect::EFFECT_CLASS_RELIC_POSITION))
				{
					EffectRelicPosition* pPosition = new EffectRelicPosition(pItem);
					//pPosition->setNextTime(10);     // 1�� �� �޼��� �Ѹ���.
					pPosition->setTick( 1*60*10 );  // 1�и��� �ѹ��� �˸���.
					pPosition->setZoneID( pCorpse->getZone()->getZoneID() );
					pPosition->setX( pt.x );
					pPosition->setY( pt.y );
					pPosition->setPart( pItem->getItemType() );
					pItem->setFlag( Effect::EFFECT_CLASS_RELIC_POSITION );
					pItem->getEffectManager().addEffect( pPosition );
					pPosition->affect();
				}
			}
		}
		return true;


		default :
			return false;
	}

	return false;

	__END_CATCH
}

// Relic�� pCorpse���� ��򰡷� warp�Ǿ��ٰ� �Ҷ�
// pCorpse�� Effect�� �ٿ��ش�.
void
sendRelicWarpEffect(Corpse* pCorpse)
	
{
	__BEGIN_TRY

	Assert(pCorpse!=NULL);

	if (pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD))
	{
		sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_GUARD_WARP );
	}
	else if (pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY))
	{
		sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_HOLY_WARP );
	}
	else 
	{
		ZoneID_t relicZoneID = pCorpse->getZone()->getZoneID();
		ZoneID_t castleZoneID;

		bool isCastle = g_pCastleInfoManager->getCastleZoneID( relicZoneID, castleZoneID );

		if (!isCastle)
			return;

		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
		Assert( pCastleInfo != NULL );

		if (pCastleInfo->getRace()==RACE_SLAYER)
		{
			sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_CASTLE_SHRINE_SLAYER_WARP );
		}
		else
		{
			sendBloodBibleEffect( pCorpse, Effect::EFFECT_CLASS_CASTLE_SHRINE_VAMPIRE_WARP );
		}
	}

	__END_CATCH
}

