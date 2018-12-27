//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareShop.h
// Written By  : 
// Description : 
// ���� NPC�� ���� ó�� �ε��� ��, ���� NPC�� �Ȱ� �� ��������
// �غ��ϴ� �׼��̴�. ShopTemplate Ŭ������ �Ŵ����� ������ ��.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PREPARE_SHOP_H__
#define __ACTION_PREPARE_SHOP_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareShop
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareShop : public Action 
{
public:
	ActionPrepareShop() ;
	virtual ~ActionPrepareShop() ;
	
public:
	virtual ActionType_t getActionType()  { return ACTION_PREPARE_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	BYTE getListNum()  { return m_ListNum;}
	void setListNum(BYTE num)  { m_ListNum = num;}

	void addListElement(ShopTemplateID_t id) ;
	void clearList()  { m_List.clear(); m_ListNum = 0; }

private :
	BYTE                   m_ListNum;
	list<ShopTemplateID_t> m_List;
	MarketCond_t           m_MarketCondBuy;
	MarketCond_t           m_MarketCondSell;
	ZoneID_t			   m_TaxingCastleZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareShopFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareShopFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_PREPARE_SHOP; }
	virtual string getActionName()  { return "PrepareShop"; }
	virtual Action* createAction()  { return new ActionPrepareShop(); }
};

#endif
