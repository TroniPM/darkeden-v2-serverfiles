//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersStone.cpp
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "StoneAbility.h"
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
StoneAbilityInfoManager* g_pStoneAbilityInfoManager = NULL;

ItemID_t StoneAbility::m_ItemIDRegistry = 0;
Mutex    StoneAbility::m_Mutex;

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
StoneAbility::StoneAbility()
	throw()
//: m_ItemType(0), m_Durability(0)
{
	setItemType(0);
	setDurability(0);
	//m_EnchantLevel = 0;
}

StoneAbility::StoneAbility(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
//: m_ItemType(itemType), m_OptionType(optionType), m_Durability(0)
{
	setItemType(itemType);
	setOptionType(optionType);
	//m_EnchantLevel = 0;

	setDurability(computeMaxDurability(this));

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "StoneAbility::StoneAbility() : Invalid item type or option type");
		throw ("StoneAbility::StoneAbility() : Invalid item type or optionType");
	}
}


//--------------------------------------------------------------------------------
// create item
//--------------------------------------------------------------------------------
void StoneAbility::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO StoneAbilityObject "
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
void StoneAbility::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE StoneAbilityObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void StoneAbility::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "UPDATE StoneAbilityObject SET "
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
		pStmt->executeQuery( "UPDATE StoneAbilityObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, OptionType='%s', OptionType2='%s', Durability=%d, Grade=%d, EnchantLevel=%d, HeroOption=%d, HeroOptionAttr=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, optionField.c_str(), optionField2.c_str(), getDurability(), getGrade(), (int)getEnchantLevel(),(int)getHeroOption(),(int)getHeroOptionAttr(), m_ItemID );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string StoneAbility::toString() const 
	throw()
{
	StringStream msg;

	msg << "StoneAbility("
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
VolumeWidth_t StoneAbility::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get height
//--------------------------------------------------------------------------------
VolumeHeight_t StoneAbility::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
// get weight
//--------------------------------------------------------------------------------
Weight_t StoneAbility::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get/set armor's Defense Bonus
//--------------------------------------------------------------------------------
Defense_t StoneAbility::getDefenseBonus() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(m_ItemType)->getDefenseBonus();

	__END_CATCH
}
Protection_t StoneAbility::getProtectionBonus() const
	throw(Error)
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(m_ItemType)->getProtectionBonus();
	
	__END_CATCH
}
*/

//--------------------------------------------------------------------------------
// get Elemental Type
//--------------------------------------------------------------------------------
ElementalType StoneAbility::getElementalType(void) const
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(getItemType())->getElementalType();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get Elemental
//--------------------------------------------------------------------------------
Elemental_t StoneAbility::getElemental(void) const
{
	__BEGIN_TRY

	return g_pStoneAbilityInfoManager->getItemInfo(getItemType())->getElemental();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string StoneAbilityInfo::toString() const 
	throw()
{
	StringStream msg;

	msg << "StoneAbilityInfo("
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
void StoneAbilityInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM StoneAbilityInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM StoneAbilityInfo"
			//"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, Durability, Defense, Protection, ReqAbility, ItemLevel, DefaultOption, UpgradeRatio, UpgradeCrashPercent, NextOptionRatio, NextItemType, DowngradeRatio FROM StoneAbilityInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			StoneAbilityInfo* pStoneAbilityInfo = new StoneAbilityInfo();

			pStoneAbilityInfo->setItemType(pResult->getInt(++i));
			pStoneAbilityInfo->setName(pResult->getString(++i));
			pStoneAbilityInfo->setEName(pResult->getString(++i));
			pStoneAbilityInfo->setPrice(pResult->getInt(++i));
			pStoneAbilityInfo->setVolumeType(pResult->getInt(++i));
			pStoneAbilityInfo->setWeight(pResult->getInt(++i));
			pStoneAbilityInfo->setRatio(pResult->getInt(++i));
			pStoneAbilityInfo->setDurability(pResult->getInt(++i));
			pStoneAbilityInfo->setDefenseBonus(pResult->getInt(++i));
			pStoneAbilityInfo->setProtectionBonus(pResult->getInt(++i));
			pStoneAbilityInfo->setReqAbility(pResult->getString(++i));
			pStoneAbilityInfo->setItemLevel(pResult->getInt(++i));
			pStoneAbilityInfo->setDefaultOptions(pResult->getString(++i));
			pStoneAbilityInfo->setUpgradeRatio(pResult->getInt(++i));
			pStoneAbilityInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pStoneAbilityInfo->setNextOptionRatio(pResult->getInt(++i));
			pStoneAbilityInfo->setNextItemType(pResult->getInt(++i));
			pStoneAbilityInfo->setDowngradeRatio(pResult->getInt(++i));

			addItemInfo(pStoneAbilityInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// load to creature
//--------------------------------------------------------------------------------
void StoneAbilityLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, "
			<< "OptionType, Durability, EnchantLevel FROM StoneAbilityObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, OptionType, OptionType2, Durability, Grade, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM StoneAbilityObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
								pCreature->getName().c_str() );


		while (pResult->next())
		{
			try {
				uint i = 0;

				StoneAbility* pStoneAbility = new StoneAbility();

				pStoneAbility->setItemID(pResult->getDWORD(++i));
				pStoneAbility->setObjectID(pResult->getDWORD(++i));
				pStoneAbility->setItemType(pResult->getDWORD(++i));
			
	
				if (g_pStoneAbilityInfoManager->getItemInfo(pStoneAbility->getItemType())->isUnique())
					pStoneAbility->setUnique();

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pStoneAbility->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pStoneAbility->setOptionType2(optionTypes2);


				pStoneAbility->setDurability(pResult->getInt(++i));
				pStoneAbility->setGrade(pResult->getInt(++i));
				pStoneAbility->setEnchantLevel(pResult->getInt(++i));
				pStoneAbility->setHeroOption(pResult->getInt(++i));
				pStoneAbility->setHeroOptionAttr(pResult->getInt(++i));
				pStoneAbility->setCreateType((Item::CreateType)pResult->getInt(++i));

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
				else throw UnsupportedError("Monster,NPC �κ��丮�� ������ ���� �������� �ʽ��ϴ�.");

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pStoneAbility))
						{
							pInventory->addItemEx(x, y, pStoneAbility);
						}
						else
						{
							processItemBugEx(pCreature, pStoneAbility);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pStoneAbility);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pStoneAbility);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pStoneAbility);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pStoneAbility);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pStoneAbility);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pStoneAbility);
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
										if (pBeltInventory->canAddingEx(x, y, pStoneAbility))
										{
											cout << " �߰��Ϸ�"<< endl;
											pBeltInventory->addItemEx(x, y, pStoneAbility);
										}else{
											cout << " ����"<< endl;
											processItemBugEx(pCreature, pStoneAbility);
										}
								}else{
									processItemBugEx(pCreature, pStoneAbility);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pStoneAbility);
						}
						else pStash->insert(x, y, pStoneAbility);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pStoneAbility);
						break;

					default :
						SAFE_DELETE(pStmt);	// by sigi
						throw Error("invalid storage or OwnerID must be NULL");
				}
			} catch (Error& error) {
				filelog("itemLoadError.txt", "[%s] %s,Owner:%s", getItemClassName().c_str(), error.toString().c_str(),pCreature->getName().c_str() );
				throw;
			} catch (Throwable& t) {
				filelog("itemLoadError.txt", "[%s] %s,Owner:%s", getItemClassName().c_str(), t.toString().c_str(),pCreature->getName().c_str() );
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
void StoneAbilityLoader::load(Zone* pZone) 
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
			<< " OptionType, OptionType2, Durability, EnchantLevel, HeroOption, HeroOptionAttr, ItemFlag FROM StoneAbilityObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			StoneAbility* pStoneAbility = new StoneAbility();

			pStoneAbility->setItemID(pResult->getInt(++i));
			pStoneAbility->setObjectID(pResult->getInt(++i));
			pStoneAbility->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			string optionField = pResult->getString(++i);
			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pStoneAbility->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pStoneAbility->setOptionType2(optionTypes2);

			pStoneAbility->setDurability(pResult->getInt(++i));
			pStoneAbility->setEnchantLevel(pResult->getInt(++i));
pStoneAbility->setHeroOption(pResult->getInt(++i));
pStoneAbility->setHeroOptionAttr(pResult->getInt(++i));
			pStoneAbility->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pStoneAbility);
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
void StoneAbilityLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

StoneAbilityLoader* g_pStoneAbilityLoader = NULL;
