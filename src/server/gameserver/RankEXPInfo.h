////////////////////////////////////////////////////////////////////////////////
// Filename    : RankEXPInfo.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __RANK_EXP_INFO_H__
#define __RANK_EXP_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "RankExpTable.h"

////////////////////////////////////////////////////////////////////////////////
// Class RankEXPInfo
////////////////////////////////////////////////////////////////////////////////

class RankEXPInfo 
{
public:
	RankEXPInfo() ;
	~RankEXPInfo() ;

public:
	void setLevel(uint lev) throw() { m_Level = lev; }
	uint getLevel()  { return m_Level; }

	void setGoalExp(uint sum) throw() { m_GoalExp = sum; }
	uint getGoalExp()  { return m_GoalExp; }

	void setAccumExp(uint accum) throw() { m_AccumExp = accum ; }
	uint getAccumExp()  { return m_AccumExp; }

	string toString() ;

private:
	uint m_Level;
	uint m_GoalExp;
	uint m_AccumExp;
};


////////////////////////////////////////////////////////////////////////////////
// Class RankEXPInfoManager
////////////////////////////////////////////////////////////////////////////////

class RankEXPInfoManager 
{
public:
	RankEXPInfoManager() ;
	~RankEXPInfoManager() ;

public:
	void init(RankType rankType);
	void load(RankType rankType);

	RankEXPInfo* getRankEXPInfo(uint value) ;
	void addRankEXPInfo(RankEXPInfo* pRankEXPInfo) ;

	string toString() ;

private:
	uint             m_RankEXPCount;
	RankEXPInfo** m_RankEXPInfoList;
};

// global variable definition
extern RankEXPInfoManager* g_pRankEXPInfoManager[RANK_TYPE_MAX];

#endif	
