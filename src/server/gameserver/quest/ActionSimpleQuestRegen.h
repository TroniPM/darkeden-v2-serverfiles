//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestRegen.h
// Written By  : 
// Description : 
// ���� NPC�� ���� ó�� �ε��� ��, ���� NPC�� �Ȱ� �� ��������
// �غ��ϴ� �׼��̴�. ShopTemplate Ŭ������ �Ŵ����� ������ ��.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SIMPLE_QUEST_REGEN_H__
#define __ACTION_SIMPLE_QUEST_REGEN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestRegen
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestRegen : public Action 
{
public:
	ActionSimpleQuestRegen() throw();
	virtual ~ActionSimpleQuestRegen() throw();
	
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SIMPLE_QUEST_REGEN; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private :
	Timeval                m_Period;    // ������ ������ �ֱ�
	Timeval                m_NextRegen; // ���� ���� ���� �ð�

};


////////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestRegenFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestRegenFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SIMPLE_QUEST_REGEN; }
	virtual string getActionName() const throw() { return "SimpleQuestRegen"; }
	virtual Action* createAction() const throw() { return new ActionSimpleQuestRegen(); }

};
#endif
