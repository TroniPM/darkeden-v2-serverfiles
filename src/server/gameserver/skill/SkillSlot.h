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
	SkillSlot() ;
	SkillSlot(SkillType_t SkillType, DWORD Exp, ulong Interval) ;
	virtual ~SkillSlot() ;

public:
	virtual void save(const string & ownerID);
	virtual void save();

	virtual void create(const string & ownerID);

	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t Type)  { m_SkillType = Type; }

	void setExp(Exp_t Exp)  { m_Exp = Exp; }
	Exp_t getExp()  { return m_Exp; }

	void setExpLevel(ExpLevel_t ExpLevel)  { m_ExpLevel = ExpLevel; }
	ExpLevel_t getExpLevel()  { return m_ExpLevel; }

	Turn_t getInterval()  { return m_Interval; }
	void setInterval(Turn_t Interval)  { m_Interval = Interval; }

	Turn_t getCastingTime()  { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime)  { m_CastingTime = CastingTime; }

	Timeval getRunTime()  { return m_runTime; }
	void setRunTime() ;
	void setRunTime(Turn_t delay, bool bSave=true) ;

	string getName()  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// ��밡���� ��� true
	// ��� �Ұ����� ��� false
	void setDisable()  { m_Enable = false; }
	void setEnable()  { m_Enable = true; }
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
