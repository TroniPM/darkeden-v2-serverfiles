////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegenEventShop.cpp
// Written By  : excel96
// Description : 
// ũ�������� �̺�Ʈ�� ������ �����ϴ� �׼�
////////////////////////////////////////////////////////////////////////////////

#include "ActionRegenEventShop.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "ShopTemplate.h"
#include "OptionInfo.h"
#include "DB.h"
#include "LogClient.h"
#include "ItemFactoryManager.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionRegenEventShop::ActionRegenEventShop()
	throw()
{
	__BEGIN_TRY

	m_Period.tv_sec     = 0;
	m_Period.tv_usec    = 0;
	m_NextRegen.tv_sec  = 0;
	m_NextRegen.tv_usec = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ActionRegenEventShop::~ActionRegenEventShop()
	throw()
{
	__BEGIN_TRY

	clearList();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionRegenEventShop::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
	    // read NPC id
		int        NPCID   = propertyBuffer.getPropertyInt("NPCID");
		Statement* pStmt   = NULL;
		Result*    pResult = NULL;

		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT ID from ShopTemplate where NPCID = %d", NPCID);
			
			while (pResult->next())
			{
				ShopTemplateID_t id = pResult->getInt(1);
				addListElement(id);
			}

			delete pStmt;
		}
		END_DB(pStmt)

		// ���� ������Ʈ �ֱ⸦ �о���δ�. (�� ����)
		int nSecond = propertyBuffer.getPropertyInt("Period");
		m_Period.tv_sec = nSecond;

		// ���� ���� ������Ʈ�� ���� �� ���ΰ��� ������ �ش�.
		Timeval currentTime;
		getCurrentTime(currentTime);
		m_NextRegen = currentTime;
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
// NOTE : ShopTemplate�� �� �׼��� ����Ǳ� ���� ��� �ε�Ǿ� �־�� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionRegenEventShop::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature1->isNPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Assert(pNPC != NULL);

	// �̺�Ʈ�� NPC�� �������ش�. 
	pNPC->setShopType(SHOPTYPE_EVENT);

	Zone* pZone = pNPC->getZone();
	Assert(pZone != NULL);

	// ���� �ð��� ����.
	Timeval currentTime;
	getCurrentTime(currentTime);

	// ������Ʈ�� �ð��� ���� ���� �ʾҴٸ� �� �����Ѵ�.
	if (currentTime < m_NextRegen) return;

	// ������ PC�� �̾߱��ϰ� �ִ� �÷��̾ ������ ���� �˻��Ѵ�.
	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
	int centerX = pNPC->getX();
	int centerY = pNPC->getY();
	try
	{
		for (int zx = centerX - 5; zx <= centerX+5; zx++)
		{
			for (int zy = centerY - 5; zy <= centerY+5; zy++)
			{
				// ��ǥ�� �Ѱ踦 �Ѿ�� �ʾҴ��� üũ...
				if (!rect.ptInRect(zx, zy))
				{
					continue;
				}

				Tile& tile = pZone->getTile(zx, zy);

				// �ɾ�ٴϴ� ũ���ĸ� �˻�
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					Assert(pNearCreature != NULL);
					// NPC�� �̾߱��ϰ� �ִ� ���� ������ �� ����
					if (pNearCreature->isPC())
					{
						return;
					}
				}
				// ���ƴٴϴ� ũ���ĸ� �˻�
				if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					Assert(pNearCreature != NULL);
					// NPC�� �̾߱��ϰ� �ִ� ���� ������ �� ����
					if (pNearCreature->isPC())
					{
						return;
					}
				}
			}
		}
	}
	catch (Throwable & t)
	{
		filelog("shopbug.txt", "%s", t.toString().c_str());
		return;
	}

	// ���� NPC�� ������ �ִ� �������� ���� ������...���� ������ �ø���.
	// �ϴ� Ŭ�����ϱ� ���� �α׸� �Ѵ�.
	for (ShopRackType_t rackType=0; rackType<SHOP_RACK_TYPE_MAX; rackType++)
	{
		for (BYTE rackIndex=0; rackIndex<SHOP_RACK_INDEX_MAX; rackIndex++)
		{
			Item* pShopItem = pNPC->getShopItem(rackType, rackIndex);
			if (pShopItem != NULL)
				log(LOG_SHOP_DESTROY_ITEM, pNPC->getName(), "", pShopItem->toString());
		}
	}

	pNPC->clearShopItem();

	for (int i=0; i<SHOP_RACK_TYPE_MAX; i++)
		pNPC->increaseShopVersion(i);

	// �������� �����.
	list<ShopTemplateID_t> IDList[SHOP_RACK_TYPE_MAX];
	int                    combi[SHOP_RACK_TYPE_MAX] = {0,0,0};
	int                    count[SHOP_RACK_TYPE_MAX] = {0,0,0};
	int                    trialMax = 0;
	ShopTemplate*          pTemplate = NULL;
	ShopRackType_t         shopType;
	int                    itemClass;
	ItemType_t             minItemType, maxItemType, itemType;
	uint                   minOptionLevel, maxOptionLevel;
	OptionType_t           optionType;

	// ������ �����ø��� ������ Ŭ������ �ּ�, �ִ� Ÿ���� ������ �ִ�.
	// �ּ�, �ִ� Ÿ���� ������, �ش��ϴ� ������ �� ������
	// �����ؾ� �ϴ� ���� �� �� �ִ�. ���� ��� ������ ����.
	// MinItemType : 0, MaxItemType : 0 --> 1����
	// MinItemType : 0, MaxItemType : 2 --> 3����
	for (list<ShopTemplateID_t>::const_iterator itr=m_List.begin(); itr != m_List.end(); itr++)
	{
		pTemplate = g_pShopTemplateManager->getTemplate((*itr));

		Assert(pTemplate != NULL);
		
		shopType    = pTemplate->getShopType();
		itemClass   = pTemplate->getItemClass();
		minItemType = pTemplate->getMinItemType();
		maxItemType = pTemplate->getMaxItemType();
		
		// ���� ����(���, �����...)�� ����, 
		// ������ �� ���ø��� ID�� ����Ʈ�� ����־� �ΰ�,
		// ������ �������� �������� ������ �д�.
		IDList[shopType].push_back(*itr);
		combi[shopType] += (maxItemType - minItemType + 1);
	}

	// �� ������ �������� �����Ѵ�.
	for (ShopRackType_t i=0; i<SHOP_RACK_TYPE_MAX; i++)
	{
		// �� Ÿ���� ������ 20�������� �������� ����.
		// ���� �����ؾ� �� �������� ������ 5�������,
		// ������ �������� 4������ ������� �� �ִ�.
		// ������ 6�������, 3������ ������� �� �ִ�.
		// �� �õ� Ƚ���� trialMax �������� ����ִ´�.
		if (combi[i] == 0) trialMax = 0;
		else trialMax = (int)(floor(SHOP_RACK_INDEX_MAX/combi[i]));

		// ���� �� Ÿ���� ����̶��, ���� �������� ���� ��
		// �����ϴ� ���� �ǹ̰� �����Ƿ�, �ѹ��� �������� �����Ѵ�.
		if (i == SHOP_RACK_NORMAL
			|| i == SHOP_RACK_MYSTERIOUS) trialMax = 1;

		// �Ʊ� ������ ���Ҵ� �� ���ø� ID ����Ʈ���� �ϳ����� �̾ƿͼ�,
		// ���� �������� �����Ѵ�.
		for (list<ShopTemplateID_t>::const_iterator itr=IDList[i].begin(); itr != IDList[i].end(); itr++)
		{
			pTemplate      = g_pShopTemplateManager->getTemplate((*itr));
			itemClass      = pTemplate->getItemClass();
			minItemType    = pTemplate->getMinItemType();
			maxItemType    = pTemplate->getMaxItemType();
			minOptionLevel = pTemplate->getMinOptionLevel();
			maxOptionLevel = pTemplate->getMaxOptionLevel();

			// ���� ���������� �ɼ� Ÿ���� ���͸� �����صд�.
			//vector<OptionType_t> optionVector = g_pOptionInfoManager->getPossibleOptionVector((Item::ItemClass)itemClass, minOptionLevel, maxOptionLevel);
			// ShopTemplate���� ItemType�� 2,3�� ���´ٸ� optionType�� +2�� �����ϰ�
			// ShopTemplate���� ItemType�� �ٸ� ���̶��, +3���� �ֵ��� �Ѵ�.

			vector<OptionType_t> optionVector;
			if(minItemType == 2 && maxItemType == 3)
			{
				optionVector.push_back(2);  // STR+2
				optionVector.push_back(7);  // DEX+2
				optionVector.push_back(12); // INT+2
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(79); // ASPEED+2
			}
			else if(minItemType == 4 && maxItemType ==5)
			{
				optionVector.push_back(3);  // STR+3
				optionVector.push_back(8);  // DEX+3
				optionVector.push_back(13); // INT+3
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(80); // ASPEED+3
			}
			else if(minItemType == 6 && maxItemType == 6)
			{
				optionVector.push_back(4);  // STR+4
				optionVector.push_back(9);  // DEX+4
				optionVector.push_back(14); // INT+4
				//optionVector.push_back(50); // DAM+3
				optionVector.push_back(80); // ASPEED+3
			}

			for (ItemType_t type=minItemType; type<=maxItemType; type++)
			{
				// �� Ÿ���� ������ 20�������� �������� ����.
				// ���� �����ؾ� �� �������� ������ 5�������,
				// ������ �������� 4������ ������� �� �ִ�.
				// ������ 6�������, 3������ ������� �� �ִ�.
				for (int tc=0; tc<trialMax; tc++)
				{
					itemType = type;

					// �ɼ� ���� ������ �������� �ɼ��� �̾Ƴ���.
					// �翬�� ������ �ɼ��� ���ٸ�, optionType�� 0(���ɼ�)�̴�.
					if (optionVector.size() > 0)
					{
						int randValue = rand();
						int size      = optionVector.size();
						int index     = randValue%size;

						optionType = optionVector[index];
					}
					else optionType = 0;

					// ������ �������� �����.
					Item::ItemClass IClass = Item::ItemClass(itemClass);
					list<OptionType_t> optionTypes;
					if (optionType!=0)
						optionTypes.push_back( optionType );
					Item* pItem = g_pItemFactoryManager->createItem(IClass, itemType, optionTypes);
					Assert(pItem != NULL);

					// zone�� object registery�� ���.
					(pZone->getObjectRegistry()).registerObject(pItem);

					// �ش� �����忡 �ڸ��� �ִٸ� �������� ���Ѵ�.
					if (count[i] < SHOP_RACK_INDEX_MAX)
					{
						pNPC->insertShopItem(i, count[i], pItem);
						count[i] = count[i] + 1;
					}
				}
			}
		}
	}

	// ���� ������Ʈ�� �ð��� �����ش�.
	m_NextRegen = m_NextRegen + m_Period;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRegenEventShop::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	int          i = 0;

	msg << "ActionRegenEventShop(";
	list<ShopTemplateID_t>::const_iterator itr=m_List.begin();
	for (; itr != m_List.end(); itr++)
		msg << "Item" << i++ << ":" 
			<< (int)(*itr) << ",";
	msg << ")";
	
	return msg.toString();
	
	__END_CATCH
}
