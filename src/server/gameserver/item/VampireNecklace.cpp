//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireNecklace.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "VampireNecklace.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Belt.h"
#include "Motorcycle.h"
#include "ItemInfoManager.h"
#include "Stash.h"
#include "ItemUtil.h"
#include "SubInventory.h"
// global variable declaration
VampireNecklaceInfoManager* g_pVampireNecklaceInfoManager = NULL;

ItemID_t VampireNecklace::m_ItemIDRegistry = 0;
Mutex    VampireNecklace::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
VampireNecklace::VampireNecklace()
	throw()
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
	setDurability(0);
	//m_EnchantLevel = 0;
}

VampireNecklace::VampireNecklace(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0)
{
	setItemType(itemType);
	setOptionType(optionType);
	//m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "VampireNecklace::VampireNecklace() : Invalid item type or option type");
		throw ("VampireNecklace::VampireNecklace() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void VampireNecklace::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	
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

		string optionField,optionField2;
		setOptionTypeToField( getOptionTypeList(), optionField );
		setOptionTypeToField( getOptionTypeList2(), optionField2 );

		sql << "INSERT INTO VampireNecklaceObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, OptionType2, Durability, Grade, HeroOption, HeroOptionAttr, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', '" << optionField2.c_str() << "', "<< getDurability() << ", " << getGrade() << "," << (int)getHeroOption() << "," << (int)getHeroOptionAttr() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireNecklace::tinysave(const char* field) const
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireNecklaceObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireNecklace::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE VampireNecklaceObject SET "
			<< "ObjectID = " << m_ObjectID
			<< ",ItemType = " << getItemType()
			<< ",OwnerID = '" << ownerID << "'"
			<< ",Storage = " <<(int)storage
			<< ",StorageID = " << storageID
			<< ",X = " <<(int)x
			<< ",Y = " <<(int)y
			<< ",OptionType = " <<(int)getOptionTypeList()
			<< ",Durability = " << getDurability()
			<< ",EnchantLevel = " <<(int)m_EnchantLevel
			<< " WHERE ItemID = " << m_ItemID;

		pStmt->executeQuery(sql.toString());
		*/

		string optionField,optionField2;
		setOptionTypeToField( getOptionTypeList(), optionField );
		setOptionTypeToField( getOptionTypeList2(), optionField2 );
		pStmt->executeQuery( "UPDATE VampireNecklaceObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', OptionType2='%s', Durability=%d, Grade=%d, EnchantLevel=%d, HeroOption=%d, HeroOptionAttr=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), optionField2.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(),(int)getHeroOption(),(int)getHeroOptionAttr(), m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireNecklace::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireNecklace("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",Durability:"   <<(int)getDurability()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}

/*
//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t VampireNecklace::getVolumeWidth() const 
	
{
	__BEGIN_TRY

	return g_pVampireNecklaceInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t VampireNecklace::getVolumeHeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireNecklaceInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t VampireNecklace::getWeight() const 
	
{
	__BEGIN_TRY

	return g_pVampireNecklaceInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t VampireNecklace::getDefenseBonus() const 
	
{
	__BEGIN_TRY

	return g_pVampireNecklaceInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t VampireNecklace::getProtectionBonus() const
	
{
	__BEGIN_TRY

	return g_pVampireNecklaceInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireNecklaceInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireNecklaceInfo("
		<< "ItemType:" << m_ItemType
		<< ",Name:" << m_Name
		<< ",EName:" << m_EName
		<< ",Price:" << m_Price
		<< ",VolumeType:" << Volume2String[m_VolumeType]
		<< ",Weight:" << m_Weight
		<< ",Description:" << m_Description
		<< ",Durability:" << m_Durability
		<< ",DefenseBonus:" << m_DefenseBonus
		<< ")";

	return msg.toString();
}


//--------------------------------------------------------------------------------
// load from DB
//--------------------------------------------------------------------------------
void VampireNecklaceInfoManager::load() 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampireNecklaceInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM VampireNecklaceInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampireNecklaceInfo* pVampireNecklaceInfo = new VampireNecklaceInfo();

			pVampireNecklaceInfo->setItemType(pResult->getInt(++i));
			pVampireNecklaceInfo->setName(pResult->getString(++i));
			pVampireNecklaceInfo->setEName(pResult->getString(++i));
			pVampireNecklaceInfo->setPrice(pResult->getInt(++i));
			pVampireNecklaceInfo->setVolumeType(pResult->getInt(++i));
			pVampireNecklaceInfo->setWeight(pResult->getInt(++i));
			pVampireNecklaceInfo->setRatio(pResult->getInt(++i));
			pVampireNecklaceInfo->setDurability(pResult->getInt(++i));
			pVampireNecklaceInfo->setDefenseBonus(pResult->getInt(++i));
			pVampireNecklaceInfo->setProtectionBonus(pResult->getInt(++i));
			pVampireNecklaceInfo->setReqAbility(pResult->getString(++i));
			pVampireNecklaceInfo->setItemLevel(pResult->getInt(++i));
			pVampireNecklaceInfo->setDefaultOptions(pResult->getString(++i));
			pVampireNecklaceInfo->setUpgradeRatio(pResult->getInt(++i));
			pVampireNecklaceInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pVampireNecklaceInfo->setNextOptionRatio(pResult->getInt(++i));
			pVampireNecklaceInfo->setNextItemType(pResult->getInt(++i));
			pVampireNecklaceInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pVampireNecklaceInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void VampireNecklaceLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< "OptionType, Durability, EnchantLevel FROM VampireNecklaceObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,OptionType, OptionType2, Durability, Grade, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM VampireNecklaceObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				VampireNecklace* pVampireNecklace = new VampireNecklace();

				pVampireNecklace->setItemID(pResult->getDWORD(++i));
				pVampireNecklace->setObjectID(pResult->getDWORD(++i));
				pVampireNecklace->setItemType(pResult->getDWORD(++i));
	
				if (g_pVampireNecklaceInfoManager->getItemInfo(pVampireNecklace->getItemType())->isUnique())
					pVampireNecklace->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pVampireNecklace->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pVampireNecklace->setOptionType2(optionTypes2);

				pVampireNecklace->setDurability(pResult->getInt(++i));
				pVampireNecklace->setGrade(pResult->getInt(++i));
				pVampireNecklace->setEnchantLevel(pResult->getInt(++i));
pVampireNecklace->setHeroOption(pResult->getInt(++i));
pVampireNecklace->setHeroOptionAttr(pResult->getInt(++i));
				pVampireNecklace->setCreateType((Item::CreateType)pResult->getInt(++i));

				Inventory*  pInventory      = NULL;
				Slayer*     pSlayer         = NULL;
				Vampire*    pVampire        = NULL;
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
				else throw UnsupportedError("Monster,NPC �κ��丮�� ������ ���� �������� �ʽ��ϴ�.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pVampireNecklace))
						{
							pInventory->addItemEx(x, y, pVampireNecklace);
						}
						else
						{
							processItemBugEx(pCreature, pVampireNecklace);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							processItemBugEx(pCreature, pVampireNecklace);
						}
						else if (pCreature->isVampire())
						{
							if (!pVampire->isWear((Vampire::WearPart)x))
							{
								pVampire->wearItem((Vampire::WearPart)x, pVampireNecklace);
							}
							else
							{
								processItemBugEx(pCreature, pVampireNecklace);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pVampireNecklace);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampireNecklace);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampireNecklace);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pVampireNecklace);
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
										if (pBeltInventory->canAddingEx(x, y, pVampireNecklace))
										{
											cout << " �߰��Ϸ�"<< endl;
											pBeltInventory->addItemEx(x, y, pVampireNecklace);
										}else{
											cout << " ����"<< endl;
											processItemBugEx(pCreature, pVampireNecklace);
										}
								}else{
									processItemBugEx(pCreature, pVampireNecklace);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pVampireNecklace);
						}
						else pStash->insert(x, y, pVampireNecklace);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pVampireNecklace);
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
void VampireNecklaceLoader::load(Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, OptionType2, Durability, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM VampireNecklaceObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			VampireNecklace* pVampireNecklace = new VampireNecklace();

			pVampireNecklace->setItemID(pResult->getInt(++i));
			pVampireNecklace->setObjectID(pResult->getInt(++i));
			pVampireNecklace->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pVampireNecklace->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pVampireNecklace->setOptionType2(optionTypes2);

			pVampireNecklace->setDurability(pResult->getInt(++i));
			pVampireNecklace->setEnchantLevel(pResult->getInt(++i));
pVampireNecklace->setHeroOption(pResult->getInt(++i));
pVampireNecklace->setHeroOptionAttr(pResult->getInt(++i));
			pVampireNecklace->setCreateType((Item::CreateType)pResult->getInt(++i));
			

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pVampireNecklace);
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


//--------------------------------------------------------------------------------
// load to inventory
//--------------------------------------------------------------------------------
void VampireNecklaceLoader::load(StorageID_t storageID, Inventory* pInventory) 
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
	}
	END_DB(pStmt)
	
	__END_CATCH
}

VampireNecklaceLoader* g_pVampireNecklaceLoader = NULL;
