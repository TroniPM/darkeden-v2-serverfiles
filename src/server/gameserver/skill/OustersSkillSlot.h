//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersSkillSlot.h
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_SKILL_SLOT_H__
#define __OUSTERS_SKILL_SLOT_H__

#include "Types.h"
#include "Timeval.h"
#include "Skill.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// Class OustersSkillSlot;
//////////////////////////////////////////////////////////////////////////////

class OustersSkillSlot 
{
public:
    OustersSkillSlot() throw();
    OustersSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime) throw();
    virtual ~OustersSkillSlot() throw();

public:
	virtual void save(const string & ownerID) throw(Error);
	virtual void save() throw(Error);
	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);

    SkillType_t getSkillType() throw() { return m_SkillType; }
    void setSkillType(SkillType_t Type) throw() { m_SkillType = Type; }

	ExpLevel_t getExpLevel() const throw() { return m_ExpLevel; }
	void setExpLevel( ExpLevel_t ExpLevel ) throw() { m_ExpLevel = ExpLevel; }

    ulong getInterval() throw() { return m_Interval; }
    void setInterval(ulong Interval) throw() { m_Interval = Interval; }

	Turn_t getCastingTime() throw() { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

    Timeval getRunTime() throw() { return m_runTime; }
	void setRunTime() throw();
	void setRunTime(Turn_t delay) throw();

	string getName() const throw() { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// ���� ĳ������ �����Ҷ����� ���� �ð�
	Turn_t getRemainTurn( Timeval currentTime ) const throw();

private:
	string       m_Name;
	SkillType_t  m_SkillType;   // ����, ����� ����
	ExpLevel_t   m_ExpLevel;    // ��ų ����
	Turn_t       m_Interval;    // ����, ����� ������, �� ����
	Turn_t       m_CastingTime; // ĳ���� Ÿ��... 0.1�� ����
	Timeval      m_runTime;     // ������ �� �� �ִ� �ð�
};

#endif // __OUSTERS_SKILL_SLOT_H__
