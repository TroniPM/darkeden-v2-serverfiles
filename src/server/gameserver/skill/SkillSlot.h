//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillSlot.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SLOT_H__
#define __SKILL_SLOT_H__

#include "Types.h"
#include "Timeval.h"
#include "Skill.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Class SkillSlot;
//////////////////////////////////////////////////////////////////////////////

class SkillSlot 
{
public:
	SkillSlot() throw();
	SkillSlot(SkillType_t SkillType, DWORD Exp, ulong Interval) throw();
	virtual ~SkillSlot() throw();

public:
	virtual void save(const string & ownerID) throw(Error);
	virtual void save() throw(Error);

	virtual void create(const string & ownerID) throw(Error);

	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t Type) throw() { m_SkillType = Type; }

	void setExp(Exp_t Exp) throw() { m_Exp = Exp; }
	Exp_t getExp() throw() { return m_Exp; }

	void setExpLevel(ExpLevel_t ExpLevel) throw() { m_ExpLevel = ExpLevel; }
	ExpLevel_t getExpLevel() throw() { return m_ExpLevel; }

	Turn_t getInterval() throw() { return m_Interval; }
	void setInterval(Turn_t Interval) throw() { m_Interval = Interval; }

	Turn_t getCastingTime() throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

	Timeval getRunTime() throw() { return m_runTime; }
	void setRunTime() throw();
	void setRunTime(Turn_t delay, bool bSave=true) throw();

	string getName()  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// ��밡���� ��� true
	// ��� �Ұ����� ��� false
	void setDisable() throw() { m_Enable = false; }
	void setEnable() throw() { m_Enable = true; }
	bool canUse()  { return m_Enable; } 

	// ���� ĳ������ �����Ҷ����� ���� �ð�
	Turn_t getRemainTurn( Timeval currentTime ) ;

protected :
	string       m_Name;
	SkillType_t  m_SkillType;     // ����, ����� ����
	Exp_t        m_Exp;           // ���õ�
	ExpLevel_t   m_ExpLevel;      // ���õ� ����
	Turn_t       m_Interval;      // ����, ����� ������, 0.1 �� ����
	Turn_t       m_CastingTime;   // ĳ���� Ÿ��... 0.1�� ����
	Timeval      m_runTime;       // ������ �� �� �ִ� �ð�
	bool         m_Enable;        // ��� ���� �Ѱ� ���Ѱ�
};

#endif // __SKILL_SLOT_H__
