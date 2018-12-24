//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireAmulet.cpp
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "VampireAmulet.h"
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
VampireAmuletInfoManager* g_pVampireAmuletInfoManager = NULL;

ItemID_t VampireAmulet::m_ItemIDRegistry = 0;
Mutex    VampireAmulet::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
VampireAmulet::VampireAmulet()
	throw()
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
	//m_EnchantLevel = 0;
}

VampireAmulet::VampireAmulet(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0)
{
	setItemType(itemType);
	setOptionType(optionType);

	//m_EnchantLevel = 0;

//	m_Durability = computeMaxDurability(this);

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "VampireAmulet::VampireAmulet() : Invalid item type or option type");
		throw ("VampireAmulet::VampireAmulet() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void VampireAmulet::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
	throw(Error)
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

		sql << "INSERT INTO VampireAmuletObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID ,"
			<< " X, Y, OptionType, OptionType2, Grade, HeroOption, HeroOptionAttr, ItemFlag)"
			<< " VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " <<(int)storage << ", " << storageID << ", " 
			<<(int)x << ", " <<(int)y << ", '" << optionField.c_str() << "', '" << optionField2.c_str() << "', " <<  getGrade() << ", " << (int)getHeroOption() << "," << (int)getHeroOptionAttr() << "," << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireAmulet::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE VampireAmuletObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void VampireAmulet::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE VampireAmuletObject SET "
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
	
		string optionField,optionField2;
		setOptionTypeToField( getOptionTypeList(), optionField );
		setOptionTypeToField( getOptionTypeList2(), optionField2 );
		pStmt->executeQuery( "UPDATE VampireAmuletObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', OptionType2='%s', Grade=%d, EnchantLevel=%d, HeroOption=%d, HeroOptionAttr=%d WHERE ItemID=%ld", 
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), optionField2.c_str(), getGrade(), (int)getEnchantLevel(),(int)getHeroOption(),(int)getHeroOptionAttr(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireAmulet::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireAmulet("
		<< "ItemID:"        << m_ItemID
		<< ",ItemType:"     <<(int)getItemType()
		<< ",OptionType:"   <<getOptionTypeToString(getOptionTypeList()).c_str()
		<< ",EnchantLevel:" <<(int)getEnchantLevel()
		<< ")";

	return msg.toString();
}


/*//--------------------------------------------------------------------------------
// get width
//--------------------------------------------------------------------------------
VolumeWidth_t VampireAmulet::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireAmuletInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t VampireAmulet::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireAmuletInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t VampireAmulet::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireAmuletInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t VampireAmulet::getDefenseBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireAmuletInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t VampireAmulet::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pVampireAmuletInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VampireAmuletInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "VampireAmuletInfo("
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
void VampireAmuletInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM VampireAmuletInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM VampireAmuletInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			VampireAmuletInfo* pVampireAmuletInfo = new VampireAmuletInfo();

			pVampireAmuletInfo->setItemType(pResult->getInt(++i));
			pVampireAmuletInfo->setName(pResult->getString(++i));
			pVampireAmuletInfo->setEName(pResult->getString(++i));
			pVampireAmuletInfo->setPrice(pResult->getInt(++i));
			pVampireAmuletInfo->setVolumeType(pResult->getInt(++i));
			pVampireAmuletInfo->setWeight(pResult->getInt(++i));
			pVampireAmuletInfo->setRatio(pResult->getInt(++i));
			pVampireAmuletInfo->setDurability(pResult->getInt(++i));
			pVampireAmuletInfo->setDefenseBonus(pResult->getInt(++i));
			pVampireAmuletInfo->setProtectionBonus(pResult->getInt(++i));
			pVampireAmuletInfo->setReqAbility(pResult->getString(++i));
			pVampireAmuletInfo->setItemLevel(pResult->getInt(++i));
			pVampireAmuletInfo->setDefaultOptions(pResult->getString(++i));
			pVampireAmuletInfo->setUpgradeRatio(pResult->getInt(++i));
			pVampireAmuletInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pVampireAmuletInfo->setNextOptionRatio(pResult->getInt(++i));
			pVampireAmuletInfo->setNextItemType(pResult->getInt(++i));
			pVampireAmuletInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pVampireAmuletInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void VampireAmuletLoader::load(Creature* pCreature) 
	throw(Error)
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
			<< "OptionType, Durability, EnchantLevel FROM VampireAmuletObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,OptionType, OptionType2, Durability, Grade, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM VampireAmuletObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				VampireAmulet* pVampireAmulet = new VampireAmulet();

				pVampireAmulet->setItemID(pResult->getDWORD(++i));
				pVampireAmulet->setObjectID(pResult->getDWORD(++i));
				pVampireAmulet->setItemType(pResult->getDWORD(++i));
	
				if (g_pVampireAmuletInfoManager->getItemInfo(pVampireAmulet->getItemType())->isUnique())
					pVampireAmulet->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pVampireAmulet->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pVampireAmulet->setOptionType2(optionTypes2);

				pVampireAmulet->setDurability(pResult->getInt(++i));
				pVampireAmulet->setGrade(pResult->getInt(++i));
				pVampireAmulet->setEnchantLevel(pResult->getInt(++i));
pVampireAmulet->setHeroOption(pResult->getInt(++i));
pVampireAmulet->setHeroOptionAttr(pResult->getInt(++i));
				pVampireAmulet->setCreateType((Item::CreateType)pResult->getInt(++i));

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
						if (pInventory->canAddingEx(x, y, pVampireAmulet))
						{
							pInventory->addItemEx(x, y, pVampireAmulet);
						}
						else
						{
							processItemBugEx(pCreature, pVampireAmulet);
						}
						break;

					case STORAGE_GEAR:
						if (pCreature->isSlayer())
						{
							processItemBugEx(pCreature, pVampireAmulet);
						}
						else if (pCreature->isVampire())
						{
							if (!pVampire->isWear((Vampire::WearPart)x))
							{
								pVampire->wearItem((Vampire::WearPart)x, pVampireAmulet);
							}
							else
							{
								processItemBugEx(pCreature, pVampireAmulet);
							}
						}
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pVampireAmulet);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pVampireAmulet);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pVampireAmulet);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pVampireAmulet);
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
										if (pBeltInventory->canAddingEx(x, y, pVampireAmulet))
										{
											cout << " �߰��Ϸ�"<< endl;
											pBeltInventory->addItemEx(x, y, pVampireAmulet);
										}else{
											cout << " ����"<< endl;
											processItemBugEx(pCreature, pVampireAmulet);
										}
								}else{
									processItemBugEx(pCreature, pVampireAmulet);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pVampireAmulet);
						}
						else pStash->insert(x, y, pVampireAmulet);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pVampireAmulet);
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
void VampireAmuletLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y,"
			<< " OptionType, OptionType2, Durability, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM VampireAmuletObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			VampireAmulet* pVampireAmulet = new VampireAmulet();

			pVampireAmulet->setItemID(pResult->getInt(++i));
			pVampireAmulet->setObjectID(pResult->getInt(++i));
			pVampireAmulet->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pVampireAmulet->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pVampireAmulet->setOptionType2(optionTypes2);

			pVampireAmulet->setDurability(pResult->getInt(++i));
			pVampireAmulet->setEnchantLevel(pResult->getInt(++i));
pVampireAmulet->setHeroOption(pResult->getInt(++i));
pVampireAmulet->setHeroOptionAttr(pResult->getInt(++i));
			pVampireAmulet->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pVampireAmulet);
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
void VampireAmuletLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

VampireAmuletLoader* g_pVampireAmuletLoader = NULL;
