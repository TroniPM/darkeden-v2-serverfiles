//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "VampireTuningItem.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "Stash.h"
#include "Utility.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"
#include "SubInventory.h"

VampireTuningItemInfoManager* g_pVampireTuningItemInfoManager = NULL;

ItemID_t VampireTuningItem::m_ItemIDRegistry = 0;
Mutex    VampireTuningItem::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class VampireTuningItem member methods
//////////////////////////////////////////////////////////////////////////////

VampireTuningItem::VampireTuningItem()
	throw()
{
	m_ItemType = 0;
	m_Num = 1;
}

VampireTuningItem::VampireTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
{
	m_ItemType = itemType;
	m_Num = Num;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "VampireTuningItem::VampireTuningItem() : Invalid item type or option type");
		throw ("VampireTuningItem::VampireTuningItem() : Invalid item type or optionType");
	}
}

void VampireTuningItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	if (itemID==0)
	{
		__ENTER_CRITICAL_SECTION(m_Mutex)

		m_ItemIDRegistry += g_pItemInfoManager->getItemIDSuccessor();
		m_ItemID = m_ItemIDRegistry;

		__LEAVE_CRITICAL_SECTION(m_Mutex)
	}
	else
	{
		m_ItemID = itemID;
	}
	
	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "INSERT INTO VampireTuningItemObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " << (int)m_Num << ", "
			<< (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireTuningItem::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireTuningItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void VampireTuningItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;

		sql << "UPDATE VampireTuningItemObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireTuningItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%u WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Num, m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string VampireTuningItem::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireTuningItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ")";

	return msg.toString();
}

VolumeWidth_t VampireTuningItem::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pVampireTuningItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t VampireTuningItem::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireTuningItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
		
Weight_t VampireTuningItem::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireTuningItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class VampireTuningItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

string VampireTuningItemInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "VampireTuningItemInfo("
		<< "ItemType:"     <<(int)m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       <<(int)m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      <<(int)m_Weight
		<< ",Description:" << m_Description
		<< ")";
	return msg.toString();
}

void VampireTuningItemInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampireTuningItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, TunningItemClass, TunningItemType, Ratio, Race FROM VampireTuningItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampireTuningItemInfo* pVampireTuningItemInfo = new VampireTuningItemInfo();

			pVampireTuningItemInfo->setItemType(pResult->getInt(++i));
			pVampireTuningItemInfo->setName(pResult->getString(++i));
			pVampireTuningItemInfo->setEName(pResult->getString(++i));
			pVampireTuningItemInfo->setPrice(pResult->getInt(++i));
			pVampireTuningItemInfo->setVolumeType(pResult->getInt(++i));
			pVampireTuningItemInfo->setTunningItemClass(pResult->getInt(++i));
			pVampireTuningItemInfo->setTunningItemType(pResult->getInt(++i));
			pVampireTuningItemInfo->setRatio(pResult->getInt(++i));
			addItemInfo(pVampireTuningItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class VampireTuningItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void VampireTuningItemLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y FROM VampireTuningItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM VampireTuningItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
												pCreature->getName().c_str() );



		while (pResult->next())
		{
			try {
				uint i = 0;

				VampireTuningItem* pVampireTuningItem = new VampireTuningItem();

				pVampireTuningItem->setItemID(pResult->getDWORD(++i));
				pVampireTuningItem->setObjectID(pResult->getDWORD(++i));
				pVampireTuningItem->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pVampireTuningItem->setNum( pResult->getInt(++i) );
				pVampireTuningItem->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*    pOusters        = NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
				Item*       pItem           = NULL;
				Stash*      pStash          = NULL;
				Belt*       pBelt           = NULL;
				Inventory*  pBeltInventory  = NULL;

				if (pCreature->isSlayer())
				{
					pSlayer     = dynamic_cast<Slayer*>(pCreature);
					pInventory  = pSlayer->getInventory();
					pStash      = pSlayer->getStash();
					pMotorcycle = pSlayer->getMotorcycle();

					if (pMotorcycle) pMotorInventory = pMotorcycle->getInventory();
				}
				else if (pCreature->isVampire()) 
				{
					pVampire   = dynamic_cast<Vampire*>(pCreature);
					pInventory = pVampire->getInventory();
					pStash     = pVampire->getStash();
				}
				else if (pCreature->isOusters()) 
				{
					pOusters   = dynamic_cast<Ousters*>(pCreature);
					pInventory = pOusters->getInventory();
					pStash     = pOusters->getStash();
				}
				else throw UnsupportedError("Monster,NPC 인벤토리의 저장은 아직 지원되지 않습니다.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pVampireTuningItem))
						{
							pInventory->addItemEx(x, y, pVampireTuningItem);
						}
						else
						{
							processItemBugEx(pCreature, pVampireTuningItem);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pVampireTuningItem);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pVampireTuningItem);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampireTuningItem);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampireTuningItem);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pVampireTuningItem);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pVampireTuningItem);
						break;

					case STORAGE_BOX :
						switch(pCreature->getCreatureClass()){
						case Creature::CREATURE_CLASS_SLAYER :
						case Creature::CREATURE_CLASS_VAMPIRE :
						case Creature::CREATURE_CLASS_OUSTERS :
							pItem = pInventory->findSubInventoryID(storageID, Item::ITEM_CLASS_SUB_INVENTORY);
								if (pItem != NULL)
								{
									SubInventory*       pBelts = dynamic_cast<SubInventory*>(pItem);
									pBeltInventory = ((SubInventory*)pBelts)->getInventory();
										if (pBeltInventory->canAddingEx(x, y, pVampireTuningItem))
										{
											cout << " 추가완료"<< endl;
											pBeltInventory->addItemEx(x, y, pVampireTuningItem);
										}else{
											cout << " 버그"<< endl;
											processItemBugEx(pCreature, pVampireTuningItem);
										}
								}else{
									processItemBugEx(pCreature, pVampireTuningItem);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pVampireTuningItem);
						}
						else pStash->insert(x, y, pVampireTuningItem);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pVampireTuningItem);
						break;

					default :
						SAFE_DELETE(pStmt);	// by sigi
						throw Error("invalid storage or OwnerID must be NULL");
				}

			} catch (Error& error) {
				filelog("itemLoadError.txt", "[%s] %s", getItemClassName().c_str(), error.toString().c_str());
				throw;
			} catch (Throwable& t) {
				filelog("itemLoadError.txt", "[%s] %s", getItemClassName().c_str(), t.toString().c_str());
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void VampireTuningItemLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM VampireTuningItemObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			VampireTuningItem* pVampireTuningItem = new VampireTuningItem();

			pVampireTuningItem->setItemID(pResult->getInt(++i));
			pVampireTuningItem->setObjectID(pResult->getInt(++i));
			pVampireTuningItem->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pVampireTuningItem->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pVampireTuningItem);
					}
					break;

				case STORAGE_STASH :
				case STORAGE_CORPSE :
					throw UnsupportedError("상자 및 시체안의 아이템의 저장은 아직 지원되지 않습니다.");

				default :
					throw Error("Storage must be STORAGE_ZONE");
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void VampireTuningItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VampireTuningItemLoader* g_pVampireTuningItemLoader = NULL;
