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
	ActionPrepareShop() throw();
	virtual ~ActionPrepareShop() throw();
	
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_PREPARE_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	BYTE getListNum() const throw() { return m_ListNum;}
	void setListNum(BYTE num) throw() { m_ListNum = num;}

	void addListElement(ShopTemplateID_t id) throw();
	void clearList() throw() { m_List.clear(); m_ListNum = 0; }

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_PREPARE_SHOP; }
	virtual string getActionName() const throw() { return "PrepareShop"; }
	virtual Action* createAction() const throw() { return new ActionPrepareShop(); }
};

#endif
