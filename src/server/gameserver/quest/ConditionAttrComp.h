////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAttrComp.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_COMP_H__
#define __ATTR_COMP_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

enum
{
	CONDITION_ATTR_COMP_LOWER = 0,
	CONDITION_ATTR_COMP_EQUAL,
	CONDITION_ATTR_COMP_HIGHER,

	CONDITION_ATTR_COMP_MAX
};

const string ConditionAttrCompOperator2String[] = 
{
	"LOWER",
	"EQUAL",
	"HIGHER",

	"MAX"
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAttrComp;
//////////////////////////////////////////////////////////////////////////////

class ConditionAttrComp : public Condition 
{
public:
	ConditionAttrComp() ;
	virtual ~ConditionAttrComp() ;

public:
	virtual ConditionType_t getConditionType()  { return CONDITION_ATTR_COMP; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:
	void parseOperator(string& op, uint& var) ;
	bool satisfy(uint op, uint current, uint restriction) ;

private:
	uint m_ReqSTR;        // �ʿ� STR
	uint m_ReqDEX;        // �ʿ� DEX
	uint m_ReqINT;        // �ʿ� INT
	uint m_ReqSum;        // �ʿ� �ɷ�ġ�� ��
	uint m_ReqLevel;      // �ʿ� LEVEL
	uint m_ReqAdv;      // �ʿ� LEVEL

	uint m_STROperator;   // STR ������
	uint m_DEXOperator;   // DEX ������
	uint m_INTOperator;   // INT ������
	uint m_SumOperator;   // SUM ������
	uint m_LevelOperator; // LEVEL ������

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAttrCompFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAttrCompFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_ATTR_COMP; }
    virtual Condition* createCondition()  { return new ConditionAttrComp(); }
    virtual string getConditionName()  { return "AttrComp"; }
};

#endif
