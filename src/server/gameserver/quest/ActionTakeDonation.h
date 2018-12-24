//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeDonation.h
// Written By  : 
// Description :
// Creature�� �־��� ��縦 ���Ѵ�. �� ���� ũ��ó�� �Ӹ� ���� ��ǳ������
// ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TAKE_DONATION_H__
#define __ACTION_TAKE_DONATION_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTakeDonation;
//////////////////////////////////////////////////////////////////////////////

class ActionTakeDonation : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_TAKE_DONATION; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	Gold_t getAmount(void) const { return m_Amount; }
	void setAmount(Gold_t amount) { m_Amount = amount; }

private:
	Gold_t m_Amount; // ���� ���� ��

};

//////////////////////////////////////////////////////////////////////////////
// class ActionTakeDonationFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTakeDonationFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_TAKE_DONATION; }
	virtual string getActionName() const throw() { return "TakeDonation"; }
    virtual Action* createAction() const throw() { return new ActionTakeDonation(); }
};

#endif
