////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRedistributeAttr.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRedistributeAttr.h"
#include "Vampire.h"
#include "Zone.h"
#include "GamePlayer.h"
#include "DB.h"
#include "VariableManager.h"
#include "StringPool.h"
#include <stdio.h>

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionRedistributeAttr::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script type
		string AttrType = propertyBuffer.getProperty("AttrType");

		if (AttrType == "STR") m_AttrType = 0;
		else if (AttrType == "DEX") m_AttrType = 1;
		else if (AttrType == "INT") m_AttrType = 2;
		else
		{
			cout << "ActionRedistributeAttr::read() : Unknown ATTR type" << endl;
			throw ("ActionRedistributeAttr::read() : Unknown ATTR type");
		}
	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionRedistributeAttr::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isVampire());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// ���� Ŭ���̾�Ʈ�� ���� GCNPCResponse�� �����ش�.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);

	Gold_t ATTR_PRICE = g_pVariableManager->getVariable( VAMPIRE_REDISTRIBUTE_ATTR_PRICE );

	// ���� ������ ���� �ʴٸ� ������.
	if (pVampire->getGold() < ATTR_PRICE) 
	{
		// ���� ��ȭâ�� �ݰ� �Ѵ�.
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&gcNPCResponse);

/*		StringStream msg;
		msg << pVampire->getName() << " ���� ����� ���� ������ ���� �ʽ��ϴ�.(" << ATTR_PRICE << " �ֵ�)"; */

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_NOT_ENOUGH_MONEY ), pVampire->getName().c_str() );

		GCSystemMessage gcSM;
		gcSM.setMessage( msg );
		pPlayer->sendPacket(&gcSM);
		return;
	}

	// ���� ������ 2��ŭ�� �ɷ�ġ�� ���ʽ� ����Ʈ�� ��ȯ�� �� �ִ�.
	// �׷��Ƿ� �̹� �� �Ѱ踦 �� ä������ �ʾҴ��� �˻��Ѵ�.
	Statement* pStmt             = NULL;
	Result*    pResult           = NULL;
	int        RedistributedAttr = 0;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT RedistributeAttr FROM Vampire WHERE Name='%s'", pVampire->getName().c_str());

		if (pResult->getRowCount() == 0)
		{
			cerr << "ActionRedistributeAttr : No Vampire Record On Table" << endl;
			throw Error("ActionRedistributeAttr : No Vampire Record On Table");
		}
		else
		{
			pResult->next();
			RedistributedAttr = pResult->getInt(1);
		}

		if (RedistributedAttr >= pVampire->getLevel())
		{
			// ���� ��ȭâ�� �ݰ� �Ѵ�.
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&gcNPCResponse);

//			StringStream msg;
//			msg << "������ŭ�� ���ʽ� ����Ʈ�� ��ȯ�� �� �ֽ��ϴ�.";

			GCSystemMessage gcSM;
			gcSM.setMessage( g_pStringPool->getString( STRID_TRANS_BONUS_POINT ) );
			pPlayer->sendPacket(&gcSM);
			SAFE_DELETE(pStmt);
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	// �ɷ�ġ�� �����ϱ⿡ �ռ� ������ �ɷ�ġ�� �����Ѵ�.
	VAMPIRE_RECORD prev;
	pVampire->getVampireRecord(prev);

	StringStream sql;
	StringStream sql2;

	// STR ��й�
	if (m_AttrType == 0)
	{
		// �������� 20���϶�� �� �̻� ��й��� ���� ����.
		if (pVampire->getSTR(ATTR_BASIC) <= 20)
		{
			// ���� ��ȭâ�� �ݰ� �Ѵ�.
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&gcNPCResponse);

//			StringStream msg;
//			msg << "STR�� 20���Ϸ� ���� ���� �����ϴ�.";

			GCSystemMessage gcSM;
			gcSM.setMessage( g_pStringPool->getString( STRID_STR_LOW_LIMIT ) );
			pPlayer->sendPacket(&gcSM);
			return;
		}

		pVampire->setSTR(pVampire->getSTR(ATTR_BASIC) - 1, ATTR_BASIC);
		sql << "STR = " << (int)pVampire->getSTR(ATTR_BASIC);
	}
	// DEX ��й�
	else if (m_AttrType == 1)
	{
		if (pVampire->getDEX(ATTR_BASIC) <= 20)
		{
			// ���� ��ȭâ�� �ݰ� �Ѵ�.
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&gcNPCResponse);

//			StringStream msg;
//			msg << "DEX�� 20���Ϸ� ���� ���� �����ϴ�.";

			GCSystemMessage gcSM;
			gcSM.setMessage( g_pStringPool->getString( STRID_DEX_LOW_LIMIT ) );
			pPlayer->sendPacket(&gcSM);
			return;
		}

		pVampire->setDEX(pVampire->getDEX(ATTR_BASIC) - 1, ATTR_BASIC);
		sql << "DEX = " << (int)pVampire->getDEX(ATTR_BASIC);
	}
	// INT ��й�
	else if (m_AttrType == 2)
	{
		if (pVampire->getINT(ATTR_BASIC) <= 20)
		{
			// ���� ��ȭâ�� �ݰ� �Ѵ�.
			GCNPCResponse gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
			pPlayer->sendPacket(&gcNPCResponse);

//			StringStream msg;
//			msg << "INT�� 20���Ϸ� ���� ���� �����ϴ�.";

			GCSystemMessage gcSM;
			gcSM.setMessage( g_pStringPool->getString( STRID_INT_LOW_LIMIT ) );
			pPlayer->sendPacket(&gcSM);
			return;
		}

		pVampire->setINT(pVampire->getINT(ATTR_BASIC) - 1, ATTR_BASIC);
		sql << "INTE = " << (int)pVampire->getINT(ATTR_BASIC);
	}
	else
	{
		Assert(false);
	}

	// �پ�� �ɷ�ġ�� ���̺��ϰ�,
	// �ɷ�ġ�� �پ�������, ���ʽ��� �ø���.
	// �׸��� ���� ���δ�.
	pVampire->tinysave(sql.toString());
	pVampire->setBonus(pVampire->getBonus() + 1);
	sql2 << "Bonus = " << (int)pVampire->getBonus();
	pVampire->tinysave(sql2.toString());
	//pVampire->setGoldEx(pVampire->getGold() - ATTR_PRICE);
	// by sigi. 2002.9.18
	pVampire->decreaseGoldEx(ATTR_PRICE);

	GCModifyInformation gcMI;
	gcMI.addShortData(MODIFY_BONUS_POINT, pVampire->getBonus());
	gcMI.addLongData(MODIFY_GOLD, pVampire->getGold());

	pVampire->initAllStat();
	pVampire->addModifyInfo(prev, gcMI);
	pVampire->sendRealWearingInfo();
	pPlayer->sendPacket(&gcMI);

	// ��ȯ�� �ɷ�ġ�� ���� �����ؾ� �Ѵ�.
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE Vampire SET RedistributeAttr = %d WHERE Name='%s'", RedistributedAttr + 1, pVampire->getName().c_str());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRedistributeAttr::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRedistributeAttr("
	    << ")";
	return msg.toString();

	__END_CATCH
}






