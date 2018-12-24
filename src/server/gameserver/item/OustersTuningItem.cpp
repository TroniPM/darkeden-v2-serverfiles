//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "OustersTuningItem.h"
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

OustersTuningItemInfoManager* g_pOustersTuningItemInfoManager = NULL;

ItemID_t OustersTuningItem::m_ItemIDRegistry = 0;
Mutex    OustersTuningItem::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItem member methods
//////////////////////////////////////////////////////////////////////////////

OustersTuningItem::OustersTuningItem()
	throw()
{
	m_ItemType = 0;
	m_Num = 1;
}

OustersTuningItem::OustersTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
{
	m_ItemType = itemType;
	m_Num = Num;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "OustersTuningItem::OustersTuningItem() : Invalid item type or option type");
		throw ("OustersTuningItem::OustersTuningItem() : Invalid item type or optionType");
	}
}

void OustersTuningItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	throw(Error)
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

		sql << "INSERT INTO OustersTuningItemObject "
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
void OustersTuningItem::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE OustersTuningItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void OustersTuningItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		/*
		StringStream sql;

		sql << "UPDATE OustersTuningItemObject SET "
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

		pStmt->executeQuery( "UPDATE OustersTuningItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%u WHERE ItemID=%ld",
								m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_Num, m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string OustersTuningItem::toString() const 
	throw()
{
	StringStream msg;

	msg << "OustersTuningItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType
		<< ")";

	return msg.toString();
}

VolumeWidth_t OustersTuningItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersTuningItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t OustersTuningItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersTuningItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
		
Weight_t OustersTuningItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pOustersTuningItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

string OustersTuningItemInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "OustersTuningItemInfo("
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

void OustersTuningItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM OustersTuningItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, TunningItemClass, TunningItemType, Ratio, Race FROM OustersTuningItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			OustersTuningItemInfo* pOustersTuningItemInfo = new OustersTuningItemInfo();

			pOustersTuningItemInfo->setItemType(pResult->getInt(++i));
			pOustersTuningItemInfo->setName(pResult->getString(++i));
			pOustersTuningItemInfo->setEName(pResult->getString(++i));
			pOustersTuningItemInfo->setPrice(pResult->getInt(++i));
			pOustersTuningItemInfo->setVolumeType(pResult->getInt(++i));
			pOustersTuningItemInfo->setTunningItemClass(pResult->getInt(++i));
			pOustersTuningItemInfo->setTunningItemType(pResult->getInt(++i));
			pOustersTuningItemInfo->setRatio(pResult->getInt(++i));
			addItemInfo(pOustersTuningItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void OustersTuningItemLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y FROM OustersTuningItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM OustersTuningItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
												pCreature->getName().c_str() );



		while (pResult->next())
		{
			try {
				uint i = 0;

				OustersTuningItem* pOustersTuningItem = new OustersTuningItem();

				pOustersTuningItem->setItemID(pResult->getDWORD(++i));
				pOustersTuningItem->setObjectID(pResult->getDWORD(++i));
				pOustersTuningItem->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pOustersTuningItem->setNum( pResult->getInt(++i) );
				pOustersTuningItem->setCreateType((Item::CreateType)pResult->getInt(++i));

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
				else throw UnsupportedError("Monster,NPC �κ��丮�� ������ ���� �������� �ʽ��ϴ�.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pOustersTuningItem))
						{
							pInventory->addItemEx(x, y, pOustersTuningItem);
						}
						else
						{
							processItemBugEx(pCreature, pOustersTuningItem);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pOustersTuningItem);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pOustersTuningItem);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pOustersTuningItem);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pOustersTuningItem);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pOustersTuningItem);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pOustersTuningItem);
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
										if (pBeltInventory->canAddingEx(x, y, pOustersTuningItem))
										{
											cout << " �߰��Ϸ�"<< endl;
											pBeltInventory->addItemEx(x, y, pOustersTuningItem);
										}else{
											cout << " ����"<< endl;
											processItemBugEx(pCreature, pOustersTuningItem);
										}
								}else{
									processItemBugEx(pCreature, pOustersTuningItem);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pOustersTuningItem);
						}
						else pStash->insert(x, y, pOustersTuningItem);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pOustersTuningItem);
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

void OustersTuningItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM OustersTuningItemObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			OustersTuningItem* pOustersTuningItem = new OustersTuningItem();

			pOustersTuningItem->setItemID(pResult->getInt(++i));
			pOustersTuningItem->setObjectID(pResult->getInt(++i));
			pOustersTuningItem->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pOustersTuningItem->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pOustersTuningItem);
					}
					break;

				case STORAGE_STASH :
				case STORAGE_CORPSE :
					throw UnsupportedError("���� �� ��ü���� �������� ������ ���� �������� �ʽ��ϴ�.");

				default :
					throw Error("Storage must be STORAGE_ZONE");
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void OustersTuningItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

OustersTuningItemLoader* g_pOustersTuningItemLoader = NULL;
