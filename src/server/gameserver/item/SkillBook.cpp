//////////////////////////////////////////////////////////////////////////////
// Filename    : DyePotion.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SkillBook.h"
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

SkillBookInfoManager* g_pSkillBookInfoManager = NULL;

ItemID_t SkillBook::m_ItemIDRegistry = 0;
Mutex    SkillBook::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class SkillBook member methods
//////////////////////////////////////////////////////////////////////////////

SkillBook::SkillBook()
	throw()
{
	setItemType(0);
}

SkillBook::SkillBook(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num)
	throw()
{
	setItemType(itemType);
	setNum(Num);

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), getItemType(), getOptionTypeList()))
	{
		filelog("itembug.log", "SkillBook::SkillBook() : Invalid item type or option type");
		throw ("SkillBook::SkillBook() : Invalid item type or optionType");
	}
}

void SkillBook::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

		sql << "INSERT INTO SkillBookObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, Num, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << getItemType() << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)getNum() << ", " << (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void SkillBook::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE SkillBookObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void SkillBook::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE SkillBookObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, Num=%d WHERE ItemID=%ld",
								m_ObjectID, getItemType(), ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, (int)getNum(), m_ItemID );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string SkillBook::toString() const 
	throw()
{
	StringStream msg;

	msg << "SkillBook("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)getItemType()
		<< ",Num:"      <<(int)getNum()
		<< ")";

	return msg.toString();
}

/*VolumeWidth_t SkillBook::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSkillBookInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t SkillBook::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSkillBookInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t SkillBook::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pSkillBookInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}
*/
//////////////////////////////////////////////////////////////////////////////
// class SkillBookInfo member methods
//////////////////////////////////////////////////////////////////////////////

string SkillBookInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "SkillBookInfo("
		<< "ItemType:"     <<(int)m_ItemType
		<< ",Name:"        << m_Name
		<< ",EName:"       << m_EName
		<< ",Price:"       <<(int)m_Price
		<< ",VolumeType:"  << Volume2String[m_VolumeType]
		<< ",Weight:"      <<(int)m_Weight
//		<< ",Function:"      <<(int)m_fFunction
		<< ",Description:" << m_Description
		<< ")";
	return msg.toString();
}

void SkillBookInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM SkillBookInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio, ReqAbility, FunctionValue, Race FROM SkillBookInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			SkillBookInfo* pSkillBookInfo = new SkillBookInfo();

			pSkillBookInfo->setItemType(pResult->getInt(++i));
			pSkillBookInfo->setName(pResult->getString(++i));
			pSkillBookInfo->setEName(pResult->getString(++i));
			pSkillBookInfo->setPrice(pResult->getInt(++i));
			pSkillBookInfo->setVolumeType(pResult->getInt(++i));
			pSkillBookInfo->setWeight(pResult->getInt(++i));
			pSkillBookInfo->setRatio(pResult->getInt(++i));
			pSkillBookInfo->setReqAbility(pResult->getString(++i));
			pSkillBookInfo->setFunctionValue(pResult->getInt(++i));
			pSkillBookInfo->setRaceValue(pResult->getInt(++i));

			addItemInfo(pSkillBookInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class SkillBookLoader member methods
//////////////////////////////////////////////////////////////////////////////

void SkillBookLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery( "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM SkillBookObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9)",
												pCreature->getName().c_str() );

		while (pResult->next())
		{
			try {
				uint i = 0;

				SkillBook* pSkillBook = new SkillBook();

				pSkillBook->setItemID(pResult->getDWORD(++i));
				pSkillBook->setObjectID(pResult->getDWORD(++i));
				pSkillBook->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pSkillBook->setNum(pResult->getBYTE(++i));
				pSkillBook->setCreateType((Item::CreateType)pResult->getInt(++i));

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
						if (pInventory->canAddingEx(x, y, pSkillBook))
						{
							pInventory->addItemEx(x, y, pSkillBook);
						}
						else
						{
							processItemBugEx(pCreature, pSkillBook);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pSkillBook);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pSkillBook);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pSkillBook);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pSkillBook);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pSkillBook);
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pSkillBook);
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
										if (pBeltInventory->canAddingEx(x, y, pSkillBook))
										{
											cout << " 추가완료"<< endl;
											pBeltInventory->addItemEx(x, y, pSkillBook);
										}else{
											cout << " 버그"<< endl;
											processItemBugEx(pCreature, pSkillBook);
										}
								}else{
									processItemBugEx(pCreature, pSkillBook);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pSkillBook);
						}
						else pStash->insert(x, y, pSkillBook);
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pSkillBook);
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

void SkillBookLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num, ItemFlag FROM SkillBookObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			SkillBook* pSkillBook = new SkillBook();

			pSkillBook->setItemID(pResult->getInt(++i));
			pSkillBook->setObjectID(pResult->getInt(++i));
			pSkillBook->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pSkillBook->setNum(pResult->getBYTE(++i));
			pSkillBook->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pSkillBook);
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

void SkillBookLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

SkillBookLoader* g_pSkillBookLoader = NULL;
