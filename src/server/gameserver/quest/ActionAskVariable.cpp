////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAskVariable.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionAskVariable.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "VariableInfo.h"
#include "VariableBuffer.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "Guild.h"
#include "GuildManager.h"
#include "WarSystem.h"
#include "VariableManager.h"
#include "MonsterInfo.h"

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "Gpackets/GCNPCAskVariable.h"
#include "StringPool.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNPCResponse.h"

#include "WarScheduler.h"
#include "WarSchedule.h"
#include "SiegeWar.h"

#include "ZoneUtil.h"

#include <stdio.h>

void convertCommaString( string& str );

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionAskVariable::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ScriptID = propertyBuffer.getPropertyInt("ScriptID");

		string buffer = propertyBuffer.getProperty("Variable");

		SAFE_DELETE( m_pVariableBuffer );

		m_pVariableBuffer = new VariableBuffer( buffer );
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionAskVariable::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature *pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	GCNPCAskVariable gcNPCAskVariable;
	gcNPCAskVariable.setObjectID(pCreature1->getObjectID());
	gcNPCAskVariable.setScriptID(m_ScriptID);

	int count = m_pVariableBuffer->getCount();
	
	for ( int i=0; i<count; i++ )
	{
		VariableInfo* pInfo = m_pVariableBuffer->getVariableInfo( i );
		
		ScriptParameter* pParam = new ScriptParameter();
		pParam->setName( pInfo->getName() );

		string keyword = pInfo->getKeyword();

		if ( keyword == "EntranceFee" )
		{
			// ����Ḧ �־��ش�.
			ZoneID_t zoneID = atoi( pInfo->getParameter(0).c_str() );

			if ( zoneID == 0 )
				throw Error("Invalid Script Variable. Keyword : EntranceFee. Invalid ZoneID");

			PlayerCreature *pPC = dynamic_cast<PlayerCreature*>(pCreature2);

			Gold_t value = g_pCastleInfoManager->getEntranceFee( zoneID, pPC );
			Race_t race	 = g_pCastleInfoManager->getCastleInfo( zoneID )->getRace();

			char strValue[20];
			// �������� ���϶� ��� ����
			// ������� ���϶� ���� �� �� �ִ� ������ ����
			if ( g_pWarSystem->hasActiveRaceWar() || g_pWarSystem->hasCastleActiveWar( zoneID ) )
			{
//				sprintf( strValue, "����" );
				sprintf( strValue, "%s", g_pStringPool->getString( STRID_FREE ).c_str() );
			}
			else if ( race == RACE_SLAYER )
			{
				char gold[15];
				sprintf( gold, "%lu", value );
				string sGold( gold );
				convertCommaString( sGold );
//				sprintf( strValue, "%s ����", sGold.c_str() );
				sprintf( strValue, "%s", (sGold + " " + g_pStringPool->getString( STRID_REI )).c_str() );
			}
			else
			{
				char gold[15];
				sprintf( gold, "%lu", value );
				string sGold( gold );
				convertCommaString( sGold );
//				sprintf( strValue, "%s �ֵ�", sGold.c_str() );
				sprintf( strValue, "%s", (sGold + " " + g_pStringPool->getString( STRID_GELD )).c_str() );
			}

			if ( g_pCastleInfoManager->isPossibleEnter( zoneID, pPC ) )
				pParam->setValue( strValue );
			else
				pParam->setValue( g_pStringPool->getString( STRID_NO_ENTER ) );
		}
		else if ( keyword == "CastleOwner" )
		{
			// �� ������ üũ�ؼ� �־��ش�.
			ZoneID_t zoneID = atoi( pInfo->getParameter(0).c_str() );

			if ( zoneID == 0 )
				throw Error("Invalid Script Variable. Keyword : CastleOwner. Invalid ZoneID");

			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( zoneID );
			string result;
			if ( pCastleInfo != NULL )
			{
				if( pCastleInfo->isCommon() )
				{
					// ���뼺�̴�.
					if( pCastleInfo->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						// �����̾� ���뼺�̴�.
//						result = "�����̾� ���뼺";
						result = g_pStringPool->getString( STRID_SLAYER_COMMON_CASTLE );
					}
					else if ( pCastleInfo->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						// �����̾� ���뼺�̴�.
//						result = "�����̾� ���뼺";
						result = g_pStringPool->getString( STRID_VAMPIRE_COMMON_CASTLE );
					}
					else
					{
//						result = "�ƿ콺���� ���뼺";
						result = g_pStringPool->getString( STRID_OUSTERS_COMMON_CASTLE );
					}
				}
				else
				{
					// ��尡 ������ ���̴�.
					Guild* pGuild = g_pGuildManager->getGuild( pCastleInfo->getGuildID() );
					if ( pGuild == NULL )
//						result = "���ξ��� ��";
						result = g_pStringPool->getString( STRID_NO_MASTER_CASTLE );
					else
//						result = pGuild->getName() + ( (pGuild->getRace() == RACE_SLAYER)?"��":"Ŭ��" ) + "�� ��";
						result = pGuild->getName() + ( (pGuild->getRace() == RACE_SLAYER)?(g_pStringPool->getString( STRID_TEAM )):(g_pStringPool->getString( STRID_CLAN )) ) + g_pStringPool->getString( STRID_S_CASTLE );
				}

				pParam->setValue( result );
			}
			else
			{
				pParam->setValue( "" );
			}
		}
		else if ( keyword == "CastleName" )
		{
			ZoneID_t zoneID = atoi( pInfo->getParameter(0).c_str() );

			if ( zoneID == 0 )
				throw Error("Invalid Script Variable. Keyword : CastleOwner. Invalid ZoneID");

			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( zoneID );
			if ( pCastleInfo != NULL )
			{
				pParam->setValue( pCastleInfo->getName() );
			}
			else
			{
				pParam->setValue( "" );
			}
		}
		else if ( keyword == "ReinforceCandidate" )
		{
			ZoneID_t zoneID = atoi( pInfo->getParameter(0).c_str() );

			Zone* pZone = getZoneByZoneID( zoneID );
			Assert( pZone != NULL );
			Assert( pZone->isCastle() );

			WarScheduler* pWarScheduler = pZone->getWarScheduler();
			Assert( pWarScheduler != NULL );

			Schedule* pNextSchedule = pWarScheduler->getRecentSchedule();

			Work* pNextWork = NULL;
			if ( pNextSchedule != NULL ) pNextWork = pNextSchedule->getWork();

			SiegeWar* pNextWar = dynamic_cast<SiegeWar*>(pNextWork);

			if ( pNextWar == NULL )
			{
				pParam->setValue( "����" );
			}
			else
			{
				GuildID_t gID = pNextWar->recentReinforceGuild();
				Guild* pGuild = g_pGuildManager->getGuild( gID );
				if ( pGuild == NULL ) pParam->setValue( "����" );
				else pParam->setValue( pGuild->getName() );

				cout << pParam->getValue() << " ����" << endl;;
			}
		}
		else if ( keyword == "RedistGold" )
		{
			Gold_t price = g_pVariableManager->getVariable( VAMPIRE_REDISTRIBUTE_ATTR_PRICE );

			char gold[15];
			sprintf( gold, "%lu", price );

			string sGold( gold );
			convertCommaString( sGold );

			pParam->setValue( sGold );
		}
		else if ( keyword == "CastleResurrectFee" )
		{
			ZoneID_t zoneID = atoi( pInfo->getParameter(0).c_str() );
		
			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( zoneID );
			if ( pCastleInfo != NULL )
			{
				Gold_t value = pCastleInfo->getEntranceFee();

				PlayerCreature *pPC = dynamic_cast<PlayerCreature*>(pCreature2);

				if ( g_pCastleInfoManager->isCastleMember( zoneID, pPC ) )
					value = 0;

				char gold[15];
				sprintf( gold, "%lu", value );
				string sGold( gold );
				convertCommaString( sGold );

				char strValue[20];
				
				if ( pCastleInfo->getRace() == RACE_SLAYER )
				{
//					sprintf( strValue, "%s ����", sGold.c_str() );
					sprintf( strValue, "%s", ( sGold + " " + g_pStringPool->getString( STRID_REI ) ).c_str() );
				}
				else if ( pCastleInfo->getRace() == RACE_VAMPIRE )
				{
//					sprintf( strValue, "%s �ֵ�", sGold.c_str() );
					sprintf( strValue, "%s", ( sGold + " " + g_pStringPool->getString( STRID_GELD ) ).c_str() );
				}
				else
				{
//					sprintf( strValue, "%s �ڵ�", sGold.c_str() );
					sprintf( strValue, "%s", ( sGold + " " + g_pStringPool->getString( STRID_ZARD ) ).c_str() );
				}

				pParam->setValue( strValue );
			}
			else
			{
				pParam->setValue( "" );
			}
		}
		else if ( keyword == "EventQuestZone" )
		{
			int questLevel = atoi( pInfo->getParameter(0).c_str() );

			if ( questLevel == 2 )
			{
				if ( pCreature2->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
					Attr_t	grade = pSlayer->getQuestGrade();

					if ( grade < 61 )
					{
//						pParam->setValue("���ϼ���");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_1 ));
					}
					else if ( grade < 96 )
					{
						pParam->setValue("������Ͼ� �ϼ�");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_2 ));
					}
					else if ( grade < 131 )
					{
						pParam->setValue("������Ͼ� �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_3 ));
					}
					else if ( grade < 171 )
					{
						pParam->setValue("������Ͼ� ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_4 ));
					}
					else if ( grade < 211 )
					{
						pParam->setValue("������Ͼ� ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_5 ));
					}
					else if ( grade < 241 )
					{
						pParam->setValue("��κ�Ÿ ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_6 ));
					}
					else if ( grade < 271 )
					{
						pParam->setValue("��κ�Ÿ ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_7 ));
					}
					else if ( grade < 291 )
					{
						pParam->setValue("Ƽ��ȣ�� ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_8 ));
					}
					else if ( grade < 301 )
					{
						pParam->setValue("Ƽ��ȣ�� ����");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_9 ));
					}
					else
					{
						pParam->setValue("��ȴ��� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_2_10 ));
					}
				}
				else if ( pCreature2->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
					Level_t level = pVampire->getLevel();

					if ( level < 11 )
					{
						pParam->setValue("���丮 ���� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_1 ));
					}
					else if ( level < 21 )
					{
						pParam->setValue("���� ����");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_2 ));
					}
					else if ( level < 31 )
					{
						pParam->setValue("���� �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_3 ));
					}
					else if ( level < 41 )
					{
						pParam->setValue("���� �ϼ�");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_4 ));
					}
					else if ( level < 51 )
					{
						pParam->setValue("Ƽ�� ȣ�� �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_5 ));
					}
					else if ( level < 61 )
					{
						pParam->setValue("�ε�� ����");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_6 ));
					}
					else if ( level < 71 )
					{
						pParam->setValue("�ε�� ����");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_7 ));
					}
					else if ( level < 81 )
					{
						pParam->setValue("���̼� ���� 1��");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_8 ));
					}
					else if ( level < 91 )
					{
						pParam->setValue("���̼� ���� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_9 ));
					}
					else
					{
						pParam->setValue("�ƴ��� ���� ����");
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_2_10 ));
					}
				}
				else if ( pCreature2->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
					Level_t level = pOusters->getLevel();

					if ( level < 11 )
					{
						pParam->setValue("�ϴϾ� ���� 1��");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_1 ));
					}
					else if ( level < 21 )
					{
						pParam->setValue("�ϴϾ� ���� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_2 ));
					}
					else if ( level < 31 )
					{
						pParam->setValue("ī��Ż�� �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_3 ));
					}
					else if ( level < 41 )
					{
						pParam->setValue("����� �ͳ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_4 ));
					}
					else if ( level < 51 )
					{
						pParam->setValue("��κ�Ÿ �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_5 ));
					}
					else if ( level < 61 )
					{
						pParam->setValue("��κ�Ÿ �ϼ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_6 ));
					}
					else if ( level < 71 )
					{
						pParam->setValue("�ε�� �ϵ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_7 ));
					}
					else if ( level < 81 )
					{
						pParam->setValue("�ε�� �ϼ�");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_8 ));
					}
					else if ( level < 91 )
					{
						pParam->setValue("�� ���� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_9 ));
					}
					else
					{
						pParam->setValue("��� ���� 2��");
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_2_10 ));
					}
				}
			}
			else if ( questLevel == 3 )
			{
				if ( pCreature2->isSlayer() )
				{
					pParam->setValue("������Ͼ� ����");
					pParam->setValue(g_pStringPool->getString( STRID_SLAYER_MINE_ENTER ));
				}
				else if ( pCreature2->isVampire() )
				{
					pParam->setValue("���� �ϵ�");
					pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_MINE_ENTER ));
				}
				else if ( pCreature2->isOusters() )
				{
					pParam->setValue("ī��Ż�� �ϵ�");
					pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_MINE_ENTER ));
				}
				else
				{
					filelog("EventBug.txt","ActionAskVariable : 3�ܰ� ����Ʈ �� ã�µ� �÷��̾ �̻��ϴ�.");
				}
			}
			else if ( questLevel == 4 )
			{
				if ( pCreature2->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
					Attr_t	grade = pSlayer->getQuestGrade();

					if ( grade < 131 )
					{
						pParam->setValue( "������Ͼ� �ϼ�" );
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_4_1 ));
					}
					else if ( grade < 211 )
					{
						pParam->setValue( "������Ͼ� ����" );
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_4_2 ));
					}
					else if ( grade < 271 )
					{
						pParam->setValue( "��κ�Ÿ ����" );
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_4_3 ));
					}
					else if ( grade < 300 )
					{
						pParam->setValue( "Ƽ�� ����" );
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_4_4 ));
					}
					else
					{
						pParam->setValue( "��� ���� 2��" );
						pParam->setValue(g_pStringPool->getString( STRID_SLAYER_QUESTZONE_4_5 ));
					}
				}
				else if ( pCreature2->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
					Level_t level = pVampire->getLevel();

					if ( level < 31 )
					{
						pParam->setValue( "���� ����" );
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_4_1 ));
					}
					else if ( level < 51 )
					{
						pParam->setValue( "���� �ϼ�" );
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_4_2 ));
					}
					else if ( level < 71 )
					{
						pParam->setValue( "��κ�Ÿ ����" );
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_4_3 ));
					}
					else if ( level < 91 )
					{
						pParam->setValue( "���̼� ���� 1��" );
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_4_4 ));
					}
					else
					{
						pParam->setValue( "���̼� ���� 2��" );
						pParam->setValue(g_pStringPool->getString( STRID_VAMPIRE_QUESTZONE_4_5 ));
					}
				}
				else if ( pCreature2->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
					Level_t level = pOusters->getLevel();

					if ( level < 31 )
					{
						pParam->setValue( "ī��Ż�� �ϵ�" );
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_4_1 ));
					}
					else if ( level < 51 )
					{
						pParam->setValue( "��κ�Ÿ �ϼ�" );
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_4_2 ));
					}
					else if ( level < 71 )
					{
						pParam->setValue( "�ε�� ����" );
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_4_3 ));
					}
					else if ( level < 91 )
					{
						pParam->setValue( "Ƽ�� ����" );
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_4_4 ));
					}
					else
					{
						pParam->setValue( "��� ���� 1��" );
						pParam->setValue(g_pStringPool->getString( STRID_OUSTERS_QUESTZONE_4_5 ));
					}
				}
				else
				{
					filelog("EventBug.txt","ActionAskVariable : 4�ܰ� ����Ʈ �� ã�µ� �÷��̾ �̻��ϴ�.");
				}
			}
			else
			{
				filelog("EventBug.txt","ActionAskVariable : ����Ʈ �� ã�µ� ����Ʈ ������ �̻��ϴ�. %d", questLevel );
				Assert( false );
			}
		}
		else if ( keyword == "EventQuestMonster" )
		{
			int questLevel = atoi( pInfo->getParameter(0).c_str() );

			if ( questLevel == 2 )
			{
				if ( pCreature2->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
					Attr_t	grade = pSlayer->getQuestGrade();

					if ( grade < 61 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIMAT));
					}
					else if ( grade < 96 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIMAT));
					}
					else if ( grade < 131 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIMAT));
					}
					else if ( grade < 171 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIMAT));
					}
					else if ( grade < 211 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIMAT));
					}
					else if ( grade < 241 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIRCON));
					}
					else if ( grade < 271 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIRCON));
					}
					else if ( grade < 291 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIRCON));
					}
					else if ( grade < 301 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIRCON));
					}
					else
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIRCON));
					}
				}
				else if ( pCreature2->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
					Level_t level = pVampire->getLevel();

					if ( level < 11 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIMAT));
					}
					else if ( level < 21 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIMAT));
					}
					else if ( level < 31 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIMAT));
					}
					else if ( level < 41 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIMAT));
					}
					else if ( level < 51 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIMAT));
					}
					else if ( level < 61 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIRCON));
					}
					else if ( level < 71 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIRCON));
					}
					else if ( level < 81 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIRCON));
					}
					else if ( level < 91 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIRCON));
					}
					else
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIRCON));
					}
				}
				else if ( pCreature2->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
					Level_t level = pOusters->getLevel();

					if ( level < 11 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIMAT));
					}
					else if ( level < 21 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIMAT));
					}
					else if ( level < 31 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIMAT));
					}
					else if ( level < 41 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIMAT));
					}
					else if ( level < 51 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIMAT));
					}
					else if ( level < 61 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_YELLOW_ZIRCON));
					}
					else if ( level < 71 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_GREEN_ZIRCON));
					}
					else if ( level < 81 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLUE_ZIRCON));
					}
					else if ( level < 91 )
					{
						pParam->setValue(g_pStringPool->getString(STRID_RED_ZIRCON));
					}
					else
					{
						pParam->setValue(g_pStringPool->getString(STRID_BLACK_ZIRCON));
					}
				}
			}
			else if ( questLevel == 5 )
			{
				if ( pCreature2->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
					Attr_t	grade = pSlayer->getQuestGrade();

					if ( grade < 131 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_1) );
					}
					else if ( grade < 211 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_2) );
					}
					else if ( grade < 271 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_3) );
					}
					else if ( grade < 301 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_4) );
					}
					else
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_5) );
					}
				}
				else if ( pCreature2->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
					Level_t level = pVampire->getLevel();

					if ( level < 31 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_1) );
					}
					else if ( level < 51 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_2) );
					}
					else if ( level < 71 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_3) );
					}
					else if ( level < 91 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_4) );
					}
					else
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_5) );
					}
				}
				else if ( pCreature2->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
					Level_t level = pOusters->getLevel();

					if ( level < 31 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_1) );
					}
					else if ( level < 51 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_2) );
					}
					else if ( level < 71 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_3) );
					}
					else if ( level < 91 )
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_4) );
					}
					else
					{
						pParam->setValue( g_pStringPool->getString(STRID_QUEST_MONSTER_5) );
					}
				}
				else
				{
					filelog("EventBug.txt","ActionAskVariable : 4�ܰ� ����Ʈ ���� ã�µ� �÷��̾ �̻��ϴ�.");
				}
			}
			else
			{
				filelog("EventBug.txt","ActionAskVariable : ����Ʈ ���� ã�µ� ����Ʈ ������ �̻��ϴ�. %d", questLevel );
				Assert( false );
			}
		}
		else if ( keyword == "ClearRankBonusFee" )
		{
		}
		else if ( keyword == "RacePetQuestTarget" )
		{
			int level=0;

			if ( pCreature2->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
				Assert( pSlayer != NULL );
				level = pSlayer->getHighestSkillDomainLevel();
			}
			else if ( pCreature2->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
				Assert( pVampire != NULL );
				level = pVampire->getLevel();
			}
			else if ( pCreature2->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
				Assert( pOusters != NULL );
				level = pOusters->getLevel();
			}

			if ( level < 40 )
			{
				GCSystemMessage gcSM;
				gcSM.setMessage("��ǰ�ȼ��޷����г�������.");
				pCreature2->getPlayer()->sendPacket( &gcSM );
				GCNPCResponse gcNPCR;
				gcNPCR.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
				pCreature2->getPlayer()->sendPacket( &gcNPCR );
				return;
			}

			pPC->initPetQuestTarget();
//			vector<MonsterType_t> mList = g_pMonsterInfoManager->getMonsterTypeBySprite( pPC->getTargetMonsterSType() );
//			if ( !mList.empty() )
//			{
				const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pPC->getTargetMonsterSType() );
				Assert( pMonsterInfo != NULL );

				pParam->setValue( pMonsterInfo->getHName() );
//			}
		}
		else if ( keyword == "UserName" )
		{
			pParam->setValue( pCreature2->getName() );
		}
		else if ( keyword == "GuildName" )
		{
			pParam->setValue( pPC->getGuildName() );
		}

		gcNPCAskVariable.addScriptParameter( pParam );
	}

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAskVariable);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionAskVariable::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionAskVariable("
	    << ",ScriptID:"  << (int)m_ScriptID
		<< ",VariableBuffer:" << m_pVariableBuffer->toString()
	    << ")";

	return msg.toString();

	__END_CATCH
}

void convertCommaString( string& str )
{
	int size = str.size();
	int l = ( size - 1 ) / 3;

	for ( int i = 0; i < l; i++ )
	{
		str.insert( size - ( (i+1) * 3 ), "," );
	}
}

