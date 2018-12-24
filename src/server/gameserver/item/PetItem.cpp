//////////////////////////////////////////////////////////////////////////////
// Filename    : PetItem.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "PetItem.h"
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
#include "PetUtil.h"
#include "EffectHasPet.h"
#include "GamePlayer.h"
#include "CreatureUtil.h"
#include "PetTypeInfo.h"
#include "SubInventory.h"
string getDBString(const string& str);

PetItemInfoManager* g_pPetItemInfoManager = NULL;

ItemID_t PetItem::m_ItemIDRegistry = 0;
Mutex    PetItem::m_Mutex;

//////////////////////////////////////////////////////////////////////////////
// class PetItem member methods
//////////////////////////////////////////////////////////////////////////////

PetItem::PetItem()
	throw()
{
	m_ItemType = 0;
	m_pPetInfo = NULL;
}

PetItem::PetItem(ItemType_t itemType, const list<OptionType_t>& optionType)
	throw()
{
	m_ItemType = itemType;
	m_pPetInfo = NULL;

	if (!g_pItemInfoManager->isPossibleItem(getItemClass(), m_ItemType, optionType))
	{
		filelog("itembug.log", "PetItem::PetItem() : Invalid item type or option type");
		throw ("PetItem::PetItem() : Invalid item type or optionType");
	}
}

void PetItem::create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID) 
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

/*		StringStream sql;

		sql << "INSERT INTO PetItemObject "
			<< "(ItemID,  ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, ItemFlag) VALUES(" 
			<< m_ItemID << ", "
			<< m_ObjectID << ", " << m_ItemType << ", '" << ownerID << "', " 
			<<(int)storage << ", " << storageID << ", " <<(int)x << ", " <<(int)y << ", " 
			<< (int)m_CreateType << ")";

		pStmt->executeQuery(sql.toString());*/

		string optionField, optionField2;
		setOptionTypeToField( m_pPetInfo->getOptionType(), optionField );
		setOptionTypeToField( m_pPetInfo->getMixOptionType(), optionField2 );

		if ( m_pPetInfo == NULL )
		{
			pStmt->executeQuery("INSERT INTO PetItemObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, ItemFlag) "
								"VALUES (%lu, %u, %u, '%s', %u, %u, %u, %u, %u)",
								m_ItemID, m_ObjectID, m_ItemType, ownerID.c_str(), storage, storageID, x, y, m_CreateType);
		}
		else
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			pStmt->executeQuery("INSERT INTO PetItemObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, ItemFlag, "
								"PetCreatureType, PetLevel, PetExp, PetHP, PetAttr, PetAttrLevel, PetOption, FoodType, "
								"CanGamble, CanCutHead, CanAttack, LastFeedTime, EnchantSkillType, PetOption2, OptionType, OptionType2) "
								"VALUES (%lu, %u, %u, '%s', %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, '%s', %d, %u, '%s', '%s')",
								m_ItemID, m_ObjectID, m_ItemType, ownerID.c_str(), storage, storageID, x, y, m_CreateType,
								m_pPetInfo->getPetCreatureType(), m_pPetInfo->getPetLevel(), m_pPetInfo->getPetExp(), m_pPetInfo->getPetHP(), 
								m_pPetInfo->getPetAttr(), m_pPetInfo->getPetAttrLevel(),
								m_pPetInfo->getPetOption(), m_pPetInfo->getFoodType(),
								m_pPetInfo->canGamble(), m_pPetInfo->canCutHead(), m_pPetInfo->canAttack(),
								m_pPetInfo->getLastFeedTime().toDateTime().c_str(), m_pPetInfo->getEnchantSkillType(), m_pPetInfo->getPetVersionOption(), optionField.c_str(), optionField2.c_str() );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// save item
//--------------------------------------------------------------------------------
void PetItem::tinysave(const char* field) const
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery( "UPDATE PetItemObject SET %s WHERE ItemID=%ld",
								field, m_ItemID);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void PetItem::save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		string optionField, optionField2;
		setOptionTypeToField( m_pPetInfo->getOptionType(), optionField );
		setOptionTypeToField( m_pPetInfo->getMixOptionType(), optionField2 );

		if ( m_pPetInfo == NULL )
		{
			pStmt->executeQuery( "UPDATE PetItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y, m_ItemID );
		}
		else
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			pStmt->executeQuery("UPDATE PetItemObject SET ObjectID=%ld, ItemType=%d, OwnerID='%s', Storage=%d, StorageID=%ld, X=%d, Y=%d, "
								"PetCreatureType=%u, PetLevel=%u, PetAttr=%u, PetAttrLevel=%u, PetExp=%u, PetHP=%u, FoodType=%u, "
								"CanGamble=%u, CanCutHead=%u, CanAttack=%u, LastFeedTime='%s', Nickname='%s', EnchantSkillType=%d, OptionType = '%s', OptionType2 = '%s' "
								"WHERE ItemID=%ld",
									m_ObjectID, m_ItemType, ownerID.c_str(), (int)storage, storageID, (int)x, (int)y,
									m_pPetInfo->getPetCreatureType(), m_pPetInfo->getPetLevel(), m_pPetInfo->getPetAttr(), m_pPetInfo->getPetAttrLevel(),
									m_pPetInfo->getPetExp(), m_pPetInfo->getPetHP(), m_pPetInfo->getFoodType(),
									m_pPetInfo->canGamble(), m_pPetInfo->canCutHead(), m_pPetInfo->canAttack(), m_pPetInfo->getLastFeedTime().toDateTime().c_str(),
									getDBString(m_pPetInfo->getNickname()).c_str(), m_pPetInfo->getEnchantSkillType(),optionField.c_str(), optionField2.c_str(), m_ItemID );
		}


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void PetItem::savePetInfo() const
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		if ( m_pPetInfo != NULL )
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			string optionField, optionField2;
			setOptionTypeToField( m_pPetInfo->getOptionType(), optionField );
			setOptionTypeToField( m_pPetInfo->getMixOptionType(), optionField2 );

			pStmt->executeQuery("UPDATE PetItemObject SET "
								"PetCreatureType=%u, PetLevel=%u, PetAttr=%u, PetAttrLevel=%u, PetExp=%u, PetHP=%u, FoodType=%u, "
								"CanGamble=%u, CanCutHead=%u, CanAttack=%u, LastFeedTime='%s', Nickname='%s', EnchantSkillType = %d, OptionType = '%s', OptionType2 = '%s' "
								"WHERE ItemID=%ld",
									m_pPetInfo->getPetCreatureType(), m_pPetInfo->getPetLevel(), m_pPetInfo->getPetAttr(), m_pPetInfo->getPetAttrLevel(),
									m_pPetInfo->getPetExp(), m_pPetInfo->getPetHP(), m_pPetInfo->getFoodType(),
									m_pPetInfo->canGamble(), m_pPetInfo->canCutHead(), m_pPetInfo->canAttack(), m_pPetInfo->getLastFeedTime().toDateTime().c_str(),
									getDBString(m_pPetInfo->getNickname()).c_str(), m_pPetInfo->getEnchantSkillType(),optionField.c_str(), optionField2.c_str(), m_ItemID );
		}


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void PetItem::makePCItemInfo(PCItemInfo& result) const
{
	Item::makePCItemInfo(result);

	if ( m_pPetInfo != NULL )
	{
		list<OptionType_t> olist;
		list<OptionType_t> olist2;

		if ( m_pPetInfo->getPetOption() != 0 ) 
			olist.push_back(m_pPetInfo->getPetOption());

		if ( m_pPetInfo->getPetVersionOption() != 0 ) 
			olist.push_back(m_pPetInfo->getPetVersionOption());

		list<OptionType_t> optionList = m_pPetInfo->getOptionType();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		list<OptionType_t> optionList2 = m_pPetInfo->getMixOptionType();
		list<OptionType_t>::const_iterator itr2 = optionList2.begin();

		while(itr != optionList.end())
		{
		olist.push_back(*itr);
		itr++;
		}
		while(itr2 != optionList2.end())
		{
		olist2.push_back(*itr2);
		itr2++;
		}
		result.setOptionType( olist );
		result.setOptionType2( olist2 );
		result.setDurability( m_pPetInfo->getPetHP() );
		result.setEnchantLevel( m_pPetInfo->getPetAttr() );
		result.setSilver( m_pPetInfo->getPetAttrLevel() );
		result.setGrade( (m_pPetInfo->getPetHP()==0)?(m_pPetInfo->getLastFeedTime().daysTo( VSDateTime::currentDateTime() )):(-1) );
		result.setItemNum( m_pPetInfo->getPetLevel() );
		result.setMainColor( 0xffff );
		//result.setHeroOption( m_pPetInfo->getPetAttr() );
		//result.setHeroOptionAttr( m_pPetInfo->getPetVersionOption() );
	}
}

void PetItem::whenPCTake( PlayerCreature* pPC )
{
	Item::whenPCTake(pPC);
	pPC->getPetItems().push_back(this);

	if ( !pPC->isFlag( Effect::EFFECT_CLASS_HAS_PET ) )
	{
		//cout << pPC->getName() << " 에게 펫 가졌다는 이펙트 부칩니당" << endl;
		EffectHasPet* pEffect = new EffectHasPet(pPC);
		pEffect->setNextTime(600);
		pPC->setFlag( Effect::EFFECT_CLASS_HAS_PET );
		pPC->addEffect(pEffect);
	}
}

void PetItem::whenPCLost( PlayerCreature* pPC )
{
	Item::whenPCLost(pPC);

	if ( m_pPetInfo == pPC->getPetInfo() )
	{
		pPC->setPetInfo( NULL );
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
		if ( pGamePlayer != NULL ) sendPetInfo( pGamePlayer, true );
	}

	pPC->getPetItems().remove(this);
	if ( pPC->getPetItems().empty() )
	{
		//cout << pPC->getName() << " 에게서 펫 가졌다는 이펙트 떼냄니당" << endl;
		Effect* pEffect = pPC->findEffect( Effect::EFFECT_CLASS_HAS_PET );
		if ( pEffect != NULL ) pEffect->setDeadline(0);
	}
}

string PetItem::toString() const 
	throw()
{
	StringStream msg;

	msg << "PetItem("
		<< "ItemID:"    << m_ItemID
		<< ",ItemType:" <<(int)m_ItemType;

	if ( m_pPetInfo != NULL )
	{
		msg << ",PetType:" << (int)m_pPetInfo->getPetType()
			<< ",PetLevel:" << (int)m_pPetInfo->getPetLevel()
			<< ",PetExp:" << (int)m_pPetInfo->getPetExp()
			<< ",PetHP:" << (int)m_pPetInfo->getPetHP()
			<< ",PetAttr:" << (int)m_pPetInfo->getPetAttr()
			<< ",PetAttrLevel:" << (int)m_pPetInfo->getPetAttrLevel()
			<< ",PetOption:" << (int)m_pPetInfo->getPetOption()
			<< ",CanGamble:" << (int)m_pPetInfo->canGamble()
			<< ",CanAttack:" << (int)m_pPetInfo->canAttack()
			<< ",FeedTime:" << m_pPetInfo->getLastFeedTime().toString();
	}

	msg << ")";

	return msg.toString();
}

VolumeWidth_t PetItem::getVolumeWidth() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPetItemInfoManager->getItemInfo(m_ItemType)->getVolumeWidth();

	__END_CATCH
}
	
VolumeHeight_t PetItem::getVolumeHeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPetItemInfoManager->getItemInfo(m_ItemType)->getVolumeHeight();

	__END_CATCH
}
	
Weight_t PetItem::getWeight() const 
	throw(Error)
{
	__BEGIN_TRY

	return g_pPetItemInfoManager->getItemInfo(m_ItemType)->getWeight();

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// class PetItemInfo member methods
//////////////////////////////////////////////////////////////////////////////

string PetItemInfo::toString() const 
	throw()
{
	StringStream msg;
	msg << "PetItemInfo("
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

void PetItemInfoManager::load() 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT MAX(ItemType) FROM PetItemInfo");

        pResult->next();

        m_InfoCount = pResult->getInt(1);

        m_pItemInfos = new ItemInfo*[m_InfoCount+1];

        for (uint i = 0 ; i <= m_InfoCount ; i ++)
            m_pItemInfos[i] = NULL;

        pResult = pStmt->executeQuery(
			"SELECT ItemType, Name, EName, Price, Volume, Weight, Ratio FROM PetItemInfo"
		);

		while (pResult->next()) 
		{
			uint i = 0;

			PetItemInfo* pPetItemInfo = new PetItemInfo();

			pPetItemInfo->setItemType(pResult->getInt(++i));
			pPetItemInfo->setName(pResult->getString(++i));
			pPetItemInfo->setEName(pResult->getString(++i));
			pPetItemInfo->setPrice(pResult->getInt(++i));
			pPetItemInfo->setVolumeType(pResult->getInt(++i));
			pPetItemInfo->setWeight(pResult->getInt(++i));
			pPetItemInfo->setRatio(pResult->getInt(++i));

			addItemInfo(pPetItemInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class PetItemLoader member methods
//////////////////////////////////////////////////////////////////////////////

void PetItemLoader::load(Creature* pCreature) 
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

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, Num FROM PetItemObject"
			<< " WHERE OwnerID = '" << pCreature->getName() << "' AND Storage IN("
			<<(int)STORAGE_INVENTORY << ", " <<(int)STORAGE_GEAR << ", " <<(int)STORAGE_BELT << ", " 
			<<(int)STORAGE_EXTRASLOT << ", " <<(int)STORAGE_MOTORCYCLE << ", " <<(int)STORAGE_STASH << ", " 
			<<(int)STORAGE_GARBAGE << ")";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery(	"SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag, "
												"PetCreatureType, PetLevel, PetExp, PetHP, PetAttr, PetAttrLevel, PetOption, FoodType, "
												"CanGamble, CanCutHead, CanAttack, LastFeedTime, MagicExpireTime, ExpertExpireTime, Nickname, EnchantSkillType, PetOption2, OptionType, OptionType2 "
												"FROM PetItemObject WHERE OwnerID = '%s' AND Storage IN(0, 1, 2, 3, 4, 7, 9, 13)",
												pCreature->getName().c_str() );

		while (pResult->next())
		{
			try {
				uint i = 0;

				PetItem* pPetItem = new PetItem();

				Timeval currentTime;
				getCurrentTime(currentTime);

				pPetItem->setItemID(pResult->getDWORD(++i));
				pPetItem->setObjectID(pResult->getDWORD(++i));
				pPetItem->setItemType(pResult->getDWORD(++i));

				Storage storage =(Storage)pResult->getInt(++i);
				StorageID_t storageID = pResult->getDWORD(++i);
				BYTE x = pResult->getBYTE(++i);
				BYTE y = pResult->getBYTE(++i);

				pPetItem->setCreateType((Item::CreateType)pResult->getInt(++i));

				PetInfo* pPetInfo = new PetInfo;
				pPetInfo->setPetType( pPetItem->getItemType() );
				pPetInfo->setPetCreatureType( pResult->getInt(++i) );
				pPetInfo->setPetLevel( pResult->getInt(++i) );
				pPetInfo->setPetExp( pResult->getInt(++i) );
				pPetInfo->setPetHP( pResult->getInt(++i) );
				pPetInfo->setPetAttr( pResult->getInt(++i) );
				pPetInfo->setPetAttrLevel( pResult->getInt(++i) );
				pPetInfo->setPetOption( pResult->getInt(++i) );
				pPetInfo->setFoodType( pResult->getInt(++i) );
				pPetInfo->setGamble( pResult->getInt(++i) );
				pPetInfo->setCutHead( pResult->getInt(++i) );
				pPetInfo->setAttack( pResult->getInt(++i) );
				pPetInfo->setFeedTime( VSDateTime(pResult->getString(++i)) );
				cout << " 고장 지점 1 "<< endl;
				VSDateTime MagiccurrentTime = VSDateTime::currentDateTime();
				VSDateTime ExpertcurrentTime = VSDateTime::currentDateTime();

				VSDateTime MagiccurrentTimeWait = VSDateTime(pResult->getString(++i));
				VSDateTime ExpertcurrentTimeWait = VSDateTime(pResult->getString(++i));
	
				if(MagiccurrentTime > MagiccurrentTimeWait )
				{
				pPetInfo->setMagicRemainSec( 0 );
				}else{
				int diffSecs = MagiccurrentTime.secsTo( MagiccurrentTimeWait );
				pPetInfo->setMagicRemainSec( diffSecs );
				}

				if(ExpertcurrentTime > ExpertcurrentTimeWait )
				{
				pPetInfo->setExpertPetChangerRemainSec( 0 );
				}else{
				int diffSecs = ExpertcurrentTime.secsTo( ExpertcurrentTimeWait );
				pPetInfo->setExpertPetChangerRemainSec( diffSecs );
				}
				cout << " 데이터 기록표 : " << pPetInfo->getExpertPetChangerRemainSec() << "," << pPetInfo->getMagicRemainSec() << endl;

//				pPetInfo->setExpertPetChangerRemainSec( (ExpertDayTime) );
			cout << " 고장 지점 2 "<< endl;
				pPetInfo->setNickname( pResult->getString(++i) );
			cout << " 고장 지점 3 "<< endl;
				pPetInfo->setEnchantSkillType( pResult->getInt(++i) );
				pPetInfo->setPetVersionOption( pResult->getInt(++i) );


				string optionField = pResult->getString(++i);
				list<OptionType_t> optionTypes;
				setOptionTypeFromField(optionTypes, optionField);
				pPetInfo->setOptionType(optionTypes);

				string optionField2 = pResult->getString(++i);
				list<OptionType_t> optionTypes2;
				setOptionTypeFromField(optionTypes2, optionField2);
				pPetInfo->setMixOptionType(optionTypes2);

				// 양방향 링크
				pPetItem->setPetInfo( pPetInfo );
				pPetInfo->setPetItem( pPetItem );
			cout << " 고장 지점 4 "<< endl;
				uint ratio = 100;

				if ( storage == STORAGE_PET_STASH )
				{
					ratio /= 2;
					pPetInfo->setFeedTurn(2);
				}
				else
				{
//					refreshHP( pPetInfo );
					pPetInfo->setFeedTurn(1);
				}
				if ( pPetInfo->getPetLevel() == 50 ) ratio /= 10;
				refreshHP( pPetInfo, ratio );
				if  ( pPetInfo->getEnchantSkillType()  == 3) ratio /= 10;
				refreshHP( pPetInfo, ratio );
				PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo( pPetInfo->getPetType() );
				if ( pPetTypeInfo != NULL )
				{
					pPetInfo->setPetCreatureType( pPetTypeInfo->getPetCreatureType( pPetInfo->getPetLevel() ) );
				}
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

				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				switch(storage)
				{
					case STORAGE_INVENTORY:
						if (pInventory->canAddingEx(x, y, pPetItem))
						{
							pInventory->addItemEx(x, y, pPetItem);
							pPetItem->whenPCTake( pPC );
						}
						else
						{
							processItemBugEx(pCreature, pPetItem);
						}
						break;

					case STORAGE_GEAR:
						processItemBugEx(pCreature, pPetItem);
						break;

					case STORAGE_BELT :
						processItemBugEx(pCreature, pPetItem);
						break;

					case STORAGE_EXTRASLOT :
						if (pCreature->isSlayer())       pSlayer->addItemToExtraInventorySlot(pPetItem);
						else if (pCreature->isVampire()) pVampire->addItemToExtraInventorySlot(pPetItem);
						else if (pCreature->isOusters()) pOusters->addItemToExtraInventorySlot(pPetItem);

						pPetItem->whenPCTake( pPC );
						break;

					case STORAGE_MOTORCYCLE:
						processItemBugEx(pCreature, pPetItem);
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
										if (pBeltInventory->canAddingEx(x, y, pPetItem))
										{
											cout << " 추가완료"<< endl;
											pBeltInventory->addItemEx(x, y, pPetItem);
										}else{
											cout << " 버그"<< endl;
											processItemBugEx(pCreature, pPetItem);
										}
								}else{
									processItemBugEx(pCreature, pPetItem);
								}
						break;
						}
						break;

					case STORAGE_STASH:
						if (pStash->isExist(x, y))
						{
							processItemBugEx(pCreature, pPetItem);
						}
						else
						{
							pStash->insert(x, y, pPetItem);
							pPetItem->whenPCTake( pPC );
						}
						break;

					case STORAGE_GARBAGE:
						processItemBug(pCreature, pPetItem);
						break;


					case STORAGE_PET_STASH:
						/* 펫을 불러다가 pCreature에 넣어야 되나?...*/
						if ( pPC->getPetStashItem( storageID ) == NULL )
						{
							pPC->addPetStashItem( storageID, pPetItem );
							pPetItem->whenPCTake( pPC );
						}
						else
							processItemBug(pCreature, pPetItem);
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

void PetItemLoader::load(Zone* pZone) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	Statement* pStmt;

	BEGIN_DB 
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT ItemID, ObjectID, ItemType, Storage, StorageID, X, Y, ItemFlag FROM PetItemObject"
			<< " WHERE Storage = " <<(int)STORAGE_ZONE << " AND StorageID = " << pZone->getZoneID();

		Result* pResult = pStmt->executeQuery(sql.toString());

		while (pResult->next())
		{
			uint i = 0;

			PetItem* pPetItem = new PetItem();

			pPetItem->setItemID(pResult->getInt(++i));
			pPetItem->setObjectID(pResult->getInt(++i));
			pPetItem->setItemType(pResult->getInt(++i));

			Storage storage =(Storage)pResult->getInt(++i);
			StorageID_t storageID = pResult->getInt(++i);
			BYTE x = pResult->getInt(++i);
			BYTE y = pResult->getInt(++i);

			pPetItem->setCreateType((Item::CreateType)pResult->getInt(++i));

			switch(storage)
			{
				case STORAGE_ZONE :	
					{
						Tile & pTile = pZone->getTile(x,y);
						Assert(!pTile.hasItem());
						pTile.addItem(pPetItem);
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

void PetItemLoader::load(StorageID_t storageID, Inventory* pInventory) 
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

PetItemLoader* g_pPetItemLoader = NULL;
