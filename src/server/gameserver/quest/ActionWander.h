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
	virtual ActionType_t getActionType() const throw() { return ACTION_WANDER; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public :
	ZoneCoord_t getX() const throw() { return m_X; }
	void setX(ZoneCoord_t x) throw() { m_X = x; }

	ZoneCoord_t getY() const throw() { return m_Y; }
	void setY(ZoneCoord_t y) throw() { m_Y = y; }

	BYTE getRadius() const throw() { return m_Radius; }
	void setRadius(BYTE radius) throw() { m_Radius = radius; }

	BYTE getMovePercentage() const throw() { return m_MovePercentage; }
	void setMovePercentage(BYTE movePercentage) throw() { m_MovePercentage = movePercentage; }

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_WANDER; }
	virtual string getActionName() const throw() { return "Wander"; }
	virtual Action* createAction() const throw() { return new ActionWander(); }

};

#endif
