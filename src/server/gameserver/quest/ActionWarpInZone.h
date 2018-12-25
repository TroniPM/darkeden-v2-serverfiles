//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpInZone.h
// Written By  : 
// Description :
// ���� ��ġ���� �Դٰ��� ��Ȳ�ϴ� ũ��ó�� ǥ���Ҷ� ����ϴ� �׼��̴�.
// ũ��ó�� ���� ��ġ�� �߽����� �ݰ� r ���� �簢 �������� 
// M �ۼ�Ʈ�� Ȯ���� �̵��ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_IN_ZONE_H__
#define __ACTION_WARP_IN_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpInZone;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpInZone : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_WARP_IN_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public :
	BYTE getMovePercentage()  { return m_MovePercentage; }
	void setMovePercentage(BYTE movePercentage) throw() { m_MovePercentage = movePercentage; }

private :
	BYTE        m_MovePercentage;	
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpInZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpInZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WARP_IN_ZONE; }
	virtual string getActionName()  { return "WarpInZone"; }
	virtual Action* createAction()  { return new ActionWarpInZone(); }

};

#endif
