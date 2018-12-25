//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireSkillSlot.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_SKILL_SLOT_H__
#define __VAMPIRE_SKILL_SLOT_H__

#include "Types.h"
#include "Timeval.h"
#include "Skill.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Class VampireSkillSlot;
//////////////////////////////////////////////////////////////////////////////

class VampireSkillSlot 
{
public:
    VampireSkillSlot() throw();
    VampireSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime) throw();
    virtual ~VampireSkillSlot() throw();

public:
	virtual void save(const string & ownerID);
	virtual void save();
	virtual void create(const string & ownerID);

    SkillType_t getSkillType() throw() { return m_SkillType; }

    void setSkillType(SkillType_t Type) throw() { m_SkillType = Type; }

    ulong getInterval() throw() { return m_Interval; }

    void setInterval(ulong Interval) throw() { m_Interval = Interval; }

	Turn_t getCastingTime() throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

    Timeval getRunTime() throw() { return m_runTime; }
	void setRunTime() throw();
	void setRunTime(Turn_t delay) throw();

	string getName()  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// ���� ĳ������ �����Ҷ����� ���� �ð�
	Turn_t getRemainTurn( Timeval currentTime ) ;

private:
	string       m_Name;
	SkillType_t  m_SkillType;   // ����, ����� ����
	Turn_t       m_Interval;    // ����, ����� ������, �� ����
	Turn_t       m_CastingTime; // ĳ���� Ÿ��... 0.1�� ����
	Timeval      m_runTime;     // ������ �� �� �ִ� �ð�
};

#endif // __VAMPIRE_SKILL_SLOT_H__
