//////////////////////////////////////////////////////////////////////////////
// Filename    : CoreZap.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "WeaponZap.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "SubInventory.h"
// global variable declaration
WeaponZapInfoManager* g_pWeaponZapInfoManager = NULL;

ItemID_t WeaponZap::m_ItemIDRegistry = 0;
Mutex    WeaponZap::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
WeaponZap::WeaponZap()
	throw()
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
}

WeaponZap::WeaponZap(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	setItemType(itemType);
	setOptionType(optionType);

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "WeaponZap::WeaponZap() : Invalid item type or option type");
		throw ("WeaponZap::WeaponZap() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void WeaponZap::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		StringStream sql;

		string optionField;
		setOptionTypeToField( getOptionTypeList(), optionField );

		sql << "INSERT INTO WeaponZapObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, Grade, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', " << getGrade() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void WeaponZap::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE WeaponZapObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void WeaponZap::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE WeaponZapObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << m_ItemType
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)m_OptionType
			<< ",Durability = " << m_Durability
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		string optionField;
		setOptionTypeToField( getOptionTypeList(), optionField );
		pStmt->executeQuery( "UPDATE WeaponZapObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', Grade=%d WHERE ItemID=%ld",
									m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), getGrade(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string WeaponZap::toString() const 
	throw()
{
	StringStream msg;

	msg << "WeaponZap("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t WeaponZap::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pWeaponZapInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t WeaponZap::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pWeaponZapInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t WeaponZap::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pWeaponZapInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t WeaponZap::getDefenseBonus() const 
	
{
	__BEGIN_TRY

	return g_pWeaponZapInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t WeaponZap::getProtectionBonus() const
	
{
	__BEGIN_TRY

	return g_pWeaponZapInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string WeaponZapInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "WeaponZapInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void WeaponZapInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM WeaponZapInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Defense, Protection FROM WeaponZapInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			WeaponZapInfo* pWeaponZapInfo = new WeaponZapInfo();

			pWeaponZapInfo->setItemType(pResult->getInt(++i));
			pWeaponZapInfo->setName(pResult->getString(++i));
			pWeaponZapInfo->setEName(pResult->getString(++i));
			pWeaponZapInfo->setPrice(pResult->getInt(++i));
			pWeaponZapInfo->setVolumeType(pResult->getInt(++i));
			pWeaponZapInfo->setWeight(pResult->getInt(++i));
			pWeaponZapInfo->setRatio(pResult->getInt(++i));
			pWeaponZapInfo->setDefenseBonus(pResult->getInt(++i));
			pWeaponZapInfo->setProtectionBonus(pResult->getInt(++i));

			addItemInfo(pWeaponZapInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void WeaponZapLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, "
			<< " OptionType, Durability, EnchantLevel FROM WeaponZapObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, Grade, EnchantLevel, ItemFlag FROM WeaponZapObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				WeaponZap* pWeaponZap = new WeaponZap();

				pWeaponZap->setItemID(pResult->getDWORD(++i));
				pWeaponZap->setObjectID(pResult->getDWORD(++i));
				pWeaponZap->setItemType(pResult->getDWORD(++i));
	
				if (g_pWeaponZapInfoManager->getItemInfo(pWeaponZap->getItemType())->isUnique())
					pWeaponZap->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pWeaponZap->setOptionType(optionTypes);

				pWeaponZap->setGrade(pResult->getInt(++i));
				pWeaponZap->setEnchantLevel(pResult->getInt(++i));
				pWeaponZap->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
				Ousters*	pOusters		= NULL;
				Motorcycle* pMotorcycle     = NULL;
				Inventory*  pMotorInventory = NULL;
				Item*       pItem           = NULL;
				Stash*      pStash          = NULL;
				SubInventory*       pBelt           = NULL;
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
						if (pInventory->canAddingEx(x, y, pWeaponZap))
						{
							pInventory->addItemEx(x, y, pWeaponZap);
						}
						else
						{
							processItemBugEx(pCreature, pWeaponZap);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							if (!pSlayer->isWear((Slayer::WearPart)x))
							{
								pSlayer->wearItem((Slayer::WearPart)x, pWeaponZap);
							}
							else
							{
								processItemBugEx(pCreature, pWeaponZap);
							}
						}
						else if (pCreature->isVampire())
						{
							if (!pVampire->isWear((Vampire::WearPart)x))
							{
								pVampire->wearItem((Vampire::WearPart)x, pWeaponZap);
							}
							else
							{
								processItemBugEx(pCreature, pWeaponZap);
							}
						}
						else if (pCreature->isOusters())
						{
							if (!pOusters->isWear((Ousters::WearPart)x))
							{
								pOusters->wearItem((Ousters::WearPart)x, pWeaponZap);
							}
							else
							{
								processItemBugEx(pCreature, pWeaponZap);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pWeaponZap);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pWeaponZap);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pWeaponZap);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pWeaponZap);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pWeaponZap);
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
										if (pBeltInventory->canAddingEx(x, y, pWeaponZap))
										{
											cout << " 추가완료"<< endl;
											pBeltInventory->addItemEx(x, y, pWeaponZap);
										}else{
											cout << " 버그"<< endl;
											processItemBugEx(pCreature, pWeaponZap);
										}
								}else{
									processItemBugEx(pCreature, pWeaponZap);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pWeaponZap);
						}
						else pStash->insert(x, y, pWeaponZap);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pWeaponZap);
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
void WeaponZapLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, ItemFlag FROM WeaponZapObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			WeaponZap* pWeaponZap = new WeaponZap();

			pWeaponZap->setItemID(pResult->getInt(++i));
			pWeaponZap->setObjectID(pResult->getInt(++i));
			pWeaponZap->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pWeaponZap->setOptionType(optionTypes);

			pWeaponZap->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pWeaponZap);
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
void WeaponZapLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

WeaponZapLoader* g_pWeaponZapLoader = NULL;
