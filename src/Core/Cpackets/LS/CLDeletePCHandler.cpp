//////////////////////////////////////////////////////////////////////////////
// Filename    : CLDeletePCHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLDeletePC.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
	#include "ItemDestroyer.h"
	#include "Properties.h"

	#include "Lpackets/LCDeletePCOK.h"
	#include "Lpackets/LCDeletePCError.h"

	#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CLDeletePCHandler::execute (CLDeletePC* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	cout << pPacket->toString() << endl;

	LoginPlayer*    pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Statement*      pStmt        = NULL;
	Statement*      pLoginStmt   = NULL;
	Result*         pResult      = NULL;
	LCDeletePCError lcDeletePCError;
	WorldID_t		WorldID		 = pLoginPlayer->getWorldID();

	try 
	{
		pLoginStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection( WorldID )->createStatement();

		////////////////////////////////////////////////////////////
		// �ϴ� �׷� �����̾ �����ϴ��� üũ�Ѵ�.
		////////////////////////////////////////////////////////////
//		printf("SELECT Active FROM Slayer WHERE Name = '%s' AND Active='ACTIVE' AND PlayerID='%s'", pPacket->getName().c_str(), pPlayer->getID().c_str());
		pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name = '%s' AND Active='ACTIVE'", pPacket->getName().c_str());
		if (pResult->getRowCount() != 1) 
		{
			lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
			throw InvalidProtocolException("no such slayer exist.");
		}

		if ( pResult->next() )
		{
			string id = pResult->getString(1);
			if ( id != pPlayer->getID() )
			{
				filelog("DeletePC.log", "Illegal PC Delete : [%s:%s]", pPlayer->getID().c_str(), pPacket->getName().c_str());
				throw InvalidProtocolException("illegal pc delete");
			}
		}

		////////////////////////////////////////////////////////////
		// �ֹε�Ϲ�ȣ�� Ȯ���Ѵ�.
		////////////////////////////////////////////////////////////

//add by zdj 2005.5.11

//�����������

/*

#if !defined(__CHINA_SERVER__) && !defined(__THAILAND_SERVER__)
		if ( (pLoginPlayer->isFreePass() && !pLoginPlayer->isWebLogin() )
			|| g_pConfig->getPropertyInt("IsNetMarble")==1)
		{
			// ������ ���� �� �ִ�.
			pResult = pLoginStmt->executeQuery("SELECT length(Password) FROM Player Where PlayerID = '%s'", pPlayer->getID().c_str());

			if(!pResult->next())
			{
				lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
				throw InvalidProtocolException("no such slayer exist.");
			}

			int    PasswordLength = pResult->getInt(1);

			if (PasswordLength != 12) 
			{
				lcDeletePCError.setErrorID(INVALID_SSN);
				throw InvalidProtocolException("invalid SSN");
			}
		}
		else
		{
			pResult = pLoginStmt->executeQuery("SELECT SSN FROM Player Where PlayerID = '%s'", pPlayer->getID().c_str());

			if(!pResult->next())
			{
				lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
				throw InvalidProtocolException("no such slayer exist.");
			}

			string SSN = pResult->getString(1);

			cout << "DB SSN:" << SSN << endl;

			if (SSN != pPacket->getSSN())
			{
				lcDeletePCError.setErrorID(INVALID_SSN);
				throw InvalidProtocolException("invalid SSN");
			}
		}
#endif

*/ //����

		////////////////////////////////////////////////////////////
		// �ϴ� �����̾� ���̺��� Ȯ���� �����Ѵ�.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Slayer WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Slayer SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif

		if (pStmt->getAffectedRowCount() != 1) 
		{
			lcDeletePCError.setErrorID(NOT_FOUND_ID);
			throw InvalidProtocolException("no such slayer exist.");
		}

#if !defined(__CHINA_SERVER__) && !defined(__THAILAND_SERVER__) && !defined(__NETMARBLE_SERVER__)
		pLoginStmt->executeQuery("INSERT INTO DeleteChar (PlayerID, WorldID, Name, delDate) VALUES ('%s',%u,'%s',now())",
			pLoginPlayer->getID().c_str(), WorldID, pPacket->getName().c_str());
#endif

		////////////////////////////////////////////////////////////
		// �����̾� ���̺��� �����.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Vampire WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Vampire SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif
		//if (pStmt->getAffectedRowCount() == 1) //cout << "Vampire(" << pPacket->getName() << ") deleted successfully...." << endl;

		////////////////////////////////////////////////////////////
		// �ƿ콺�ͽ� ���̺��� �����.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Ousters WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Ousters SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif

#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		////////////////////////////////////////////////////////////
		// �����̾� ��ų�� �����.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM SkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());
		//cout << "Slayer(" << pPacket->getName() << ") deleted successfully...." << endl;

		////////////////////////////////////////////////////////////
		// �����̾� ��ų�� �����ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM VampireSkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// �ƿ콺���� ��ų�� �����ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM OustersSkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());
#endif

		////////////////////////////////////////////////////////////
		// ��� ���ʽ��� �����ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM RankBonusData WHERE OwnerID = '%s'", pPacket->getName().c_str() );

		////////////////////////////////////////////////////////////
		// �������� ���׸� �����.
		////////////////////////////////////////////////////////////
//		g_pItemDestroyer->destroyAll(pPacket->getName());
		string ownerID = pPacket->getName();
		pStmt->executeQuery("DELETE FROM ARObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BeltObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BladeObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BloodBibleObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BombMaterialObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BombObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CastleSymbolObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CrossObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventGiftBoxObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventStarObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventTreeObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GloveObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM HelmObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM HolyWaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM KeyObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LearningItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MagazineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MoneyObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MotorcycleObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM NecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PotionObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM QuestItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM RelicObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SMGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SRObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SerumObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShieldObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShoesObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SkullObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SlayerPortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SwordObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM TrouserObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM RingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoupleRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireAmuletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireBraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireCoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireEarringObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireNecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampirePortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireWeaponObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireCoupleRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM WaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM DyePotionObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ResurrectItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MixingItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersArmsbandObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersBootsObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersChakramObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersCircletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersCoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersPendentObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersStoneObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersWristletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LarvaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PupaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ComposMeiObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersSummonItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EffectItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CodeSheetObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MoonCardObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SweeperObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetFoodObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetEnchantItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LuckyBagObject WHERE OwnerID = '" + ownerID + "'");
#ifndef __THAILAND_SERVER__
		pStmt->executeQuery("DELETE FROM SMSItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoreZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GQuestItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GQuestSave WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM TrapItemObject WHERE OwnerID = '" + ownerID + "'");
#endif
		pStmt->executeQuery("DELETE FROM CarryingReceiverObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShoulderArmorObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM DermisObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PersonaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM FasciaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MittenObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SubInventoryObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SkillBookObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM NecklaceZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoatZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BeltZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BootZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM WeaponZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM HelmObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GloveZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShoesZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EtheRealObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM StoneAbilityObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EffectItemLoader WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CommonItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireWingItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersWingItemObject WHERE OwnerID = '" + ownerID + "'");
		////////////////////////////////////////////////////////////
		// Ŀ���� ��� Ŀ�� ��Ͽ��� �����ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM CoupleInfo WHERE FemalePartnerName='%s'",ownerID.c_str());
		pStmt->executeQuery("DELETE FROM CoupleInfo WHERE MalePartnerName='%s'",ownerID.c_str());

		////////////////////////////////////////////////////////////
		// ���� �ִ� ����Ʈ�鵵 �����.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM EffectAcidTouch where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectAftermath where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectBloodDrain where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectDetectHidden where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectFlare where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectLight where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectParalysis where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectPoison where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectPoisonousHands where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectProtectionFromParalysis where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectProtectionFromPoison where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectRestore where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectYellowPoisonToCreature where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectMute where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EnemyErase where OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// �÷��� �µ� ������ �ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM FlagSet WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// �ð����� �����۵� ������ �ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM TimeLimitItems WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// �̺�Ʈ ������ ������ �ش�.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM EventQuestAdvance WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// ���۽� �Ŀ� ����Ʈ�� ����.. ����
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM MofusPowerPoint WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// Ŭ���̾�Ʈ���� PC ���� ���� ��Ŷ�� ������.
		////////////////////////////////////////////////////////////
		LCDeletePCOK lcDeletePCOK;
		pLoginPlayer->sendPacket(&lcDeletePCOK);
	
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

		SAFE_DELETE(pStmt);
	} 
	catch (InvalidProtocolException & ipe) 
	{
		cout << "Fail to deletePC : " << ipe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pLoginStmt);

		// Ŭ���̾�Ʈ���� PC ���� ���� ��Ŷ�� ������.
		pLoginPlayer->sendPacket(&lcDeletePCError);
	} 
	catch (SQLQueryException & sqe) 
	{
		cout << "Fail to deletePC : " << sqe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pLoginStmt);

		// Ŭ���̾�Ʈ���� PC ���� ���� ��Ŷ�� ������.
		pLoginPlayer->sendPacket(&lcDeletePCError);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
