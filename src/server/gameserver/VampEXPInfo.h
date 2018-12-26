////////////////////////////////////////////////////////////////////////////////
// Filename    : VampEXPInfo.h
// Written By  : beowulf
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VAMP_EXP_INFO_H__
#define __VAMP_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
// Class VampEXPInfo
////////////////////////////////////////////////////////////////////////////////

class VampEXPInfo 
{
public:
	VampEXPInfo() ;
	~VampEXPInfo() ;

public:
	void setLevel(uint lev) throw() { m_Level = lev; }
	uint getLevel()  { return m_Level; }

	void setGoalExp(Exp_t sum) throw() { m_GoalExp = sum; }
	uint getGoalExp()  { return m_GoalExp; }

	void setAccumExp(Exp_t accum) throw() { m_AccumExp = accum ; }
	uint getAccumExp()  { return m_AccumExp; }

	string toString() ;

private:
	Level_t m_Level;		// 레벨
	Exp_t m_GoalExp;   	// 목표 경험치
	Exp_t m_AccumExp;		// 누적 경험치
};


////////////////////////////////////////////////////////////////////////////////
// Class VampEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class VampEXPInfoManager 
{
public:
	VampEXPInfoManager() ;
	~VampEXPInfoManager() ;

public:
	void init();
	void load();

	VampEXPInfo* getVampEXPInfo(uint VampEXPType) ;
	void addVampEXPInfo(VampEXPInfo* pVampEXPInfo) throw(DuplicatedException, Error);

	string toString() ;

private:
	uint          m_VampEXPCount;
	VampEXPInfo** m_VampEXPInfoList;
		
};

// Global Variable Definition
extern VampEXPInfoManager* g_pVampEXPInfoManager;

#endif	

