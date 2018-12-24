//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWanderZone.h
// Written By  : 
// Description :
// ���� ��ġ���� �Դٰ��� ��Ȳ�ϴ� ũ��ó�� ǥ���Ҷ� ����ϴ� �׼��̴�.
// ũ��ó�� ���� ��ġ�� �߽����� �ݰ� r ���� �簢 �������� 
// M �ۼ�Ʈ�� Ȯ���� �̵��ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WANDER_ZONE_H__
#define __ACTION_WANDER_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWanderZone;
//////////////////////////////////////////////////////////////////////////////

class ActionWanderZone : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_WANDER_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public :
	BYTE getMovePercentage() const throw() { return m_MovePercentage; }
	void setMovePercentage(BYTE movePercentage) throw() { m_MovePercentage = movePercentage; }

private :
	BYTE        m_MovePercentage;	
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWanderZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWanderZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_WANDER_ZONE; }
	virtual string getActionName() const throw() { return "WanderZone"; }
	virtual Action* createAction() const throw() { return new ActionWanderZone(); }

};

#endif
