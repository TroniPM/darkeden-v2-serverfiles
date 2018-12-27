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
    VampireSkillSlot() ;
    VampireSkillSlot(SkillType_t SkillType, ulong Interval, ulong CastingTime) ;
    virtual ~VampireSkillSlot() ;

public:
	virtual void save(const string & ownerID);
	virtual void save();
	virtual void create(const string & ownerID);

    SkillType_t getSkillType()  { return m_SkillType; }

    void setSkillType(SkillType_t Type)  { m_SkillType = Type; }

    ulong getInterval()  { return m_Interval; }

    void setInterval(ulong Interval)  { m_Interval = Interval; }

	Turn_t getCastingTime()  { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime)  { m_CastingTime = CastingTime; }

    Timeval getRunTime()  { return m_runTime; }
	void setRunTime() ;
	void setRunTime(Turn_t delay) ;

	string getName()  { return m_Name; }
	void setName(const string & Name) { m_Name = Name; }

	// 다음 캐스팅이 가능할때까지 남은 시간
	Turn_t getRemainTurn( Timeval currentTime ) ;

private:
	string       m_Name;
	SkillType_t  m_SkillType;   // 마법, 기술의 종류
	Turn_t       m_Interval;    // 마법, 기술의 딜레이, 초 단위
	Turn_t       m_CastingTime; // 캐스팅 타임... 0.1초 단위
	Timeval      m_runTime;     // 다음에 쓸 수 있는 시간
};

#endif // __VAMPIRE_SKILL_SLOT_H__
