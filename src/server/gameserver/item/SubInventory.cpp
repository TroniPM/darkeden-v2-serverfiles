//////////////////////////////////////////////////////////////////////////////
// Filename    : Belt.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SubInventory.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include	"Ousters.h"
#include "SubInventory.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "PCItemInfo.h"

// global variable declaration
SubInventoryInfoManager* g_pSubInventoryInfoManager = NULL;

ItemID_t SubInventory::m_ItemIDRegistry = 0;
Mutex    SubInventory::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
SubInventory::SubInventory()
	
//: m_ItemType(0), m_Durability(0), m_pInventory(NULL)
{
	setItemType(0);
	m_pInventory = NULL;
//	m_EnchantLevel = 0;
}

SubInventory::SubInventory(ItemType_t itemType, const list<OptionType_t>& optionType)
	
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0), m_pInventory(NULL)
{
	__BEGIN_TRY

	setItemType(itemType);

	SubInventoryInfo* pSubInventoryInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(getItemType()));

	m_pInventory = new Inventory(pSubInventoryInfo->getPocketWidthCount(), pSubInventoryInfo->getPocketHeightCount());

//	m_EnchantLevel = 0;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "SubInventory::SubInventory() : Invalid item type or option type");
		throw ("SubInventory::SubInventory() : Invalid item type or optionType");
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
SubInventory::~SubInventory()
	
{
	SAFE_DELETE(m_pInventory);
}

//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void SubInventory::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

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

		pStmt->executeQuery( "INSERT INTO SubInventoryObject (ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, ItemFlag) VALUES(%ld, %ld, %d, '%s', %d, %ld, %d, %d, %d)",
								m_ItemID, m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)m_CreateType );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// destroy item
//--------------------------------------------------------------------------------
bool SubInventory::destroy()
	
{
	__BEGIN_TRY

	Statement* pStmt;

	//-------------------------------------------------------
	// 벨트에 남아있는 아이템이 있다면 안에 있는 아이템들도
	// destroy 해줘야 한다.
	// 벨트 같은 경우는 위에서 delete하면서 아이템을 삭제
	// 하기 때문에 여기서는 delete해주지 않기로 한다...
	// 쓸모가 없다면 위에서 필히 벨트를 지워야 한다.
	//-------------------------------------------------------
	for (int i = 0; i < m_pInventory->getHeight(); i++) 
	{
		for (int j = 0; j < m_pInventory->getWidth(); j++) 
		{
			Item* pItem = m_pInventory->getItem(j, i);
			if (pItem != NULL) 
			{
				pItem->destroy();
			}
		}
	}

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("DELETE FROM SubInventoryObject WHERE ItemID = %ld", m_ItemID);

		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH

	return true;
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SubInventory::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE SubInventoryObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SubInventory::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE SubInventoryObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)m_OptionType
			<< ",Durability = " << m_Durability
			<< ",EnchantLevel = " <<(int)m_EnchantLevel
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE SubInventoryObject SET ObjectID=%ld, ItemType=%d, OwnerID= '%s', Storage=%d, StorageID=%ld, X=%d, Y=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_ItemID);

		// 일일이 아이템을 하나씩 꺼내서 바로 UPDATE 하도록 한다.
		for (int i = 0; i < m_pInventory->getHeight(); i++) 
		/*{
			for (int j = 0; j < m_pInventory->getWidth(); j++) 
			{
				Item* pItem = m_pInventory->getItem(i, j);
				if (pItem != NULL) {
					pItem->save(ownerID, STORAGE_BOX, m_ItemID, i, j);
				}
			}
		}*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void SubInventory::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);

	BYTE SubItemCount = 0;

	// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
	for (int i = 0; i < getPocketWidthCount() ; i++) 
	{
		for (int j = 0; j < getPocketHeightCount(); j++) 
		{
			Item* pSubInventoryItem = getInventory()->getItem(i, j);
			if (pSubInventoryItem != NULL) 
			{
				SubItemInfo* pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pSubInventoryItem->getObjectID());
				pSubItemInfo->setItemClass(pSubInventoryItem->getItemClass());
				pSubItemInfo->setItemType(pSubInventoryItem->getItemType());
				pSubItemInfo->setItemNum(pSubInventoryItem->getNum());
				pSubItemInfo->setSlotID(i);

				result.addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}
	}

	result.setListNum(SubItemCount);
}

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string SubInventory::toString() const 
	
{
	StringStream msg;

	msg << "SubInventory("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",Durability:"   <<(int)getDurability()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t SubInventory::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t SubInventory::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t SubInventory::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pSubInventoryInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/
//--------------------------------------------------------------------------------
// get pocket count
//--------------------------------------------------------------------------------
PocketNum_t SubInventory::getPocketWidthCount(void) const
	
{
	__BEGIN_TRY

	SubInventoryInfo* pSubInventoryInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(getItemType()));
	Assert(pSubInventoryInfo != NULL);
	return pSubInventoryInfo->getPocketWidthCount();

	__END_CATCH
}

PocketNum_t SubInventory::getPocketHeightCount(void) const
	
{
	__BEGIN_TRY

	SubInventoryInfo* pSubInventoryInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(getItemType()));
	Assert(pSubInventoryInfo != NULL);
	return pSubInventoryInfo->getPocketHeightCount();

	__END_CATCH
}



//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string SubInventoryInfo::toString() const 
	
{
	StringStream msg;

	msg << "SubInventoryInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void SubInventoryInfoManager::load() 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SubInventoryInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Width, Height FROM SubInventoryInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SubInventoryInfo* pSubInventoryInfo = new SubInventoryInfo();

			pSubInventoryInfo->setItemType(pResult->getInt(++i));
			pSubInventoryInfo->setName(pResult->getString(++i));
			pSubInventoryInfo->setEName(pResult->getString(++i));
			pSubInventoryInfo->setPrice(pResult->getInt(++i));
			pSubInventoryInfo->setVolumeType(pResult->getInt(++i));
			pSubInventoryInfo->setWeight(pResult->getInt(++i));
			pSubInventoryInfo->setRatio(pResult->getInt(++i));
			pSubInventoryInfo->setPocketWidthCount(pResult->getInt(++i));
			pSubInventoryInfo->setPocketHeightCount(pResult->getInt(++i));
			addItemInfo(pSubInventoryInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_DEBUG
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void SubInventoryLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ROM SubInventoryObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM SubInventoryObject WHERE OwnerID = '%s' AND Storage IN (0, 1, 2, 3, 4, 9)",
												pCreature->getName().c_str() );



		while (pResult->next())
		{
			try {
				uint i = 0;

				SubInventory* pSubInventory = new SubInventory();

				pSubInventory->setItemID(pResult->getDWORD(++i));
				pSubInventory->setObjectID(pResult->getDWORD(++i));
				pSubInventory->setItemType(pResult->getDWORD(++i));
	
				if (g_pSubInventoryInfoManager->getItemInfo(pSubInventory->getItemType())->isUnique())
					pSubInventory->setUnique();

				SubInventoryInfo* pSubInventoryInfo = dynamic_cast<SubInventoryInfo*>(g_pSubInventoryInfoManager->getItemInfo(pSubInventory->getItemType()));
				Inventory* pSubInventoryInventory = new Inventory(pSubInventoryInfo->getPocketWidthCount(), pSubInventoryInfo->getPocketHeightCount());

				pSubInventory->setInventory(pSubInventoryInventory);

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pSubInventory->setCreateType((Item::CreateType)pResult->getInt(++i));
				
				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*    pOusters       = NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
				//Item*       pItem           = NULL;
				Stash*      pStash          = NULL;

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
						if (pInventory->canAddingEx(x, y, pSubInventory))
						{
							pInventory->addItemEx(x, y, pSubInventory);
						}
						else 
						{
							processItemBugEx(pCreature, pSubInventory);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pSubInventory);
							}
							else
							{
								processItemBugEx(pCreature, pSubInventory);
							}
						}
						else if (pCreature->isVampire())
						{
							processItemBugEx(pCreature, pSubInventory);
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pSubInventory);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSubInventory);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSubInventory);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pSubInventory);
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pSubInventory);
						}
						else
						{
							pStash->insert(x, y, pSubInventory);
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pSubInventory);
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


//--------------------------------------------------------------------------------
// load to zone
//--------------------------------------------------------------------------------
void SubInventoryLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " ItemFlag FROM SubInventoryObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			SubInventory* pSubInventory = new SubInventory();

			pSubInventory->setItemID(pResult->getInt(++i));
			pSubInventory->setObjectID(pResult->getInt(++i));
			pSubInventory->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pSubInventory->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pSubInventory);
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


//--------------------------------------------------------------------------------
// load to inventory
//--------------------------------------------------------------------------------
void SubInventoryLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

// global variable definition
SubInventoryLoader* g_pSubInventoryLoader = NULL;
