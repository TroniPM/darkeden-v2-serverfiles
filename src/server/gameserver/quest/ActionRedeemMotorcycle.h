////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRedeemMotorcycle.h
// Written By  : 
// Description : 
// �÷��̾ ���ӿ� ������ ��, ������̰� ��� �ְ�, �÷��̾��� �տ�
// ������� ��ü�� ������ �ִ� ������ �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REDEEM_MOTORCYCLE_H__
#define __ACTION_REDEEM_MOTORCYCLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRedeemMotorcycle;
//////////////////////////////////////////////////////////////////////////////

class Item;
class Zone;
class Slayer;

class ActionRedeemMotorcycle : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_REDEEM_MOTORCYCLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2=NULL) throw(Error);
	virtual string toString() ;

protected:
	bool load(Item* pItem, Slayer* pSlayer, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionRedeemMotorcycleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRedeemMotorcycleFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType()  { return Action::ACTION_REDEEM_MOTORCYCLE; }
	virtual string getActionName()  { return "RedeemMotorcycle"; }
	virtual Action* createAction()  { return new ActionRedeemMotorcycle(); }
};



#endif
