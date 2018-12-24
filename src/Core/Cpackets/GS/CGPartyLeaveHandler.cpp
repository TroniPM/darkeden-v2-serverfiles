//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeaveHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyLeave.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "Zone.h"
	#include "Party.h"
	#include "PCFinder.h"

	#include "Gpackets/GCPartyLeave.h"
	#include "Gpackets/GCPartyError.h"

	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyLeaveHandler::execute (CGPartyLeave* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT( SYSTEM_PARTY );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	string TargetName = pPacket->getTargetName();

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	int PartyID = pCreature->getPartyID();
	if (PartyID == 0)
	{
		//filelog("PARTY_EXCEPTION.log", "CGPartyLeaveHandler::execute() : ��ƼID�� 0�Դϴ�. [%s]", pCreature->toString().c_str());
		throw ProtocolException();
	}

	GCPartyError gcPartyError;

	// Ÿ�� �̸��� NULL�̶�� ������ ��Ƽ�� �������� �ϴ� ���̴�.
	if (TargetName == "")
	{
		// �۷ι� ��Ƽ���� ������ �ش�.
		// 2���� ���¿��� �ٸ� �ϳ��� �߹��ߴٸ�, 
		// �� ���ο��� �۷ι� ��Ƽ�� �����ȴ�.
		// ���� ��Ƽ������ ID�� 0���� �ٲ��.
		//cout << "===== ��Ƽ�� ������ ���� �۷ι� ��Ƽ �Ŵ��� ����" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "================================================" << endl;

		g_pGlobalPartyManager->deletePartyMember(PartyID, pCreature);

		//cout << "===== ��Ƽ�� ���� ���� �۷ι� ��Ƽ �Ŵ��� ����" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "================================================" << endl;

		// ���� ��Ƽ���� �������ش�.
		LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
		Assert(pLocalPartyManager != NULL);
		pLocalPartyManager->deletePartyMember(PartyID, pCreature);
	}
	// �̸��� �ٸ��ٸ� ��Ƽ ���� �����ϴ� �ٸ� ��Ƽ���� �߹��ϰ��� �ϴ� ���̴�.
	else 
	{
		//cout << "===== �߹����� �۷ι� ��Ƽ �Ŵ��� ����" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		// �۷ι� ��Ƽ���� �������ش�.
		// 2���� ���¿��� �ٸ� �ϳ��� �߹��ߴٸ�, 
		// �� ���ο��� �۷ι� ��Ƽ�� �����ȴ�.
		// ���� ��Ƽ������ ID�� 0���� �ٲ��.
		g_pGlobalPartyManager->expelPartyMember(PartyID, pCreature, TargetName);

		//cout << "===== �߹����� �۷ι� ��Ƽ �Ŵ��� ����" << endl;
		//cout << g_pGlobalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		// ���� ���� ���� ��Ƽ���� �������ش�.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(TargetName);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2	
		if (pTargetCreature==NULL)
		{
			g_pPCFinder->unlock();
			return;
		}

		Zone* pTargetZone = pTargetCreature->getZone();
		Assert(pTargetZone != NULL);
		LocalPartyManager* pLocalPartyManager = pTargetZone->getLocalPartyManager();
		Assert(pLocalPartyManager != NULL);

		//cout << "===== �߹� ���� ���� ��Ƽ �Ŵ��� ����" << endl;
		//cout << pLocalPartyManager->toString() << endl;
		//cout << "=======================================" << endl;

		pLocalPartyManager->deletePartyMember(PartyID, pTargetCreature);
		//cout << "���� ��Ƽ���� �߹���� �÷��̾ �����߽��ϴ�." << endl;

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

