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
    OustersSkillSlot() ;
    OustersSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime) ;
    virtual ~OustersSkillSlot() ;

public:
	virtual void save(const string & ownerID);
	virtual void save();
	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);

    SkillType_t getSkillType()  { return m_SkillType; }
    void setSkillType(SkillType_t Type)  { m_SkillType = Type; }

	ExpLevel_t getExpLevel()  { return m_ExpLevel; }
	void setExpLevel( ExpLevel_t ExpLevel )  { m_ExpLevel = ExpLevel; }

    ulong getInterval()  { return m_Interval; }
    void setInterval(ulong Interval)  { m_Interval = Interval; }

	Turn_t getCastingTime()  { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime)  { m_CastingTime = CastingTime; }

    Timeval getRunTime()  { return m_runTime; }
	void setRunTime() ;
	void setRunTime(Turn_t delay) ;

	string getName()  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// ���� ĳ������ �����Ҷ����� ���� �ð�
	Turn_t getRemainTurn( Timeval currentTime ) ;

private:
	string       m_Name;
	SkillType_t  m_SkillType;   // ����, ����� ����
	ExpLevel_t   m_ExpLevel;    // ��ų ����
	Turn_t       m_Interval;    // ����, ����� ������, �� ����
	Turn_t       m_CastingTime; // ĳ���� Ÿ��... 0.1�� ����
	Timeval      m_runTime;     // ������ �� �� �ִ� �ð�
};

#endif // __OUSTERS_SKILL_SLOT_H__
