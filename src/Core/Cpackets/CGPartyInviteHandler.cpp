//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyInviteHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPartyInvite.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "Zone.h"
	#include "Party.h"
	#include "CreatureUtil.h"
	#include "GQuestManager.h"
	#include "PlayerCreature.h"

	#include "Gpackets/GCPartyInvite.h"
	#include "Gpackets/GCPartyError.h"
	#include "Gpackets/GCSystemMessage.h"

	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyInviteHandler::execute (CGPartyInvite* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	SYSTEM_ASSERT( SYSTEM_PARTY );

	ObjectID_t TargetOID = pPacket->getTargetObjectID();
	BYTE CODE = pPacket->getCode();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();

	// ��Ƽ ��� ���� ������ ���Ƴ��� �κ��̴�.
	// �輺��
	/*
	pPIIM->cancelInvite(pCreature);

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage("��Ƽ ����� ���׷� ���Ͽ� ���� �������� �ʽ��ϴ�.");
	pPlayer->sendPacket(&gcSystemMessage);

	executeError(pPacket, pPlayer, GC_PARTY_ERROR_UNKNOWN);
	return;
	*/
	/////

	Creature* pTargetCreature = NULL;
	/*
	try
	{
		pTargetCreature = pZone->getCreature(TargetOID);
	}
	catch (NoSuchElementException)
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pTargetCreature = pZone->getCreature(TargetOID);

	if (pTargetCreature==NULL)
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	// add by Coffee 2006.12.7
	if(pCreature->getObjectID() == pTargetCreature->getObjectID())
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer, GC_PARTY_ERROR_TARGET_NOT_EXIST);
		return;
	}
	// end

	// ��Ƽ�� �ʴ��� ���� PC�� �ƴϰų�, ������ �ٸ��� ���Խ�ų ���� ����.
	if (!pTargetCreature->isPC() || !isSameRace(pCreature, pTargetCreature))
	{
		pPIIM->cancelInvite(pCreature);
		executeError(pPacket, pPlayer,GC_PARTY_ERROR_RACE_DIFFER);
		return;
	}

	// Ÿ���� �÷��̾ �޾ƿ´�. 
	//PartyInviteInfo* pInfo1 = pPIIM->getInviteInfo(pCreature->getName());
	PartyInviteInfo* pInfo2 = pPIIM->getInviteInfo(pTargetCreature->getName());
	Player* pTargetPlayer = pTargetCreature->getPlayer();

	GCPartyInvite gcPartyInvite;

	// �ٸ� ����� ��Ƽ�� ���Խ�Ű���� �� ��
	if (CODE == CG_PARTY_INVITE_REQUEST)
	{
		//cout << "CODE:CG_PARTY_INVITE_REQUEST" << endl;

		// �ʴ��� ���� �̹� �ٸ� ���� �ʴ� ���̶��... 
		// A�� B�� �ʴ��Ѵ�. �� ����, B�� A�� �䱸��
		// ���޹��� ���� ���¿��� A�� �ʴ��Ѵ�. 
		// �� ��� �� �� CODE�� CG_PARTY_INVITE_REQUEST�ε�...
		// cancalInvite�ع�����, A�� B�� ������ ���ư������� �ȴ�.
		// �װ��� �����ϱ� ���� �ּ�ó���ع�����.
		// ��, ���� ������ ���� ���� �� �𸣰ڳ�... -- excel96
		/*
		if (pInfo1 != NULL)
		{
			//pPIIM->cancelInvite(pCreature);
			return;
		}
		*/

		// �ʴ���� ���� �̹� �ٸ� ��� �ʴ� ���� ���̶��...
		// �ٻڴϰ� �ʴ뿡 ���� �� ����.
		if (pInfo2 != NULL)
		{
			//cout << "pInfo2 != NULL" << endl;

			gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_BUSY);
			pPlayer->sendPacket(&gcPartyInvite);
			return;
		}

		int PartyID       = pCreature->getPartyID();
		int TargetPartyID = pTargetCreature->getPartyID();

		//cout << "Creature" << pCreature->getName() << "] PartyID = " << PartyID << endl;
		//cout << "TargetCreature" << pTargetCreature->getName() << "] PartyID = " << PartyID << endl;

		// �ʴ��� ��� �ʴ���� �� �� �ٰ� ��Ƽ�� ���ԵǾ��ִٸ� ������ ���� ����.
		if (PartyID != 0 && TargetPartyID != 0)
		{
			gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_ANOTHER_PARTY);
			pPlayer->sendPacket(&gcPartyInvite);
			return;
		}

		// �ʴ��� ���� ��Ƽ ���ڰ� �ƽ���� �ʴ��� �� ����.
		if (PartyID != 0)
		{
			if (!g_pGlobalPartyManager->canAddMember(PartyID))
			{
				gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
				gcPartyInvite.setCode(GC_PARTY_INVITE_MEMBER_FULL);
				pPlayer->sendPacket(&gcPartyInvite);
				return;
			}
		}

		// �ʴ���� ���� ��Ƽ ���ڰ� �ƽ���� �ʴ��� �� ����.
		if (TargetPartyID != 0)
		{
			if (!g_pGlobalPartyManager->canAddMember(TargetPartyID))
			{
				gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
				gcPartyInvite.setCode(GC_PARTY_INVITE_MEMBER_FULL);
				pPlayer->sendPacket(&gcPartyInvite);
				return;
			}
		}

		//cout << "Sending Packet" << endl;

		// ��Ŷ�� �����ش�.
		gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
		gcPartyInvite.setCode(GC_PARTY_INVITE_REQUEST);
		pTargetPlayer->sendPacket(&gcPartyInvite);

		//cout << "Sent gcPartyInvite" << endl;

		// �� �� �ʴ���� �����Ƿ�, �ʴ� ������ ������ �ش�.
		pPIIM->initInviteInfo(pCreature, pTargetCreature);

		//cout << "initInviteInfo OK" << endl;
	}
	// ��Ƽ ���� ��û�� ����� ��
	else if (CODE == CG_PARTY_INVITE_CANCEL)
	{
		// ���� �ʴ� �������� üũ�Ѵ�.
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			// ��Ŷ�� �غ��� �����ش�.
			gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_CANCEL);
			pTargetPlayer->sendPacket(&gcPartyInvite);

			// �ʴ븦 ��ҽ�Ų��.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	// ��Ƽ ���� ��û�� �޾Ƶ鿴�� ��
	else if (CODE == CG_PARTY_INVITE_ACCEPT)
	{
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			int PartyID       = pCreature->getPartyID();
			int TargetPartyID = pTargetCreature->getPartyID();

			// ��Ƽ�� ���� �ִ� ���� ��Ƽ�� ������ �ʴ� ���� �ʴ����� ��
			// (��Ƽ�� �������� ���� ����, ��Ƽ�� ���� �ִ� ���� �ʴ뿡 ������ ��)
			if (TargetPartyID != 0 && PartyID == 0)
			{
				// �۷ι� ��Ƽ �Ŵ����� ����� ���Ѵ�.
				if (g_pGlobalPartyManager->addPartyMember(TargetPartyID, pCreature))
				{
					// ���� ��Ƽ �Ŵ����� ����� ���Ѵ�.
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->addPartyMember(TargetPartyID, pCreature);
				}
			}
			// ��Ƽ�� �������� ���� ���� ��Ƽ�� �����ִ� ���� �ʴ����� ��
			// (��Ƽ�� �����ִ� ����, ��Ƽ�� �������� ���� ���� �ʴ뿡 ������ ��)
			// (��Ƽ�� �����ִ� ����, �ܺ����� ������ �㰡���� ��)
			else if (PartyID != 0 && TargetPartyID == 0)
			{
				// �۷ι� ��Ƽ �Ŵ����� ����� ���Ѵ�.
				if (g_pGlobalPartyManager->addPartyMember(PartyID, pTargetCreature))
				{
					// ���� ��Ƽ �Ŵ����� ����� ���Ѵ�.
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->addPartyMember(PartyID, pTargetCreature);
				}
			}
			// �� �� �� �ƹ��� ��Ƽ�� �������� ���� ��
			// (���ο� ��Ƽ�� ������ ��)
			else
			{
				// ���ο� ��Ƽ�� ����� ����Ѵ�.
				int NewPartyID = g_pGlobalPartyManager->registerParty();

				// �۷ι� ��Ƽ �Ŵ����� �۷ι� ��Ƽ�� ���ϰ�, ����� ���Ѵ�.
				g_pGlobalPartyManager->createParty(NewPartyID, pTargetCreature->getCreatureClass());
				g_pGlobalPartyManager->addPartyMember(NewPartyID, pCreature);
				g_pGlobalPartyManager->addPartyMember(NewPartyID, pTargetCreature);

				// ���� ��Ƽ �Ŵ����� ���� ��Ƽ�� ���ϰ�, ����� ���Ѵ�.
				LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
				pLocalPartyManager->createParty(NewPartyID, pTargetCreature->getCreatureClass());
				pLocalPartyManager->addPartyMember(NewPartyID, pCreature);
				pLocalPartyManager->addPartyMember(NewPartyID, pTargetCreature);

				if ( pCreature->getLevel() >= 25 && pTargetCreature->getLevel() < 25 )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
					pPC->getGQuestManager()->eventParty();
				}
				else if ( pTargetCreature->getLevel() >= 25 && pCreature->getLevel() < 25 )
				{
					PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);
					pPC->getGQuestManager()->eventParty();
				}
			}

			// ��Ƽ �ʴ밡 �������Ƿ�, ��Ƽ �ʴ� ������ �������ش�.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	// ��Ƽ ���� ��û�� �ź����� ��
	else if (CODE == CG_PARTY_INVITE_REJECT)
	{
		if (pPIIM->isInviting(pCreature, pTargetCreature))
		{
			// ��Ŷ�� ������.
			gcPartyInvite.setTargetObjectID(pCreature->getObjectID());
			gcPartyInvite.setCode(GC_PARTY_INVITE_REJECT);
			pTargetPlayer->sendPacket(&gcPartyInvite);

			// ��Ƽ �ʴ븦 �ź������Ƿ� �ʴ� ������ ���������ش�.
			pPIIM->cancelInvite(pCreature, pTargetCreature);
		}
		else
		{
			executeError(pPacket, pPlayer, GC_PARTY_ERROR_NOT_INVITING);
			return;
		}
	}
	else if (CODE == CG_PARTY_INVITE_BUSY)
	{
		gcPartyInvite.setTargetObjectID(pPacket->getTargetObjectID());
		gcPartyInvite.setCode(GC_PARTY_INVITE_BUSY);
		pPlayer->sendPacket(&gcPartyInvite);
	}
	else
	{
		throw ProtocolException("CGPartyInvite::execute() : Unknown Code");
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPartyInviteHandler::executeError (CGPartyInvite* pPacket , Player* pPlayer, BYTE ErrorCode)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GCPartyError gcPartyError;
	gcPartyError.setTargetObjectID(pPacket->getTargetObjectID());
	gcPartyError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcPartyError);

#endif

	__END_DEBUG_EX __END_CATCH
}
