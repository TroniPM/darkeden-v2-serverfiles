#include "VariableManager.h"
#include "DB.h"
#include "Properties.h"
#include "SystemAvailabilitiesManager.h"
#include <stdlib.h>

extern void strlwr(char* str);

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
VariableManager::VariableManager()
	throw(Error)
{
	__BEGIN_TRY

	m_Variables.resize(VARIABLE_MAX);

	m_Variables[STAR_RATIO] = 1000;
	m_Variables[EVENT_ACTIVE] = 1;
	m_Variables[EVENT_RATIO] = 1000;
    m_Variables[ITEM_PROBE_RATIO] = 1;
	m_Variables[EXP_RATIO] = 1;
	m_Variables[COMBAT_BONUS_TIME] = 30;	// 30��
	m_Variables[COMBAT_SLAYER_HP_BONUS_RATIO] = 0;
	m_Variables[COMBAT_VAMPIRE_HP_BONUS_RATIO] = 0;
	m_Variables[COMBAT_SLAYER_DAMAGE_BONUS]= 0;
	m_Variables[COMBAT_VAMPIRE_DAMAGE_BONUS]= 0;
	m_Variables[PREMIUM_EXP_BONUS_PERCENT] = 150; // 150%
	m_Variables[PREMIUM_ITEM_PROBE_PERCENT] = 220; // 220%
	m_Variables[ZONE_GROUP_BALANCING_MINUTE] = 4*7*24*60; // 4����
	m_Variables[GAMBLE_ITEM_TYPE_RATIO] = 100;	// 100%
	m_Variables[GAMBLE_ITEM_OPTION_RATIO] = 100;	// 100%
	m_Variables[SUMMON_MOTORCYCLE] = 0;
	m_Variables[ENEMY_LIMIT_TIME] = 300; // 5�� 
	m_Variables[RARE_ITEM_RATIO] = 100; // 100%
	m_Variables[UNIQUE_ITEM_RATIO] = 100; // 100%
	m_Variables[ACTIVE_MASTER_LAIR] = 0;
	m_Variables[RETRY_MASTER_LAIR] = 0;
	m_Variables[HARVEST_FESTIVAL_ITEM_RATIO] = 100;	// 100%

	// [������ ���� ���]
	// HP�� 70% �̻��϶��� �������� �ʰ�
	// HP�� 70%�϶� 10%�� Ȯ���� �����ϰ�
	//      50%     20%
	// HP�� 30%�϶� 30%�� Ȯ���� �����Ѵ�.
	// HP�� 30%�����϶��� 30%�� Ȯ���� �����Ѵ�.
	m_Variables[MASTER_BLOOD_DRAIN_START_HP] 	= 70;
	m_Variables[MASTER_BLOOD_DRAIN_START_BD] 	= 10;
	m_Variables[MASTER_BLOOD_DRAIN_END_HP] 	= 30;
	m_Variables[MASTER_BLOOD_DRAIN_END_BD] 	= 30;

	m_Variables[ACTIVE_CHIEF_MONSTER] = 0;
	m_Variables[CHIEF_MONSTER_RARE_ITEM_RATIO] = 0;

	m_Variables[NEWBIE_TRANSPORT_TO_GUILD] = 1;

	// 2002.11.19
	m_Variables[FREE_PLAY_SLAYER_DOMAIN_SUM] = 30;
	m_Variables[FREE_PLAY_VAMPIRE_LEVEL] = 30;

	// 2002.12.10
	m_Variables[LOG_INCOMING_CONNECTION] = false;

	// 2002.12.11
	m_Variables[CHRISTMAS_FIRE_CRACKER_RATIO] = 0;
	m_Variables[CHRISTMAS_TREE_PART_RATIO] = 0;

	// 2002.12.12
	m_Variables[CHRISTMAS_GIFT_BOX_RATIO] = 0;

	// 2002.12.17
	m_Variables[CHRISTMAS_TREE_DECAY_TIME] = 6*60*60*10;

	// 2002.12.31
	m_Variables[MASTER_LAIR_PLAYER_NUM] = 15;
	m_Variables[RANK_EXP_GAIN_PERCENT] 	= 100;	// 100�̸� ���� �״��
	m_Variables[ITEM_LUCK_PERCENT] 		= 100;	// 200�̸� �ι�(200%)��� �ǹ̴�.

	// ��� �̺�Ʈ �� ( code name : lotto event )
	// 2003. 1. 12 by bezz. Sequoia. dew
	m_Variables[LOTTO_ITEM_RATIO]		= 0;
	m_Variables[LOTTO_ITEM_BONUS_NUM]	= 0;
	m_Variables[LOTTO_SKULL_RATIO]		= 0;
	m_Variables[PREMIUM_HALF_EVENT]		= false;

	// 2003. 1. 20 by bezz, Sequoia
	m_Variables[COMMON_CASTLE_ENTRANCE_FEE]	= 1000;
	m_Variables[GUILD_CASTLE_ENTRANCE_FEE] = 10000;

	m_Variables[COMMON_CASTLE_ITEM_TAX_RATIO] = 110;
	m_Variables[GUILD_CASTLE_ITEM_TAX_RATIO] = 150;
	m_Variables[WAR_REGISTRATION_FEE] 	= 50000000;

	m_Variables[GUILD_WAR_TIME] 	= 1*60*60;	// 1�ð�
	m_Variables[RACE_WAR_TIME] 		= 3*60*60;	// 3�ð�

	m_Variables[WAR_PERIOD_WEEK] 	= true;		// ������ �� �� ������ �ֱ⸦ ������.

	m_Variables[WAR_ACTIVE] 		= false;	// ���� ����� �۵����� �ʴ´�.

	m_Variables[RACE_WAR_TIMEBAND]	= 2;		// ���� ����� �ð�

	m_Variables[AUTO_START_RACE_WAR]= false;	// ���� ������ �ڵ����� �����ϴ°�?

	m_Variables[ACTIVATE_COUPLE] = false;	// Ŀ���� ����� �� �ִ� �Ⱓ�ΰ�?

	m_Variables[ACTIVE_RACE_WAR_LIMITER] = true;	// ���� ���� ���� �ο� ����

	m_Variables[CHIEF_ITEM_BONUS_NUM] = 0;		// ġ�� ���� �߰� ������ ����

	m_Variables[ACTIVE_EVENT_GIVE_ITEM] = false;		// ������ �ִ� �̺�Ʈ

	m_Variables[VAMPIRE_REDISTRIBUTE_ATTR_PRICE] = 1000000;	// �ɷ�ġ ��й� ���

	m_Variables[ACTIVATE_COUPLE] = true;		// Ŀ�� ���

	m_Variables[CAN_RECOUPLE] = false;			// ��ȥ(?) �̶�⺸�� ��??Ŀ���� �� �� �ִ°�

	m_Variables[GUILD_WAR_ACTIVE] = false;		// ������� �ϴ°�?

	m_Variables[FREE_PLAY_OUSTERS_LEVEL] = 30;	// �ƿ콺�ͽ��� ����� �÷����� �� �ִ� ����

	m_Variables[CAN_APPLY_QUEST] = true;	// ����Ʈ�� ��û�� �� �ִ°�
	m_Variables[SEND_QUEST_INFO] = false;	// ����Ʈ ������ ������� �ϴ°�
	m_Variables[CAN_BUY_SHOP] = true;

	m_Variables[PCROOM_EXP_BONUS] = 100;
	m_Variables[PCROOM_ITEM_RATIO_BONUS] = 100;

	m_Variables[MONEY_TRACE_LOG_LIMIT] = 5000000;

	m_Variables[PC_ROOM_LOTTO_EVENT] = false;	// �ǽù� ���� �̺�Ʈ ����
	m_Variables[ACTIVE_FLAG_WAR] = false;	// ��߻��� ���� ����

	m_Variables[KILL_DAEMONCTL] = false;	// daemonctl2 ���̴� �� ����
	m_Variables[EVENT_MOON_CARD] = false;	// daemonctl2 ���̴� �� ����

	m_Variables[FULL_MOON_CARD_RATIO] = 3000;
	m_Variables[HALF_MOON_CARD_RATIO] = 100;
	m_Variables[NEW_MOON_CARD_RATIO] = 200;
	m_Variables[OLD_MOON_CARD_RATIO] = 1000;

	m_Variables[ACTIVE_LEVEL_WAR] = 1000;
	m_Variables[RACE_WAR_HP_BONUS] = 0;
	m_Variables[HEAD_COUNT] = 0;

	m_Variables[HEAD_PRICE_BONUS] = 100;

	m_Variables[LEVEL_WAR_ZONE_FREE_ENTER] = false;
	m_Variables[PET_EXP_RATIO] = 100;

	m_Variables[EVENT_LUCKY_BAG] = false;
	m_Variables[GREEN_LUCKY_BAG_RATIO] = 150;
	m_Variables[BLUE_LUCKY_BAG_RATIO] = 1000;
	m_Variables[GOLD_LUCKY_BAG_RATIO] = 5000;
	m_Variables[RED_LUCKY_BAG_RATIO] = 20000;

	m_Variables[EVENT_GIFT_BOX] = false;
	m_Variables[RED_GIFT_BOX_RATIO] = 10000;
	m_Variables[BLUE_GIFT_BOX_RATIO] = 10000;
	m_Variables[GREEN_GIFT_BOX_RATIO] = 10000;
	m_Variables[YELLOW_GIFT_BOX_RATIO] = 10000;

	m_Variables[NETMARBLE_CARD_RATIO] = 0;
	m_Variables[NETMARBLE_CARD_EVENT] = 0;

	m_Variables[PET_FOOD_EVENT] = 0;

	m_Variables[HIGHER_PET_FOOD_RATIO] = 30;

	m_Variables[PET_FOOD_RATIO] = 125;
	m_Variables[RACE_PET_FOOD_RATIO] = 30;

	m_Variables[SLAYER_HP_RATIO] = 100;
	m_Variables[VAMPIRE_HP_RATIO] = 100;
	m_Variables[OUSTERS_HP_RATIO] = 100;
	m_Variables[MONSTER_HP_RATIO] = 100;
	m_Variables[MONSTER_EXP_RATIO] = 100;

	m_Variables[CLOVER_EVENT] = 0;
	m_Variables[CLOVER_RATIO] = 0;

	m_Variables[MONSTER_DAMAGE_RATIO] = 100;
	m_Variables[RACE_PET_QUEST] = 0;

	m_Variables[NICKNAME_PEN_EVENT] = 0;
	m_Variables[NICKNAME_PEN_RATIO] = 0;
	m_Variables[GOLD_MEDAL_RATIO] = 0;
	m_Variables[PET_DAY_EVENT] = 0;

	m_Variables[OLYMPIC_ITEM_RATIO] = 0;
	m_Variables[OLYMPIC_EVENT] = 0;

	m_Variables[CROWN_PRICE] = 0;
	m_Variables[CHOBO_EVENT] = 0;

	m_Variables[QUIT_GUILD_PENALTY_TERM] = 0;
	m_Variables[GUILD_UNION_MAX] = 0;

	m_Variables[LUCK_CHARM_RATIO] = 0;
	m_Variables[GDR_LAIR_PC_LIMIT] = 36;

	m_Variables[DONATION_EVENT_200501] = 0;

	m_Variables[EVENT_NEW_YEAR_2005] = 0;
	m_Variables[BOKJORY_RATIO] = 80000;
	m_Variables[EVENT_RED_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_GREEN_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_BLUE_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_BLACK_RICE_CAKE_SOUP_RATIO] = 80000;
	m_Variables[EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO] = 80000;

	m_Variables[TIME_PERIOD_EXP_2X] = 0;
	m_Variables[ZONE_RANK_EXP] = 0;
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
	m_fRemoveAllGame = false;
	m_fEggDummyDB    = false;

#endif
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
VariableManager::~VariableManager() 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void VariableManager::init()
	throw(Error)
{
	__BEGIN_TRY

	m_VariableNames.clear();

	for (int i=0; i<VARIABLE_MAX; i++)
	{
		char str[256];
		strcpy(str, VariableType2String[i].c_str());
		strlwr(str);
		m_VariableNames[str] = (VariableType)i;
	}

	load();

	// Ư���� �ٸ� �ʱⰪ�� �����ϴ� ���
	setVariable( AUTO_START_RACE_WAR, g_pConfig->getPropertyInt("ActiveRaceWar") );
	setVariable( GUILD_WAR_ACTIVE, g_pConfig->getPropertyInt("ActiveGuildWar") );
	setVariable( ACTIVE_FLAG_WAR, g_pConfig->getPropertyInt("ActiveFlagWar") );
	setVariable( ACTIVE_LEVEL_WAR, g_pConfig->getPropertyInt("ActiveLevelWar") );
	setVariable( HEAD_COUNT, g_pConfig->getPropertyInt("HeadCount") );
	setVariable( KILL_DAEMONCTL, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_HOLY_LAND_WAR ) )
		setVariable( WAR_ACTIVE, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_GUILD_WAR ) )
		setVariable( GUILD_WAR_ACTIVE, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_RACE_WAR ) )
		setVariable( AUTO_START_RACE_WAR, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_FLAG_WAR ) )
		setVariable( ACTIVE_FLAG_WAR, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_MASTER_LAIR ) )
		setVariable( ACTIVE_MASTER_LAIR, 0 );

	__END_CATCH
}


void VariableManager::load()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(attrID) FROM AttrInfo");

		if (pResult->getRowCount() <= 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("VariableManager::load(): attrID MAX���� ���� �� �����ϴ�.");
		}

		pResult->next();
		int maxAttr = pResult->getInt(1);
		m_Variables.clear();
		m_Variables.resize( max((maxAttr+1), (int)VARIABLE_MAX) );

		pResult = pStmt->executeQuery("SELECT attrID, attr1, attr2 FROM AttrInfo");

		if(pResult->getRowCount() <= 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("VariableManager::load(): ���� �ϳ��� �������� �ʽ��ϴ�");
		}

		while(pResult->next())
		{
			VariableType    attrID = (VariableType)pResult->getInt(1);
			int    			attr1  = pResult->getInt(2);
			//int    			attr2  = pResult->getInt(3);


			setVariable(attrID, attr1);
			cout << toString(attrID).c_str() << endl;
		}
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

VariableType     
VariableManager::getVariableType(const string& variableName) const
{
	char str[256];
	strcpy(str, variableName.c_str());
	strlwr(str);

	VARIABLE_NAME::const_iterator itr = m_VariableNames.find( str );

	if (itr==m_VariableNames.end())
	{
		return VARIABLE_MAX;
	}

	return itr->second;
}

void 
VariableManager::setVariable(VariableType vt, const string& strVariable)
{
	int value = atoi(strVariable.c_str());

	if (value==0)
	{
		if (strcasecmp(strVariable.c_str(), "on")==0)
		{
			setVariable(vt, 1);
		}
		else if (strcasecmp(strVariable.c_str(), "off")==0)
		{
			setVariable(vt, 0);
		}
		else
		{
			setVariable(vt, 0);
		}
	}
	else
	{
		setVariable(vt, value);
	}
}

void 
VariableManager::setVariable(VariableType vt, int value)
{ 
	try {

		// RACE_WAR_TIMEBAND ���� üũ
		if ( vt == RACE_WAR_TIMEBAND )
		{
			if ( value < 0 || value > 3 )
				return;
		}

		m_Variables[vt] = value; 

		Statement* pStmt = NULL;
		//Result*    pResult = NULL;
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("UPDATE AttrInfo SET attr1=%d WHERE attrID=%d", value, (int)vt);

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
		
	} catch (Throwable& t){
		filelog("variableManagerError.log", "%s", t.toString().c_str());
	}
}

string   
VariableManager::toString(VariableType vt) const
{
	StringStream msg;

	int attr1 = m_Variables[vt];

	switch (vt)
	{
		case EVENT_ACTIVE:
			msg << "Event�߻�����: " << attr1;
			break;
		case EVENT_RATIO:
			msg << "Event�߻���: " << attr1;
			break;
		case ITEM_PROBE_RATIO:
			msg << "Item�߰��߻�Ȯ��:  " << attr1;
			break;
		case EXP_RATIO:
			msg << "����ġ �߰� �߻�Ȯ��: " << attr1;
			break;
		case COMBAT_BONUS_TIME:
			msg << "���� �¸� �����ð�: " << attr1;
			break;

		case COMBAT_SLAYER_HP_BONUS_RATIO:
			msg << "�����̾� ���� HP ��?ʽ? " << attr1;
			break;

		case COMBAT_VAMPIRE_HP_BONUS_RATIO:
			msg << "�����̾� ���� HP ���ʽ�: " << attr1;
			break;

		case PREMIUM_EXP_BONUS_PERCENT:
			msg << "�����̾� ������� ����ġ ���ʽ�: " << attr1;
			break;

		case PREMIUM_ITEM_PROBE_PERCENT:
			msg << "�����̾� ���� ������ ���� Ȯ��: " << attr1;
			break;

		case ZONE_GROUP_BALANCING_MINUTE:
			msg << "ZoneGroupBalancing �ð� �ֱ�: " << attr1 << "��";
			break;

		case GAMBLE_ITEM_TYPE_RATIO:
			msg << "���� ItemType Ȯ��: " << attr1;
			break;

		case GAMBLE_ITEM_OPTION_RATIO:
			msg << "���� ItemOption Ȯ��: " << attr1;
			break;

		case SUMMON_MOTORCYCLE:
			msg << "������� ��ȯ���: " << (attr1? "ON":"OFF");
			break;

		case ENEMY_LIMIT_TIME:
			msg << "���� ���� �� ���� �ð�: " << attr1 << "��"; 
			break;

		case COMBAT_SLAYER_DAMAGE_BONUS:
			msg << "�����̾� ���� Damage ���ʽ�: " << attr1;
			break;

		case COMBAT_VAMPIRE_DAMAGE_BONUS:
			msg << "�����̾� ���� Damage ���ʽ�: " << attr1;
			break;

		case RARE_ITEM_RATIO:
			msg << "���� ������ ���� Ȯ��: " << attr1;
			break;

		case UNIQUE_ITEM_RATIO:
			msg << "����ũ ������ ���� Ȯ��: " << attr1; 
			break;

		case ACTIVE_MASTER_LAIR:
			msg << "������ ���� �۵�: " << (attr1? "ON":"OFF");
			break;

		case RETRY_MASTER_LAIR:
			msg << "������ ��� �װ� �ٽ� ����: " << (attr1? "ON":"OFF");
			break;


		case HARVEST_FESTIVAL_ITEM_RATIO:
			if (attr1==0)
			{
				msg << "�߼� ���� ������ Ȯ�� : 0";
			}
			else
			{
				msg << "�߼� ���� ������ Ȯ�� : 1/" << attr1;
			}
			break;

		case MASTER_BLOOD_DRAIN_START_HP:
			msg << "������ ���� ���� HP : " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_START_BD:
			msg << "������ ���� ���� BD : " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_END_HP:
			msg << "������ ���� �� HP : " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_END_BD:
			msg << "������ ���� �� BD : " << attr1 << "%";
			break;

		case ACTIVE_CHIEF_MONSTER:
			msg << "ġ�� ���� ���� " << (attr1? "ON":"OFF");
			break;
		case CHIEF_MONSTER_RARE_ITEM_RATIO:
			msg << "ġ�� ���� ���� ������ ���� Ȯ�� : " << attr1 << "%";
			break;

		case NEWBIE_TRANSPORT_TO_GUILD:
			msg << "�ɷ�ġ 40�� �ֵ� ���� �̵� : " << (attr1? "ON":"OFF");
			break;

		case FREE_PLAY_SLAYER_DOMAIN_SUM:
			msg << "�����̾� ���� ��� ���� �����η�����: " << attr1;
			break;

		case FREE_PLAY_VAMPIRE_LEVEL:
			msg << "�����̾� ���� ��� ���� ����: " << attr1;
			break;

		case LOG_INCOMING_CONNECTION:
			msg << "IncomingConnection���õ� Log: " << (attr1? "ON":"OFF");
			break;

		case CHRISTMAS_FIRE_CRACKER_RATIO:
			msg << "ũ�������� ���� ���� Ȯ�� : " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_TREE_PART_RATIO:
			msg << "ũ�������� Ʈ�� ���� ���� Ȯ�� : " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_GIFT_BOX_RATIO :
			msg << "ũ�������� ���� ���� ���� Ȯ��: " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_TREE_DECAY_TIME :
			msg << "ũ�������� Ʈ�� ���� �ð�: " << attr1/600 << "��";
			break;

		case MASTER_LAIR_PLAYER_NUM :
			msg << "������ ���� ���� ���� �ο� ��: " << attr1 << "��";
			break;

		case RANK_EXP_GAIN_PERCENT :
			msg << "��� ����ġ�� �⺻ ����ġ�� " << attr1 << "%";
			break;

		case ITEM_LUCK_PERCENT :
			msg << "Luck ���ʽ��� �⺻ Ȯ���� " << attr1 << "%";
			break;

		case LOTTO_ITEM_RATIO :
			msg << "��� ������ Ȯ�� : " << attr1 << " / 10000";
			break;

		case LOTTO_ITEM_BONUS_NUM:
			msg << "��� ������ �߰� ������ ���� : " << attr1;
			break;

		case LOTTO_SKULL_RATIO :
			msg << "��� �ذ� Ȯ�� : " << attr1 << " / 10000";
			break;

		case PREMIUM_HALF_EVENT :
			msg << "���� ����� ����, ��û �ݰ� �̺�Ʈ : " << (attr1?"ON":"OFF");
			break;

		case COMMON_CASTLE_ENTRANCE_FEE :
			msg << "���뼺 ����� : " << attr1;
			break;

		case GUILD_CASTLE_ENTRANCE_FEE :
			msg << "��强 ����� : " << attr1;
			break;

		case COMMON_CASTLE_ITEM_TAX_RATIO :
			msg << "����??������ ���� : " << attr1;
			break;

		case GUILD_CASTLE_ITEM_TAX_RATIO :
			msg << "��强 ������ ���� : " << attr1;
			break;

		case WAR_REGISTRATION_FEE :
			msg << "���� ��û�� : " << attr1;
			break;

		case GUILD_WAR_TIME :
			msg << "��� ���� �ð� : " << attr1 << " �� == " << attr1/60 << "��";
			break;

		case RACE_WAR_TIME :
			msg << "���� ���� �ð� : " << attr1 << " �� == " << attr1/60 << "��";
			break;

		case WAR_PERIOD_WEEK :
			msg << "�����ֱ� : " << (attr1? "�� ����":"�� ����");
			break;

		case WAR_ACTIVE :
			msg << "�ƴ��� ���� ���� ��� : " << (attr1?"ON":"OFF");
			break;

		case RACE_WAR_TIMEBAND:
			msg << "���� ����� Timeband : ";
			if ( attr1 == 0 )
				msg << "����";
			else if ( attr1 == 1 )
				msg << "��";
			else if ( attr1 == 2 )
				msg << "����";
			else if ( attr1 == 3 )
				msg << "��";
			else
				msg << "�� �� ����";
			break;

		case AUTO_START_RACE_WAR:
			msg << "���� ���� �ڵ� ���� ���: " << (attr1?"ON":"OFF");
			break;

		case ACTIVE_RACE_WAR_LIMITER :
			msg << "���� ���� ���� �ο� ����: " << (attr1?"ON":"OFF");
			break;

		case CHIEF_ITEM_BONUS_NUM:
			msg << "ġ�� ���� �߰� ������ ����: " << attr1 << " ��";
			break;

		case ACTIVE_EVENT_GIVE_ITEM :
			msg << "������ �ִ� �̺�Ʈ: " << (attr1?"ON":"OFF");
			break;

		case VAMPIRE_REDISTRIBUTE_ATTR_PRICE:
			msg << "�����̾� �ɷ�ġ ��й� ���: " << attr1;
			break;

		case ACTIVATE_COUPLE:
			msg << "Ŀ�� ���� ���: " << (attr1?"ON":"OFF");
			break;

		case CAN_RECOUPLE:
			msg << "����� �� �ִ� ����� �� Ŀ���� �� �� �ִ°�: " << (attr1?"Y":"N");
			break;

		case GUILD_WAR_ACTIVE:
			msg << "��� ������ �ϴ°�?: " << (attr1?"Yes":"No");
			break;

		case FREE_PLAY_OUSTERS_LEVEL:
			msg << "�ƿ콺�ͽ� ���� ��� ���� ����: " << attr1;
			break;

		case CAN_APPLY_QUEST:
			msg << "����Ʈ�� ��û�� �� �ִ°�?: " << (attr1?"Yes":"No");
			break;

		case SEND_QUEST_INFO:
			msg << "����Ʈ ������ ������� �ϴ°�?: " << (attr1?"Yes":"No");
			break;

		case CAN_BUY_SHOP:
			msg << "������ ���� ����� �����ִ°�: " << (attr1?"Yes":"No");
			break;
		case PCROOM_EXP_BONUS:
			msg << "PC�� ����ġ ���ʽ�: " << attr1;
			break;
		case PCROOM_ITEM_RATIO_BONUS:
			msg << "PC�� ������ ȹ�� Ȯ�� ���ʽ�: " << attr1;
			break;
		case MONEY_TRACE_LOG_LIMIT:
			msg << "�� �α� ����� �ּ� �ݾ�: " << attr1;
			break;
		case PC_ROOM_LOTTO_EVENT:
			msg << "�Ǿ��� ���� �̺�Ʈ: " << attr1;
			break;
		case ACTIVE_FLAG_WAR:
			msg << "��߻��� ���� ����: " << (attr1?"yes":"no");
			break;
		case KILL_DAEMONCTL:
			msg << "DAEMONCTL ���̴� ����: " << (attr1?"yes":"no");
			break;

		case EVENT_MOON_CARD:
			if ( attr1 )
				msg << "��ī�� �̺�Ʈ�� �������Դϴ�.";
			else
				msg << "��ī�� �̺�Ʈ�� �ߴ��߽��ϴ�.";
			break;

		case FULL_MOON_CARD_RATIO:
			msg << "������ ī�� ���� Ȯ��: 1 / " << attr1;
			break;

		case HALF_MOON_CARD_RATIO:
			msg << "�ݴ� ī�� ���� Ȯ��: 1 / " << attr1;
			break;

		case NEW_MOON_CARD_RATIO:
			msg << "�ʽ´� ī�� ���� Ȯ��: 1 / " << attr1;
			break;

		case OLD_MOON_CARD_RATIO:
			msg << "�׹ʴ�(����) ī�� ���� Ȯ��: 1 / " << attr1;
			break;

		case ACTIVE_LEVEL_WAR:
			msg << "������ ���� ���� ����: " << (attr1?"yes":"no");
			break;

		case RACE_WAR_HP_BONUS:
			msg << "�������� HP ���ʽ�: " << attr1;
			break;

		case HEAD_COUNT:
			msg << "�Ӹ� ���� ī��Ʈ�ϱ�: " << (attr1?"yes":"no");
			break;

		case HEAD_PRICE_BONUS:
			msg << "�Ӹ� ���� ���ʽ� : " << attr1;
			break;

		case LEVEL_WAR_ZONE_FREE_ENTER:
			msg << "������ ���� ���� �����Ӱ� �� �� �ִ°�? : " << (attr1?"yes":"no");
			break;

		case PET_EXP_RATIO:
			msg << "�� ����ġ ���� : " << attr1;
			break;

		case EVENT_LUCKY_BAG:
			if ( attr1 )
				msg << "���ָӴ� �̺�Ʈ�� �������Դϴ�.";
			else
				msg << "���ָӴ� �̺�Ʈ�� ���������� �ʽ��ϴ�.";
			break;

		case GREEN_LUCKY_BAG_RATIO:
			msg << "�ʷϻ� ���ָӴ� ���� Ȯ�� : 1 / " << attr1;
			break;

		case BLUE_LUCKY_BAG_RATIO:
			msg << "�Ķ��� ���ָӴ� ���� Ȯ�� : 1 / " << attr1;
			break;

		case GOLD_LUCKY_BAG_RATIO:
			msg << "Ȳ�ݻ� ���ָӴ� ���� Ȯ�� : 1 / " << attr1;
			break;

		case RED_LUCKY_BAG_RATIO:
			msg << "������ ���ָӴ� ���� Ȯ�� : 1 / " << attr1;
			break;

		case EVENT_GIFT_BOX:
			if ( attr1 )
				msg << "�������� ��ȯ �̺�Ʈ�� �������Դϴ�.";
			else
				msg << "�������� ��ȯ �̺�Ʈ�� ���������� �ʽ��ϴ�.";
			break;

		case RED_GIFT_BOX_RATIO:
			msg << "������ �������� ���� Ȯ�� : 1 / " << attr1;
			break;

		case BLUE_GIFT_BOX_RATIO:
			msg << "�Ķ��� �������� ���� Ȯ�� : 1 / " << attr1;
			break;

		case GREEN_GIFT_BOX_RATIO:
			msg << "�ʷϻ� �������� ���� Ȯ�� : 1 / " << attr1;
			break;

		case YELLOW_GIFT_BOX_RATIO:
			msg << "����� �������� ���� Ȯ�� : 1 / " << attr1;
			break;

		case NETMARBLE_CARD_RATIO:
			msg << "�ݸ��� ī�� ���� Ȯ�� : " << attr1 << " / 100000";
			break;

		case NETMARBLE_CARD_EVENT:
			msg << "�ݸ��� ī�� �̺�Ʈ : " << ((attr1)?"Yes":"No");
			break;

		case PREMIUM_TRIAL_EVENT:
			msg << "�����̾� ü�� �̺�Ʈ : " << ((attr1)?"Yes":"No");
			break;

		case PET_FOOD_EVENT:
			msg << "�� ���� �̺�Ʈ : " << ((attr1)?"Yes":"No");
			break;

		case HIGHER_PET_FOOD_RATIO:
			msg << "��ܰ� �� ���� Ȯ�� : " << attr1 << "%";
			break;

		case RACE_PET_FOOD_RATIO:
			msg << "������ �� ���� Ȯ�� : " << attr1 << "%";
			break;

		case PET_FOOD_RATIO:
			msg << "�� ���� ���� Ȯ�� : " << attr1 << " / 100000";
			break;

		case REVIVAL_SET_RATIO:
			msg << "�����̹� �� Ȯ�� : " << attr1 << "%";
			break;

		case TODAY_IS_HOLYDAY:
			if ( attr1 ) msg << "������ ������ �Դϴ�.";
			else msg << "������ �������� �ƴմϴ�.";
			break;

		case SLAYER_HP_RATIO:
			msg << "�����̾� HP���� : " << attr1 << "%";
			break;
		case VAMPIRE_HP_RATIO:
			msg << "�����̾� HP���� : " << attr1 << "%";
			break;
		case OUSTERS_HP_RATIO:
			msg << "�ƿ콺���� HP���� : " << attr1 << "%";
			break;
		case MONSTER_HP_RATIO:
			msg << "���� HP���� : " << attr1 << "%";
			break;

		case MONSTER_EXP_RATIO:
			msg << "���� EXP���� : " << attr1 << "%";
			break;

		case CLOVER_EVENT:
			msg << "����Ŭ�ι� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case CLOVER_RATIO:
			msg << "����Ŭ�ι� Ȯ�� : " << attr1 << "/100000";
			break;

		case MONSTER_DAMAGE_RATIO:
			msg << "���� Damage ���� : " << attr1 << "%";
			break;

		case RACE_PET_QUEST:
			msg << "2�� �� ����Ʈ : " << ((attr1)?"on":"off");
			break;

		case NICKNAME_PEN_EVENT:
			msg << "���̹��� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case NICKNAME_PEN_RATIO:
			msg << "���̹��� Ȯ�� : " << attr1 << "/100000";
			break;

		case GOLD_MEDAL_RATIO:
			msg << "�ݸ޴� Ȯ�� : " << attr1 << "/100000";
			break;

		case PET_DAY_EVENT:
			msg << "���� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case OLYMPIC_ITEM_RATIO:
			msg << "�ø��� �̺�Ʈ ������ ���� Ȯ�� : " << attr1 << "/100000";
			break;

		case OLYMPIC_EVENT:
			msg << "�ٵ� �ø��� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case CROWN_PRICE:
			msg << "����� ���� : " << attr1;
			break;

		case CHOBO_EVENT:
			msg << "�ʺ��� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case QUIT_GUILD_PENALTY_TERM:
			msg << "��� Ż��� �簡�� �Ұ� �Ⱓ : " << attr1;
			break;

		case GUILD_UNION_MAX:
			msg << "���� ��� ���� ���� : " << attr1;
			break;

		case LUCK_CHARM_RATIO:
			msg << "���� ��� ������ Ȯ�� : " << attr1;
			break;

		case GDR_LAIR_PC_LIMIT:
			msg << "���巹 ���� �ο� ���� : " << attr1;
			break;

		case DONATION_EVENT_200501:
			msg << "��� �̺�Ʈ 2005.01 : " << ((attr1)?"on":"off");
			break;

		case EVENT_NEW_YEAR_2005:
			msg << "2005�� ���� ���� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case BOKJORY_RATIO:
			msg << "������ ������ Ȯ�� : 1 / " << attr1;
			break;
			
		case EVENT_RED_RICE_CAKE_SOUP_RATIO:
			msg << "�̺�Ʈ ���� ���� ������ Ȯ�� : 1 / " << attr1;
			break;
			
		case EVENT_GREEN_RICE_CAKE_SOUP_RATIO:
			msg << "�̺�Ʈ ��� ���� ������ Ȯ�� : 1 / " << attr1;
			break;
			
		case EVENT_BLUE_RICE_CAKE_SOUP_RATIO:
			msg << "�̺�Ʈ �Ķ� ���� ������ Ȯ�� : 1 / " << attr1;
			break;
			
		case EVENT_BLACK_RICE_CAKE_SOUP_RATIO:
			msg << "�̺�Ʈ ���� ���� ������ Ȯ�� : 1 / " << attr1;
			break;
			
		case EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO:
			msg << "�̺�Ʈ ���� ���� ������ Ȯ�� : 1 / " << attr1;
			break;

		case TIME_PERIOD_EXP_2X:
			msg << "�ð��뺰 ����ġ 2�� �̺�Ʈ : " << ((attr1)?"on":"off");
			break;

		case ZONE_RANK_EXP:
			msg << "�ʵ� ��� ����ġ �߰� �߻�Ȯ��: " << attr1;
			break;

		default:
                       if(vt<VARIABLE_MAX) //add by viva
                        msg << VariableType2String[vt] << ": " << attr1;
//			msg << VariableType2String[vt] << ": " << attr1;
			break;
	}

	return msg.toString();
}

VariableManager* g_pVariableManager = NULL;

