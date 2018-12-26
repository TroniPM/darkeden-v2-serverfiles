////////////////////////////////////////////////////////////////////////////////
// Filename    : OustersEXPInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_EXP_INFO_H__
#define __OUSTERS_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class OustersEXPInfo
////////////////////////////////////////////////////////////////////////////////

class OustersEXPInfo 
{
public:
	OustersEXPInfo() ;
	~OustersEXPInfo() ;

public:
	void setLevel(uint lev) throw() { m_Level = lev; }
	uint getLevel()  { return m_Level; }

	void setGoalExp(Exp_t sum) throw() { m_GoalExp = sum; }
	uint getGoalExp()  { return m_GoalExp; }

	void setAccumExp(Exp_t accum) throw() { m_AccumExp = accum ; }
	uint getAccumExp()  { return m_AccumExp; }

	void setSkillPointBonus(SkillBonus_t SkillBonus) throw() { m_SkillPointBonus = SkillBonus; }
	SkillBonus_t getSkillPointBonus()  { return m_SkillPointBonus; }

	string toString() ;

private:
	Level_t m_Level;		// 레벨
	Exp_t m_GoalExp;   		// 목표 경험치
	Exp_t m_AccumExp;		// 누적 경험치
	SkillBonus_t m_SkillPointBonus;		// 레벨업시 스킬 보너스 포인트
};


////////////////////////////////////////////////////////////////////////////////
// Class OustersEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class OustersEXPInfoManager 
{
public:
	OustersEXPInfoManager() ;
	~OustersEXPInfoManager() ;

public:
	void init();
	void load();

	OustersEXPInfo* getOustersEXPInfo(uint OustersEXPType) ;
	void addOustersEXPInfo(OustersEXPInfo* pOustersEXPInfo) throw(DuplicatedException, Error);

	string toString() ;

private:
	uint          m_OustersEXPCount;
	OustersEXPInfo** m_OustersEXPInfoList;
		
};

// Global Variable Definition
extern OustersEXPInfoManager* g_pOustersEXPInfoManager;

#endif
