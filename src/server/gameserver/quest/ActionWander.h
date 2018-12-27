//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWander.h
// Written By  : 
// Description :
// ���� ��ġ���� �Դٰ��� ��Ȳ�ϴ� ũ��ó�� ǥ���Ҷ� ����ϴ� �׼��̴�.
// ũ��ó�� ���� ��ġ�� �߽����� �ݰ� r ���� �簢 �������� 
// M �ۼ�Ʈ�� Ȯ���� �̵��ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WANDER_H__
#define __ACTION_WANDER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWander;
//////////////////////////////////////////////////////////////////////////////

class ActionWander : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_WANDER; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public :
	ZoneCoord_t getX()  { return m_X; }
	void setX(ZoneCoord_t x)  { m_X = x; }

	ZoneCoord_t getY()  { return m_Y; }
	void setY(ZoneCoord_t y)  { m_Y = y; }

	BYTE getRadius()  { return m_Radius; }
	void setRadius(BYTE radius)  { m_Radius = radius; }

	BYTE getMovePercentage()  { return m_MovePercentage; }
	void setMovePercentage(BYTE movePercentage)  { m_MovePercentage = movePercentage; }

private :
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
	BYTE        m_Radius;
	BYTE        m_MovePercentage;	
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWanderFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWanderFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WANDER; }
	virtual string getActionName()  { return "Wander"; }
	virtual Action* createAction()  { return new ActionWander(); }

};

#endif
