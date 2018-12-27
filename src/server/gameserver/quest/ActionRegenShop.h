//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegenShop.h
// Written By  : 
// Description : 
// ���� NPC�� ���� ó�� �ε��� ��, ���� NPC�� �Ȱ� �� ��������
// �غ��ϴ� �׼��̴�. ShopTemplate Ŭ������ �Ŵ����� ������ ��.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REGEN_SHOP_H__
#define __ACTION_REGEN_SHOP_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRegenShop
//////////////////////////////////////////////////////////////////////////////

class ActionRegenShop : public Action 
{
public:
	ActionRegenShop() ;
	virtual ~ActionRegenShop() ;
	
public:
	virtual ActionType_t getActionType()  { return ACTION_REGEN_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	void addListElement(ShopTemplateID_t id)  { m_List.push_back(id); }
	void clearList()  { m_List.clear(); }

private :
	list<ShopTemplateID_t> m_List;      // Shop template ID list
	Timeval                m_Period;    // ������ ������ �ֱ�
	Timeval                m_NextRegen; // ���� ���� ���� �ð�

};


////////////////////////////////////////////////////////////////////////////////
// class ActionRegenShopFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionRegenShopFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_REGEN_SHOP; }
	virtual string getActionName()  { return "RegenShop"; }
	virtual Action* createAction()  { return new ActionRegenShop(); }

};
#endif
